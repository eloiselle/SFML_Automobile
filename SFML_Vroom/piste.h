/*En-tête du fichier d'en-tête
================================
Auteurs		: Émile Loiselle et Francis Forest
Nom du .h	: piste.h
Date		: 27 avril 2017
But			: Piste de course. Est générée à partir d'un fichier texte.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

//Directives au pré-processeur
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "cerclePiste.h"

using namespace std;
using namespace sf;

//Objet
class piste
{

private:
	string _nom;										//nom de la piste
	string _fichierTexture;								//nom du fichier qui contient la texture
	Texture _texture;									//texture de la piste
	Sprite _sprite;										//sprite de la piste
	int _nbCollisions;									//nombre de formes convexes de collisions
	int _nbCercles;
	int _nbPneus;
	ConvexShape _collisions[50];						//formes convexes de collisions (50 est un nombre arbitraire)
	//CircleShape _cercles[50];
	CircleShape _pneus[250];
	cerclePiste _cercles[50];

public:
	//Constructeur / Déconstructeur
	piste();											//constructeur sans paramètres
	piste(string nomPiste);								//constructeur avec le nom du fichier qui contient les informations pour la création de la piste
	~piste();											//destructeur de la piste

	//Getteur 
	int getNbRectangles();								//get le nombre de formes convexes de collisions
	int getNbCercles();
	int getNbPneus();
	ConvexShape getRectangle(int i);					//get une forme de collision
	CircleShape getCercle(int i);
	CircleShape getPneu(int i);
	Sprite getSprite();									//get le sprite de la piste

	//Setteur
	void setPosition(float x, float y);					//set la position x et y du sprite de la piste
	void setNbRectangles(int nbCollisions);				//set le nombre de collisions de la piste

	//Chargement
	void lireFichierEntete(ifstream& entree);			//lecture de l'entête du fichier et affecte le nom du fichier à le nom du fichier de texture en .png
	void chargerPiste(ifstream& entree);				//charge la piste selon les informations du fichier texte, ainsi que toutes les formes convexes de collisions
};

//constructeur sans paramètres
piste::piste()
{
}

//destructeur
piste::~piste()
{
}

//constructeur avec le nom du fichier qui contient les informations pour la création de la piste
piste::piste(string nomFichier)
{
	ifstream entree;									//fichier texte d'entrée

	string nomPiste;									//nom de la piste
	string fichierTexture;								//nom du fichier texte qui contient la texture
	
	Sprite piste;										//sprite de la piste

	ConvexShape rectangles[50];							//formes convexes de collisions

	Vector2f point;										//coordonnées x et y d'un point

	_nom = nomFichier;
	fichierTexture = _nom + ".png";

	entree.open(_nom + ".txt");
	//entree >> _nbCollisions;							//lecture entete

	chargerPiste(entree);

	_texture.loadFromFile(fichierTexture, IntRect(0, 0, 1280, 768));
	
	_sprite.setTexture(_texture);

}

//get le nombre de formes convexes de collisions
int piste::getNbRectangles()
{
	return _nbCollisions;
}

int piste::getNbCercles()
{
	return _nbCercles;
}

int piste::getNbPneus()
{
	return _nbPneus;
}

//get la forme convexe de collision
ConvexShape piste::getRectangle(int i)
{
	return _collisions[i];
}

CircleShape piste::getCercle(int i)
{
	return _cercles[i].cercle;
}

CircleShape piste::getPneu(int i)
{
	return _pneus[i];
}

//get le sprite de la piste
Sprite piste::getSprite()
{
	return _sprite;
}

//set la position du sprite de la piste selon les coordonnées x et y
void piste::setPosition(float x, float y)
{
	_sprite.setPosition(x, y);
}

//setle nombre de formes de collisions de la piste
void piste::setNbRectangles(int nbCollisions)
{
	_nbCollisions = nbCollisions;
}

//lecture de l'entête du fichier 
void piste::lireFichierEntete(ifstream& entree)
{
	
}

//charge la piste selon les informations du fichier texte, ainsi que toutes les formes convexes de collisions
void piste::chargerPiste(ifstream& entree)
{
	int nbPoints;											//nb de points par forme
	Vector2f point;											//coordonnées d'un point

	//for (int i = 0; i < _nbCollisions; i++)					//pr ch. forme convexe de collision
	//{
	//	entree >> nbPoints;

	//	_collisions[i].setPointCount(nbPoints);

	//	for (int j = 0; j < nbPoints; j++)					//pr ch. point de la forme
	//	{
	//		entree >> point.x >> point.y;

	//		_collisions[i].setPoint(j, point);
	//	}

	//	_collisions[i].setFillColor(Color::Transparent);	//a titre de visibilitépour tests
	//	_collisions[i].setOutlineColor(Color::White);
	//	_collisions[i].setOutlineThickness(4);
	//}

	entree >> _nbCercles;

	for (int i = 0; i < _nbCercles; i++)
	{
		int x;
		int y;
		int rad;

		int hg, hd, bd, bg = 0;

		entree >> x >> y >> rad >> hg >> hd >> bd >> bg;

		_cercles[i].setAll(hg, hd, bd, bg);
		

		_cercles[i].cercle.setOrigin(rad, rad);
		_cercles[i].cercle.setPosition(x, y);
		_cercles[i].cercle.setRadius(rad);
		_cercles[i].cercle.setFillColor(Color::Transparent);
		_cercles[i].cercle.setOutlineColor(Color::White);
		_cercles[i].cercle.setOutlineThickness(2);

	}

	entree >> _nbPneus;

	for (int i = 0; i < _nbPneus; i++)
	{
		int x;
		int y;
		int rad;

		int buffer;

		entree >> x >> y >> rad;
		
		for (int j = 0; j < 4; j++)
		{
			entree >> buffer;
		}

		_pneus[i].setOrigin(rad, rad);
		_pneus[i].setPosition(x, y);
		_pneus[i].setRadius(rad);
		_pneus[i].setFillColor(Color::Transparent);
		_pneus[i].setOutlineColor(Color::White);
		_pneus[i].setOutlineThickness(2);
	}

	entree >> _nbCollisions;

	for (int i = 0; i < _nbCollisions; i++)
	{
		int nbPoints;

		entree >> nbPoints;

		_collisions[i].setPointCount(nbPoints);

		for (int j = 0; j < nbPoints; j++)
		{
			int x;
			int y;

			entree >> x >> y;

			_collisions[i].setPoint(j, Vector2f(x, y));
			_collisions[i].setFillColor(Color::Transparent);
			_collisions[i].setOutlineColor(Color::White);
			_collisions[i].setOutlineThickness(2);

		}
	}
}