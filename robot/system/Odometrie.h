/*
 * Odometrie.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ODOMETRIE_H_
#define ODOMETRIE_H_

#include "Encodeurs.h"

class Odometrie {
public:
	Odometrie();
	virtual ~Odometrie();

	void calculPosition(Encodeurs enc);
};

#endif /* ODOMETRIE_H_ */
