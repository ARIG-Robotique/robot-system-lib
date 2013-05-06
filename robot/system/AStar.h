/*
 * AStar.h
 *
 *  Created on: 01 janv 2013
 *      Author: Heiginko
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "../vo/Astar/Collection.h"
#include "../vo/Point.h"
#include "../vo/Map.h"

class Astar 	
{
	private :
		Collection _ListeOuverte;
		Collection _ListeFermer;
		
		Point _PointDepart;
		Point _PointArriver;
		
		Map& _Map;
		
		void ajouterCasesAdjacentes(Point *p);
		int distance(Point *p1 , Point *p2);
		Point meilleurNoeud();
		void trouverChemin();


	public :

		Astar(Point pDepart, Point pArriver, Map &map);
		void lancerCalcul();
		
};

#endif /* ASTAR_H_ */
