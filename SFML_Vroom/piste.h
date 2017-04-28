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

	ConvexShape collisions[50];							//formes convexes de collisions
	int nbPoints;										//nombre de points d'une forme de collision

	Vector2f point;										//coordonnées x et y d'un point

	_nom = nomFichier;
	fichierTexture = _nom + ".png";

	entree.open(_nom + ".txt");
	entree >> _nbCollisions;							//lecture entete

	chargerPiste(entree);

	_texture.loadFromFile(fichierTexture, IntRect(0, 0, 1024, 768));
	
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

//lecture de l'entête du fichier 
void piste::lireFichierEntete(ifstream& entree)
{
	
}

//charge la piste selon les informations du fichier texte, ainsi que toutes les formes convexes de collisions
void piste::chargerPiste(ifstream& entree)
{
	int nbPoints;											//nb de points par forme
	Vector2f point;											//coordonnées d'un point

	for (int i = 0; i < _nbCollisions; i++)					//pr ch. forme convexe de collision
	{
		entree >> nbPoints;

		_collisions[i].setPointCount(nbPoints);

		for (int j = 0; j < nbPoints; j++)					//pr ch. point de la forme
		{
			entree >> point.x >> point.y;

			_collisions[i].setPoint(j, point);
		}

		_collisions[i].setFillColor(Color::Transparent);	//a titre de visibilitépour tests
		_collisions[i].setOutlineColor(Color::White);
		_collisions[i].setOutlineThickness(4);
	}
}