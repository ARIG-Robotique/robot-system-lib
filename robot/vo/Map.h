/*
 * Map
 *
 *  Created on: 1 mai 2013
 *      Author: heiGinko
 */

#ifndef MAP_
#define MAP_

#include <Arduino.h>

class Map
{
	public :
		Map(int tailleX, int tailleY);

		int getTailleX();
		int getTailleY();

		void setInfranchissable(int x, int y);
		void setFranchissable(int x, int y);
		void setTemporairementInfranchissable(int x, int y);
		void setRestoreEtat(int x, int y);

		bool isFranchissable(int x, int y);

	private :
		int _TailleX;
		int _TailleY;
		byte **_Tableau;

};


#endif /* MAP_ */
