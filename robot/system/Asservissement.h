/*
 * Asservissement.h
 *
 *  Created on: 26 d�c. 2012
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
