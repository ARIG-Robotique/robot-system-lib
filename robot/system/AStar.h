/*
 * AStar.h
 *
 *  Created on: 01 janv 2013
 *      Author: Heiginko
 */

#ifndef ASTAR_H_
#define ASTAR_H_


class Point 
{
	public :
		Point();
		Point(int x, int y);
		Point(Point *p);
		int getX();
		int getY();
		void setX(int x);
		void setY (int y);
	private :
		int _X;
		int _Y;
};
	
class Noeud
{
	public :
		Noeud();
		Noeud(point p);
		Noeud(point p,point pParent);
		Point getPoint();
		Point getPointParent();
		void setPoint(Point p);
		void setPointParent(Point pParent);
		int getCoutG();
		void setCoutG();
		int getCoutH();
		void setCoutH();
		int getCoutF();
		void setCoutF();
	private :
		Point _Point;
		Point _PointParent;
		float _CoutG;
		float _CoutH;
		float _CoutF;
};

class ListeObjects
{
	private :
		ObjectListe * _PremierObject;
		ObjectListe * _DernierObject;
		ObjectListe * _CourantObject;
		int nbObjects;
		int indexCourant;
		//ObjectListe * rechercherObject(Noeud *n);
		ObjectListe * recupererObject();
		
	public :
		ListeObjects();
		boolean isFinListe();
		boolean isDebutListe();
		void suivant();
		void precedent();
		Noeud * recupererObject(Noeud *n);
		//ObjectListe* rechercherObject(ObjectListe n);
		//boolean ObjectExist(ObjectListe n);
		boolean ajouterNoeud(Noeud *n);
};
		
class ObjectListe
{
	private : 
		Noeud _Noeud;
		ObjectListe *_ObjectSuivant;
		ObjectListe *_ObjectPrecedant;
		int _Index;
	
	public :
		ObjectListe()
		ObjectListe( ObjectListe *suivant, ObjectListe *precedant, Noeud n);
		
		ObjectListe* getObjectSuivant();
		ObjectListe* getObjectPrecedant();
		void setObjectSuivant(ObjectListe * suivant);
		void setObjectPrecedent(ObjectListe * precedant);
		
		Noeud getNoeud();
		void setNoeud(Noeud n);
		
		void setIndex(int i);
		int getIndex();
};

class Astar 	
{
	private :
		ListeObjects _ListeOuverte;
		ListeObjects _ListeFermer;
		
	public :
		Astart(Point *pDepart, Point *pArriver, int * map)
		void lancerCalcul();
		
};

#endif /* ASTAR_H_ */
