/*
 * Asservissement.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

#include "../vo/ConsignePolaire.h"

class Asservissement {
public:
	Asservissement();
	virtual ~Asservissement();

	void process(ConsignePolaire *);
};

#endif /* ASSERVISSEMENT_H_ */
