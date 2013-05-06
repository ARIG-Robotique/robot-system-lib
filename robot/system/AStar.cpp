/*
 * 		AStar.cpp
 *
 *  	Created on: 01 janv 2013
 *      	Author: Heiginko
 */

#include "AStar.h"

Astar::Astar( Point pDepart, Point pArriver, Map &map )
{
	_PointDepart = pDepart;
	_PointArriver = pArriver;
	_Map = map;

	//_ListeFermer = Collection();
	//_ListeOuverte = Collection();


}

int Astar::distance( Point *p1, Point *p2){

	return ((p1->getX()-p2->getX())*(p1->getX()-p2->getX())) +  ((p1->getY()-p2->getY()) * (p1->getY()-p2->getY()));

}

void Astar::ajouterCasesAdjacentes(Point * p)
{
	int i,j;
	Point newPoint;
	Noeud newNoeud;

	newNoeud = Noeud();

	/* on met tous les noeud adjacents dans la liste ouverte (+vérif) */
	for (i=(p->getX()-1); i<=p->getX()+1; i++){
		if ((i<0) || (i>=_Map.getTailleX()))  /*On ne prend pas les points qui sont endors de la map*/
			continue;
		for (j=p->getY()-1; j<=p->getY()+1; j++){
			if ((j<0) || (j>=_Map.getTailleY()))   /*On ne prend pas les points qui sont endors de la map*/
				continue;
			if ((i==p->getX()) && (j==p->getY()))  /* case actuelle n, on oublie */
				continue;

			if (_Map.isFranchissable(i,j) == false)
				/* obstace, terrain non franchissable, on oublie */
				continue;

			/*Le point est acceptable*/
			newPoint = Point(i,j);

			if(!_ListeFermer.noeudExiste(newPoint))/* le noeud n'est pas déjà présent dans la liste fermée */
			{

				/* calcul du cout G du noeud en cours d'étude : cout du parent + distance jusqu'au parent */
				newNoeud.setCoutG( _ListeFermer.rechercherNoeud(p)->getCoutG() + this->distance(&newPoint,p));

				/* calcul du cout H du noeud à la destination */
				newNoeud.setCoutH( this->distance(&newPoint,&_PointArriver));
				newNoeud.setPointParent(*p);


				if(_ListeOuverte.noeudExiste(newPoint))
				{
					/* le noeud est déjà présent dans la liste ouverte, il faut comparer les couts */
					if(newNoeud.getCoutF()< _ListeOuverte.rechercherNoeud(newPoint)->getCoutF())
					{
						 /* si le nouveau chemin est meilleur, on met à jour */
						_ListeOuverte.remplacerNoeud(&newNoeud);
					}

					/* le noeud courant a un moins bon chemin, on ne change rien */

				}else{

					/* le noeud n'est pas présent dans la liste ouverte, on l'y ajoute */

					_ListeOuverte.ajouterNoeud(&newNoeud);

				}


			}//if ListeFermer.noeudExiste

		}// deuxieme For
	}// Premier for
}

Point Astar::meilleurNoeud(){

	float mCoutF;
	Point pMeilleur;
	mCoutF = -1;

	while (_ListeOuverte.isFinListe()==false)
	{

		if(_ListeOuverte.getNoeudCourant()->getCoutF()<mCoutF || mCoutF ==-1)
		{
			pMeilleur = _ListeOuverte.getPointCourant();
			mCoutF = _ListeOuverte.getNoeudCourant()->getCoutF();
		}

		_ListeOuverte.suivant();
	}

	return pMeilleur;

}

void Astar::trouverChemin(){




}

void Astar::lancerCalcul(){

	Point pCourant;
	Noeud nCourant;

	pCourant = Point(_PointDepart);

	_ListeFermer = Collection();
	_ListeOuverte = Collection();

	nCourant = Noeud(_PointDepart,pCourant);

	_ListeFermer.ajouterNoeud(&nCourant);

	ajouterCasesAdjacentes(&pCourant);

	 while( !( (pCourant.getX() == _PointArriver.getX() ) && ( pCourant.getY() == _PointArriver.getY() )) && (!(_ListeOuverte.getNbObjects()==0))){


		 pCourant = meilleurNoeud();

		 _ListeFermer.ajouterNoeud( _ListeOuverte.getNoeudCourant() );
		 _ListeOuverte.supprimerNoeudCourant();

		 ajouterCasesAdjacentes(&pCourant);

	 }

}
	






