#include <Arduino.h>
#include <Wire.h>

#include <robot/system/capteurs/Board2007NoMux.h>
#include <robot/system/capteurs/Board2007Define.h>
#include <robot/system/encoders/ARIGEncodeurs.h>
#include <robot/system/motors/MD22.h>
#include <robot/system/servos/SD21.h>
#include <robot/RobotManager.h>
#include <utils/Convertion.h>
#include <utils/I2CUtils.h>

#include "define.h"

// Prototype des fonctions principale
void setup();
void matchLoop();
void startFunnyAction();
void endMatch();
void nextEtape();

// Prototype des fonctions business
void heartBeat();
void brasHome();
void closeDoors();
void openVanne();
void closeVanne();
void startGonfleur();
void stopGonfleur();
boolean hasObstacle();
boolean isInPresentArea();

// Heartbeat variables
int heartTimePrec;
int heartTime;
boolean heart;

// Classe de convertion (pour 2000 CPR, rayon 19,9 et entraxe 161)
Convertion Conv = Convertion(15.9954716675272, 44.9469570072585);

// Classe de gestion du robot (asserv, odométrie, pathfinding, evittement, etc...)
RobotManager robotManager = RobotManager();
Board2007NoMux capteurs = Board2007NoMux();

// I2C Boards
SD21 servoManager = SD21(SD21_ADD_BOARD);
MD22 motorsPropulsion = MD22(MD22_ADD_BOARD, 0, 0);
ARIGEncodeurs encodeurs = ARIGEncodeurs(ENCODEUR_GAUCHE_BOARD, ENCODEUR_DROIT_BOARD);

// Gestion des étapes
int gestEtapes;

// Position des zones cadeaux pour les servos
const int cdx1Center = 600;
const int cdx2Center = 1200;
const int cdx3Center = 1800;
const int cdx4Center = 2400;
const int cdxStartOffset = 150;
const int cdxStopOffset = 220;

// ------------------------ //
// Configuration des rampes //
// ------------------------ //
const int rampAccDistance = 800.0; // en mm/s2
const int rampDecDistance = 800.0; // en mm/s2

const double rampAccOrientation = 800.0; // en mm/s2
const double rampDecOrientation = 800.0; // en mm/s2

// -------------- //
// Parametres PID //
// -------------- //
const double kpDistance = 0.30;
const double kiDistance = 0.20;
const double kdDistance = 0.90;

const double kpOrientation = 1.00;
const double kiOrientation = 0.10;
const double kdOrientation = 1.00;

// Constantes d'ajustement pour les roues folles
const double coefRoueDroite = 1.00;
const double coefRoueGauche = 1.00;

// Variable pour l'équipe
byte team;

// ------------------------------------------------------- //
// ------------------------- MAIN ------------------------ //
// ------------------------------------------------------- //

// Methode de configuration pour le fonctionnement du programme
void setup() {
	// ------------------------------------------------------------- //
	// Initialisation du port série en debug seulement (cf define.h) //
	// ------------------------------------------------------------- //
#ifdef DEBUG_MODE
	Serial.begin(115200);
	Serial.println(" == INITIALISATION ROBOT RECYCLE ==");
#endif

	// ---------- //
	// Config I2C //
	// ---------- //
	Wire.begin();
#ifdef DEBUG_MODE
	Serial.println(" - I2C [OK] (Master)");
#endif
	i2cUtils.pullup(false);
	i2cUtils.fastSpeed(false);

	// Tempo attente pour boot autres cartes
	delay(4000);
	byte nbDevices = i2cUtils.scan();
	if (nbDevices != NB_I2C_DEVICE) {
#ifdef DEBUG_MODE
		Serial.println(" [ ERROR ] Il manque des périphériques I2C. Check the connections");
#endif
		// Il manque des périphérique on bloque tout
		while(1 == 1);
	}

	// ------------- //
	// Servo manager //
	// ------------- //
#ifdef DEBUG_MODE
	servoManager.printVersion();
#endif

	// Configuration des vitesses
	servoManager.setSpeed(SERVO_BRAS_DROIT, SPEED_BRAS);
	servoManager.setSpeed(SERVO_BRAS_GAUCHE, SPEED_BRAS);
	servoManager.setSpeed(SERVO_PORTE_DROITE, SPEED_PORTE);
	servoManager.setSpeed(SERVO_PORTE_GAUCHE, SPEED_PORTE);

	// --------------------- //
	// Moteurs de propulsion //
	// --------------------- //
#ifdef DEBUG_MODE
	motorsPropulsion.printVersion();
#endif
	motorsPropulsion.assignMotors(ASSIGN_MOTOR_2, ASSIGN_MOTOR_1);

	// --------- //
	// Encodeurs //
	// --------- //
	encodeurs.setCoefs(coefRoueGauche, coefRoueDroite);

	// ------------- //
	// Robot manager //
	// ------------- //
	robotManager.setMotorsImpl(&motorsPropulsion);
	robotManager.setEncodeursImpl(&encodeurs);
	robotManager.setHasObstacle(hasObstacle);
	robotManager.setSampleTime(TIME_ASSERV_MS);
	robotManager.setPIDDistance(kpDistance, kiDistance, kdDistance);
	robotManager.setPIDOrientation(kpOrientation, kiOrientation, kdOrientation);
	robotManager.setRampAcc(rampAccDistance, rampAccOrientation);
	robotManager.setRampDec(rampDecDistance, rampDecOrientation);
	robotManager.init();

#ifdef DEBUG_MODE
	Serial.println(" - Robot manager [OK]");
#endif

	// -- //
	// IO //
	// -- //

	// Inputs
	capteurs.setPinForCapteur(TIRETTE, TIRETTE_PIN, true);
	capteurs.setPinForCapteur(EQUIPE, EQUIPE_PIN, true);
	capteurs.setPinForCapteur(LATERAL_ARRIERE_DROIT, LATERAL_ARRIERE_DROIT_PIN, true, true);
	capteurs.setPinForCapteur(LATERAL_ARRIERE_GAUCHE, LATERAL_ARRIERE_GAUCHE_PIN, true, true);
	capteurs.setPinForCapteur(LATERAL_AVANT_DROIT, LATERAL_AVANT_DROIT_PIN, true, true);
	capteurs.setPinForCapteur(LATERAL_AVANT_GAUCHE, LATERAL_AVANT_GAUCHE_PIN, true, true);
	capteurs.setPinForCapteur(ARRIERE_DROIT, ARRIERE_DROIT_PIN, true, true);
	capteurs.setPinForCapteur(ARRIERE_GAUCHE, ARRIERE_GAUCHE_PIN, true, true);
	capteurs.setPinForCapteur(AVANT_DROIT, AVANT_DROIT_PIN, true, true);
	capteurs.setPinForCapteur(AVANT_GAUCHE, AVANT_GAUCHE_PIN, true, true);
#ifdef DEBUG_MODE
	Serial.println(" - Capteurs [OK]");
#endif

	// Outputs
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(GONFLEUR, OUTPUT);
	pinMode(ELECTRO_VANNE, OUTPUT);
#ifdef DEBUG_MODE
	Serial.println(" - Outputs [OK]");
#endif

	// Configuration par défaut des variables
	heartTime = heartTimePrec = millis();
	heart = false;

	brasHome();
	closeDoors();
	stopGonfleur();
	closeVanne();

	// Ini Gestion Etapes
	gestEtapes = 0;
}

// Point d'entrée du programme
int main(void) {
	// Initialisation du SDK Arduino. A réécrire si on veut customiser tout le bouzin.
	init();

	// Initialisation de l'application
	setup();

#ifdef DEBUG_MODE
	// Affichage de la couleur de l'équipe
	team = capteurs.readCapteurValue(EQUIPE);
	Serial.print(" ========================= > ");
	Serial.println((team == ROUGE) ? "ROUGE" : "BLEU");

	// Procédure d'initialisation Robot (calage, tirette, etc).
	Serial.println(" == INIT MATCH ==");
#endif

	if (!capteurs.readCapteurValue(TIRETTE)) {
#ifdef DEBUG_MODE
		Serial.println(" -> /!\\ La tirette n'est pas présente il faut d'abord la mettre !");
		while(!capteurs.readCapteurValue(TIRETTE));
		delay(1000);
#endif
	}

#ifdef DEBUG_MODE
	Serial.println(" -> Attente depart tirette ...");
#endif

	while(capteurs.readCapteurValue(TIRETTE)) {
		heartBeat();
		if (Serial.available()) {
			if (Serial.read() == 's') { // La touche s de la liaison série est égal à la tirette
				break;
			}
		}
	}

	// Démarrage du comptage
	unsigned long startMatch = millis();
	unsigned long t;

	// Reset des valeurs codeurs lors des différents mouvements de positionnement
	robotManager.resetEncodeurs();

	team = capteurs.readCapteurValue(EQUIPE);
#ifdef DEBUG_MODE
	Serial.print(" - Equipe : ");
#endif
	if (team == ROUGE) {
#ifdef DEBUG_MODE
		Serial.println("ROUGE");
#endif
		robotManager.setPosition(Conv.mmToPulse(2850), Conv.mmToPulse(250), Conv.degToPulse(135));
	} else {
#ifdef DEBUG_MODE
		Serial.println("BLEU");
#endif
		robotManager.setPosition(Conv.mmToPulse(150), Conv.mmToPulse(250), Conv.degToPulse(45));
	}

	// Pour tester //
	// TODO : A supprimer
	//robotManager.setPosition(0, 0, 0);
	robotManager.setPosition(Conv.mmToPulse(300), Conv.mmToPulse(300), Conv.degToPulse(90));

#ifdef DEBUG_MODE
	Serial.println(" == DEBUT DU MATCH ==");

	// En tête de log
	Serial.println("Gauche;Droit;X;Y;A;Type;Cons. Dist.;Cons. Orient.;PID Dist. setPoint;PID Dist. In;PID Dist. sumErr;PID Dist. Out;PID O setPoint;PID O In;PID O sumErr;PID O Out;Approche;Atteint");
#endif

	boolean g = false;
	do {
		heartBeat();
		matchLoop();

		// Gestion du temps
		t = millis();

		if (t - startMatch >= PREPARE_GONFLAGE && !g) {
			startGonfleur();
			g = true;
		}
	} while(t - startMatch <= TPS_MATCH);

	// Plus de mouvement on arrete les moteurs.
	robotManager.stop();

#ifdef DEBUG_MODE
	Serial.println(" == FIN DU MATCH ==");
#endif
	// Attente du temps de démarrage de la fin du match
	while(millis() - startMatch <= START_GONFLAGE);
	startFunnyAction();
	while(millis() - startMatch <= END_TOUT);
	endMatch();

	// Action de clignotement de la la led built-in pour montrer que la programme fonctionne toujours.
	while(true) {
		heartBeat();
	}
}

// ---------------------------------------------------------------------------- //
// Méthode appelé encore et encore, tant que le temps du match n'est pas écoulé //
// ---------------------------------------------------------------------------- //
void matchLoop() {
	if(robotManager.getTrajetAtteint() || robotManager.getTrajetEnApproche()) {
		nextEtape();
	}

	// Processing de l'asservissement.
	robotManager.process();
}

void nextEtape(){
	switch (gestEtapes) {
	// Pour tester les valeurs de convertions
	case 0 :
		robotManager.setVitesse(300.0, 600.0);
		robotManager.gotoPointMM(300.0, 2500.0, false);
		gestEtapes++;
		break;
	case 1 :
		robotManager.setVitesse(300.0, 600.0);
		robotManager.gotoPointMM(1800.0, 2800.0, false);
		gestEtapes++;
		break;
	case 2 :
		robotManager.setVitesse(300.0, 600.0);
		robotManager.gotoPointMM(2000.0, 300.0, false);
		gestEtapes++;
		break;
	case 3 :
		robotManager.setVitesse(100.0, 300.0);
		robotManager.gotoPointMM(300.0, 300.0, true);
		gestEtapes++;
		break;
	}
}

// ----------------------------------- //
// Méthode appelé pour la fin du match //
// ----------------------------------- //
void startFunnyAction() {
#ifdef DEBUG_MODE
	Serial.println(" == START FUNNY ACTION ==");
#endif
	startGonfleur();
	openVanne();
}

void endMatch() {
#ifdef DEBUG_MODE
	Serial.println(" == FIN FUNNY ACTION ==");
#endif
	stopGonfleur();
	closeVanne();
}

// ------------------------------------------------------- //
// -------------------- BUSINESS METHODS ----------------- //
// ------------------------------------------------------- //

/*
 * Méthode pour le battement de coeur
 */
void heartBeat() {
	heartTime = millis();
	if (heartTime - heartTimePrec > 1000) {
		heartTimePrec = heartTime;
		digitalWrite(LED_BUILTIN, (heart) ? HIGH : LOW);
		heart = !heart;
	}
}

/*
 * Méthode pour placer les bras à la maison
 */
void brasHome() {
	servoManager.setPosition(SERVO_BRAS_DROIT, BRAS_DROIT_HOME);
	servoManager.setPosition(SERVO_BRAS_GAUCHE, BRAS_GAUCHE_HOME);
}

/*
 * Méthode pour fermer les portes
 */
void closeDoors() {
	servoManager.setPosition(SERVO_PORTE_DROITE, PORTE_DROITE_CLOSE);
	servoManager.setPosition(SERVO_PORTE_GAUCHE, PORTE_GAUCHE_CLOSE);
}

/*
 * Ouverture de l'electrovanne
 */
void openVanne() {
	digitalWrite(ELECTRO_VANNE, HIGH);
}

/*
 * Fermeture de la vanne
 */
void closeVanne() {
	digitalWrite(ELECTRO_VANNE, LOW);
}

/*
 * Allumage du gonfleur
 */
void startGonfleur() {
	digitalWrite(GONFLEUR, HIGH);
}

/*
 * Arret du gonfleur
 */
void stopGonfleur() {
	digitalWrite(GONFLEUR, LOW);
}

/*
 * Méthode retournant l'information de présence d'un obstacle (adversaire ???)
 */
boolean hasObstacle() {
	return false;
/*
	// Juste les deux de devant et les deux de dérriere
	boolean obstacle = capteurs.readCapteurValue(AVANT_DROIT)
			|| capteurs.readCapteurValue(AVANT_GAUCHE)
			|| capteurs.readCapteurValue(ARRIERE_DROIT)
			|| capteurs.readCapteurValue(ARRIERE_GAUCHE);

	if (isInPresentArea()) {
		if (team == BLEU) {
			// Les cadeaux sont a droite
			obstacle = obstacle || capteurs.readCapteurValue(LATERAL_AVANT_GAUCHE)
						|| capteurs.readCapteurValue(LATERAL_ARRIERE_GAUCHE);
		} else if (team == ROUGE) {
			// Les cadeaux sont a gauche
			obstacle = obstacle || capteurs.readCapteurValue(LATERAL_AVANT_DROIT)
						|| capteurs.readCapteurValue(LATERAL_ARRIERE_DROIT);
		}
	} else {
		// Pas dans la zone cadeaux, on active tous les capteurs avant et arriere
		obstacle = obstacle || capteurs.readCapteurValue(LATERAL_AVANT_GAUCHE)
				|| capteurs.readCapteurValue(LATERAL_AVANT_DROIT)
				|| capteurs.readCapteurValue(LATERAL_ARRIERE_GAUCHE)
				|| capteurs.readCapteurValue(LATERAL_ARRIERE_DROIT);
	}
	return obstacle;
*/
}

boolean isInPresentArea() {
	return false;
}
