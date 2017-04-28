/*En-tête du fichier d'en-tête
================================
Auteurs		: Émile Loiselle et Francis Forest
Nom du .h	: piste.h
Date		: 27 avril 2017
But			: Piste de course. Est générée à partir d'un fichier texte.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

//Classe
class piste
{

private:
	string _nom;										//nom de la piste
	Texture _texture;									//texture de la piste
	Sprite _sprite;										//sprite de la piste
	int _nbCollisions;									//nombre de formes convexes de collisions
	ConvexShape _collisions[50];						//formes convexes de collisions (50 est un nombre arbitraire)


public:
	//Constructeur / Déconstructeur
	piste();											//constructeur sans paramètres
	piste(string nomPiste);								//constructeur avec le nom du fichier qui contient les informations pour la création de la piste
	~piste();											//destructeur de la piste

	//Getteur 
	int getNbCollisions();								//get le nombre de formes convexes de collisions
	ConvexShape getCollisions(int i);					//get une forme de collision
	Sprite getSprite();									//get le sprite de la piste
	
	//Setteur
	void setPosition(int x, int y);						//set la position x et y du sprite de la piste

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
	string fichierTexture;

	string nomPiste;									//nom de la piste
	Sprite piste;										//sprite de la piste

	ConvexShape collisions[50];							//formes convexes de collisions
	int nbPoints;										//nombre de points d'une forme de collision

	Vector2f point;										//coordonnées x et y d'un point

	entree.open(nomFichier + ".txt");

	entree >> _nom >> fichierTexture >> _nbCollisions;

	for (int i = 0; i < _nbCollisions; i++)				//pr ch. forme convexe de collision
	{
		entree >> nbPoints;

		_collisions[i].setPointCount(nbPoints);

		for (int j = 0; j < nbPoints; j++)				//pr ch. point de la forme
		{
			entree >> point.x >> point.y;

			_collisions[i].setPoint(j, point);
		}
	}

	_texture.loadFromFile(fichierTexture, IntRect(0, 0, 1024, 768));
	RenderTexture;

	_sprite.setTexture(_texture);

}

//get le nombre de formes convexes de collisions
int piste::getNbCollisions()
{
	return _nbCollisions;
}

//get la forme convexe de collision
ConvexShape piste::getCollisions(int i)
{
	return _collisions[i];
}

//get le sprite de la piste
Sprite piste::getSprite()
{
	return _sprite;
}

//set la position du sprite de la piste selon les coordonnées x et y
void piste::setPosition(int x, int y)
{
	_sprite.setPosition(x, y);
}

