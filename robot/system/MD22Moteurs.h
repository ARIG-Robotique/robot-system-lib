/*
 * MD22Moteurs.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef MD22MOTEURS_H_
#define MD22MOTEURS_H_

class MD22Moteurs {
public:
	MD22Moteurs();
	virtual ~MD22Moteurs();

	void generateMouvement(int gauche, int droit);
	void init();
	void printVersion();
private:
	bool alternate;

	void moteurGauche(int);
	void moteurDroit(int);
};

#endif /* MD22MOTEURS_H_ */
