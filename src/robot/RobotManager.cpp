/*
 * RobotManager.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "RobotManager.h"

RobotManager::RobotManager() {
	// Définition des paramètres généraux pour le manager
	odom = Odometrie();
	asserv = AsservissementPolaire();

	// Initialisation des pointeurs
	enc = 0;
	moteurs = 0;
	hasObstacle = 0;

	// Initialisation des valeurs par défaut
	timePrec = time = 0;
	trajetAtteint = false;
	trajetEnApproche = false;
	evittementEnCours = false;

	fenetreArretDistance = Conv.mmToPulse(1);
	fenetreArretOrientation = Conv.degToPulse(1);

	// Angle de départ pour les déplacement.
	// Si l'angle est supérieur en absolu, on annule la distance
	// afin de naviguer en priorité en marche avant.
	// TODO : Externalisé le coëficient de départ
	startAngle = 0.45 * Conv.getPiPulse();
}

/* ------------------------------------------------------------------ */
/* ------------------------ BUSINESS METHODS ------------------------ */
/* ------------------------------------------------------------------ */

/*
 * Fonction permettant d'initialiser les composants externe pour le fonctionnement
 */
void RobotManager::init() {
	// Initialisation des cartes codeurs
	resetEncodeurs();

	// Initialisation du contrôle moteurs
	moteurs->init();
	stop();
}

/*
 * Configuration de l'implémentation de la commande des moteurs de propulsion
 */
void RobotManager::setMotorsImpl(AbstractPropulsionMotors * impl) {
	moteurs = impl;
}

/*
 * Configuration de l'implémentation pour la lecture des valeurs codeurs
 */
void RobotManager::setEncodeursImpl(AbstractEncodeurs * impl) {
	enc = impl;
}

/*
 * Commande de reset des valeurs codeurs
 */
void RobotManager::resetEncodeurs() {
	enc->reset();
}

/*
 * Fonction permettant de gérer l'arret des actionneur du manageur
 */
void RobotManager::stop() {
	moteurs->stopAll();
}

/*
 * Cette méthode permet de réaliser les fonctions lié aux déplacements.
 * Le schéduling est assuré par la méthode elle même. De ce fait elle peut
 * être appélé depuis la loop principale.
 */
void RobotManager::process() {
	time = millis();
	if ((time - timePrec) >= asserv.getSampleTimeMs()) {
		timePrec = time;

		// 1. Calcul de la position du robot
		enc->lectureValeurs();
		odom.calculPosition(enc);

		// 2. Calcul des consignes
		calculConsigne();

		// 3.Gestion de l'evittement, de la reprise, et du cycle continue
		if ((*hasObstacle)() && !evittementEnCours) {
			stop();
			asserv.reset(true);
			evittementEnCours = true;

		} else if ((*hasObstacle)() && evittementEnCours) {
			// TODO : Trajectoire d'évittement. Comme le hasObstacle externalisé
			// cette gestion au programme principale

		} else if (!(*hasObstacle)() && evittementEnCours) {
			evittementEnCours = false;

		} else {
			// 3.4.1. Asservissement sur les consignes
			asserv.process(enc, consigneTable.getConsignePolaire());

			// 3.4.2. Envoi aux moteurs
			moteurs->generateMouvement(consigneTable.getConsignePolaire().getCmdGauche(), consigneTable.getConsignePolaire().getCmdDroit());
		}

		// 4. Gestion des flags pour le séquencement du calcul de la position
		gestionFlags();

#ifdef LIB_DEBUG_MODE
		Serial.print(";");Serial.print(trajetEnApproche, DEC);
		Serial.print(";");Serial.print(trajetAtteint, DEC);
		Serial.println();
#endif
	}
}

/*
 * Calcul des consignes d'asservissement
 * -> a : Gestion en fonction de l'odométrie
 * -> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
 */
void RobotManager::calculConsigne() {
	if (!trajetAtteint && (consigneTable.getType() & CONSIGNE_XY)) {
#ifdef LIB_DEBUG_MODE
		Serial.print(";XY");
#endif

		// Calcul en fonction de l'odométrie
		double dX = consigneTable.getPosition().getX() - odom.getPosition().getX();
		double dY = consigneTable.getPosition().getY() - odom.getPosition().getY();

		// Calcul des consignes
		double consDist = calculDistanceConsigne(dX, dY);
		double consOrient = calculAngleConsigne(dX, dY);

		// Calcul du coef d'annulation de la distance
		// Permet d'effectuer d'abord une rotation avant de lancer le déplacement.
		if (abs(consOrient) > startAngle) {
			consDist = consDist * ((startAngle - abs(consOrient)) / startAngle);
		}

		// Sauvegarde des consignes
		consigneTable.getConsignePolaire().setConsigneDistance(consDist);
		consigneTable.getConsignePolaire().setConsigneOrientation(consOrient);
	} else if (!trajetAtteint && (consigneTable.getType() & CONSIGNE_LINE)) {
#ifdef LIB_DEBUG_MODE
		Serial.print(";LINE");
#endif

		// Calcul des consigne pour la ligne

	} else if (!trajetAtteint && (consigneTable.getType() & CONSIGNE_CIRCLE)) {
#ifdef LIB_DEBUG_MODE
		Serial.print(";CIRCLE");
#endif

		// Calcul des consignes pour le cercle

	} else {
#ifdef LIB_DEBUG_MODE
		Serial.print(";DIST_ANGLE");
#endif
		// Calcul par différence vis a vis de la valeur codeur (asservissement de position "basique").
		if (consigneTable.getType() & CONSIGNE_DIST) {
			consigneTable.getConsignePolaire().setConsigneDistance(consigneTable.getConsignePolaire().getConsigneDistance() - enc->getDistance());
		}
		if (consigneTable.getType() & CONSIGNE_ANGLE) {
			consigneTable.getConsignePolaire().setConsigneOrientation(consigneTable.getConsignePolaire().getConsigneOrientation() - enc->getOrientation());
		}
	}

#ifdef LIB_DEBUG_MODE
	Serial.print(";");Serial.print(Conv.pulseToMm(consigneTable.getConsignePolaire().getConsigneDistance()));
	Serial.print(";");Serial.print(Conv.pulseToDeg(consigneTable.getConsignePolaire().getConsigneOrientation()));
#endif
}

/*
 * Méthode de calcul de la consigne d'angle en fonction de dX et dY.
 */
double RobotManager::calculAngleConsigne(double dX, double dY) {
	double alpha = Conv.radToPulse(atan2(Conv.pulseToRad(dY), Conv.pulseToRad(dX)));

	// Ajustement a PI
	return ajusteAngle(alpha - odom.getPosition().getAngle());
}

/**
 * Ajustement de l'angle [ -pi ; pi ]
 */
double RobotManager::ajusteAngle(double angle) {
	if (angle > Conv.getPiPulse()) {
		angle = angle - Conv.get2PiPulse();
	} else if (angle < -Conv.getPiPulse()) {
		angle = angle + Conv.get2PiPulse();
	}

	return angle;
}

/*
 * Méthode de calcul de la consigne de distance en fonction de dX et dY.
 */
double RobotManager::calculDistanceConsigne(double dX, double dY) {
	return sqrt(pow(dX, 2) + pow(dY, 2));
}

/*
 * Méthode permettant de positionner les flags de trajet en fonction des types de consigne
 */
void RobotManager::gestionFlags() {
	// TODO : Voir si il ne serait pas judicieux de traiter le cas des consignes XY avec un rayon sur le point a atteindre.
	if (consigneTable.getConsignePolaire().getFrein()
			&& abs(consigneTable.getConsignePolaire().getConsigneDistance()) < fenetreArretDistance
			&& abs(consigneTable.getConsignePolaire().getConsigneOrientation()) < fenetreArretOrientation) {

		// Notification que le trajet est atteint.
		trajetAtteint = true;
	}

	// Détermination de la présence du robot dans le voisinage du point a atteindre.
	// Information utile uniquement lors de l'enchainement des points.
	if (abs(consigneTable.getConsignePolaire().getConsigneDistance()) < asserv.getFenetreApprocheDistance()
			&& abs(consigneTable.getConsignePolaire().getConsigneOrientation()) < asserv.getFenetreApprocheOrientation()) {

		// Modification du type de consigne pour la stabilisation
		// Lorsque l'on est dans le voisinage du point d'arrivé
		consigneTable.setType(CONSIGNE_DIST | CONSIGNE_ANGLE);

		if (!consigneTable.getConsignePolaire().getFrein()) {
			trajetEnApproche = true;
		}
	}
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

/*
 * Méthode pour passer une consigne d'asservissement
 */
void RobotManager::prepareNextMouvement() {
	// Reset de l'erreur de l'asserv sur le mouvement précédent lorsqu'il
	// s'agit d'un nouveau mouvement au départ vitesse presque nulle
	if (trajetAtteint) {
		asserv.reset();
	}

	// Réinitialisation des infos de trajet
	trajetAtteint = false;
	trajetEnApproche = false;
}

/*
 * Cette méthode permet de mettre à jour la position actuel.
 * Elle est utilisé lors de l'initialisation ou en cas de recalage.
 */
void RobotManager::setPosition(double x, double y, double angle) {
	odom.initOdometrie(x, y, angle);
}

/*
 * Accesseur pour la position courante du robot.
 */
RobotPosition RobotManager::getPosition() {
	return odom.getPosition();
}

/*
 * Mutateur pour spécifier le temps d'asservissement.
 */
void RobotManager::setSampleTime(int sampleTime) {
	asserv.setSampleTimeMs(sampleTime);
}

/*
 * Configuration du PID pour l'asservissement en distance
 */
void RobotManager::setPIDDistance(double kp, double ki, double kd) {
	asserv.setPIDDistance(kp, ki, kd);
}

/*
 * Configuration du PID pour l'asservissement en orientation
 */
void RobotManager::setPIDOrientation(double kp, double ki, double kd) {
	asserv.setPIDOrientation(kp, ki, kd);
}

/*
 * Configuration des rampes d'acceleration
 */
void RobotManager::setRampAcc(double rampDistance, double rampOrientation) {
	asserv.setRampAcc(rampDistance, rampOrientation);
}

/*
 * Configuration des rampes de décéleration
 */
void RobotManager::setRampDec(double rampDistance, double rampOrientation) {
	asserv.setRampDec(rampDistance, rampOrientation);
}

/*
 * Mutateur pour spécifier la vitesse de déplacement du robot
 */
void RobotManager::setVitesse(word vDistance, word vOrientation) {
	consigneTable.getConsignePolaire().setVitesseDistance(vDistance);
	consigneTable.getConsignePolaire().setVitesseOrientation(vOrientation);
}

/*
 * Méthode permettant de donnée une consigne de position sur un point.
 */
void RobotManager::gotoPointMM(double x, double y, boolean frein) {
	consigneTable.getPosition().setAngle(0);
	consigneTable.getPosition().setX(Conv.mmToPulse(x));
	consigneTable.getPosition().setY(Conv.mmToPulse(y));
	consigneTable.setType(CONSIGNE_XY);
	if (frein) {
		consigneTable.enableFrein();
	} else {
		consigneTable.disableFrein();
	}

	prepareNextMouvement();
}

/*
 * Méthode permettant d'aligner le robot sur un angle en fonction du repere
 */
void RobotManager::gotoOrientationDeg(double angle) {
	double newOrientation = angle - Conv.pulseToDeg(odom.getPosition().getAngle());
	tourneDeg(newOrientation);
}

/*
 * Méthode permettant d'aligner le robot face a un point
 */
void RobotManager::alignFrontTo(double x, double y) {
	double dX = Conv.mmToPulse(x) - odom.getPosition().getX();
	double dY = Conv.mmToPulse(y) - odom.getPosition().getY();

	consigneTable.setType(CONSIGNE_DIST | CONSIGNE_ANGLE);
	consigneTable.getConsignePolaire().setConsigneDistance(0);
	consigneTable.getConsignePolaire().setConsigneOrientation(calculAngleConsigne(dX, dY));
	consigneTable.enableFrein();

	prepareNextMouvement();
}

/*
 * Méthode permettant d'aligner le robot dos a un point
 */
void RobotManager::alignBackTo(double x, double y) {
	double dX = Conv.mmToPulse(x) - odom.getPosition().getX();
	double dY = Conv.mmToPulse(y) - odom.getPosition().getY();

	double consigneOrientation = calculAngleConsigne(dX, dY);
	if (consigneOrientation > 0) {
		consigneOrientation = consigneOrientation - Conv.getPiPulse();
	} else {
		consigneOrientation = consigneOrientation + Conv.getPiPulse();
	}

	consigneTable.setType(CONSIGNE_DIST | CONSIGNE_ANGLE);
	consigneTable.getConsignePolaire().setConsigneDistance(0);
	consigneTable.getConsignePolaire().setConsigneOrientation(consigneOrientation);
	consigneTable.enableFrein();

	prepareNextMouvement();
}

/*
 * Méthode permettant d'effectuer un déplacement en avant de distance fixe
 */
void RobotManager::avanceMM(double distance) {
	consigneTable.setType(CONSIGNE_DIST | CONSIGNE_ANGLE);
	consigneTable.getConsignePolaire().setConsigneDistance(Conv.mmToPulse(distance));
	consigneTable.getConsignePolaire().setConsigneOrientation(0);
	consigneTable.enableFrein();

	prepareNextMouvement();
}

/*
 * Méthode permettant d'effectuer un déplacement en arriere de distance fixe
 */
void RobotManager::reculeMM(double distance) {
	avanceMM(-distance);
}

/*
 * Méthode permettant d'effectuer une rotation d'angle fixe
 */
void RobotManager::tourneDeg(double angle) {
	consigneTable.setType(CONSIGNE_DIST | CONSIGNE_ANGLE);
	consigneTable.getConsignePolaire().setConsigneDistance(0);
	consigneTable.getConsignePolaire().setConsigneOrientation(Conv.degToPulse(angle));
	consigneTable.enableFrein();

	prepareNextMouvement();
}

void RobotManager::followLine(double x1, double y1, double x2, double y2) {
	// TO BE IMPLEMENTED
}

void RobotManager::turnAround(double x, double y, double r) {
	// TO BE IMPLEMENTED
}

/*
 * Mutateur pour préciser la fonction permettant d'effectuer la détéction d'obstacle pour l'evittement.
 * Il s'agit d'un pointeur de fonction ayant la signature suivante :
 *
 * 		boolean maFonction();
 *
 */
void RobotManager::setHasObstacle(boolean (*hasObstacle)(void)){
	this->hasObstacle = hasObstacle;
}

/*
 * Accesseur pour savoir si la position demandé est atteinte
 */
boolean RobotManager::getTrajetAtteint() {
	return trajetAtteint;
}

/*
 * Accesseur pour savoir si la position demandé est en approche.
 * Est utilisé pour l'enchainement de point de passage.
 */
boolean RobotManager::getTrajetEnApproche() {
	return trajetEnApproche;
}
