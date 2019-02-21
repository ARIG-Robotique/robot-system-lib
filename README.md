(c) Association ARIG.

Projet contenant l'ensemble des éléments de pilotage des robots pour la coupe.

* comm
    * I2C

* filters
    * PID_v1 : Librairie Arduino PID.
	* QuadRamp : Filtre permettant de limit� les consigne d'asservissement selon un profil trapézoïdale.

* robot
    * RobotManager : Systeme central de gestion des autres resources.
    * vo
	    * RobotPosition : Objet representatif de la position d'un robot.
	    * ConsignePolaire : Objet représentant une consigne pour l'asservissement polaire.
	* system
        * Asservissement : Classe réalisant l'algorithme d'asservissement. Il s'agit d'une implémentation polaire.
        * Encodeurs : Classe de gestions des valeurs des encodeurs. La récupération est effectué en I2C.
        * MD22Moteurs : Classe de gestion de la carte de pilotage moteurs Devantech MD22.
        * Odometrie : Classe réalisant les calcul odométrique
        * PathFinding : Classe permettant de réaliser le calcul des points de passage. Algorithme A*.

* utils
	* Convertion : Classe utilitaire permettant de réaliser les diverses convertion entre les systéme de mesures.
