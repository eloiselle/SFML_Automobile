/*En-tête du fichier d'en-tête
================================
Auteurs		: Émile Loiselle et Francis Forest
Nom du .h	: piste.h
Date		: 27 avril 2017
But			: Traffics Lights. Permet au joueur de s'avoir quand la course débute. De couleur rouge, change à jaune puis à vert 
			  selon le temps de jeu écoulé.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

//Directives au pré-processeur
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

//Objet
class trafficLights
{
private:
	string _nom;							//nom du trafficLights
	Texture _texture;						//texture du trafficLights
	Sprite _sprite;							//sprite du trafficLights
						
public:
	trafficLights();						//Constructeur sans paramètre. Charge la texture de la lumière rouge et la met dans le sprite
	~trafficLights();						//destructeur

	void setPosition(int x, int y);			//set la position du sprite

	void changerLumiere(Clock clock);		//change la couleur de la lumière selon le temps de jeu passé en paramètre

	Sprite getSprite();						//fet le sprite

};

//Constructeur sans paramètre. Charge la texture de la lumière rouge et la met dans le sprite
trafficLights::trafficLights()
{
	_nom = "trafficLights";

	_texture.loadFromFile(_nom + "rouge.png", IntRect(0, 0, 200, 137));
	

	_sprite.setTexture(_texture);
}

//destructeur
trafficLights::~trafficLights()
{
}

//change la couleur de la lumière selon le temps de jeu passé en paramètre
void trafficLights::changerLumiere(Clock clock)
{
	Time temps;											//evalue temps passé

	temps = clock.getElapsedTime();
	
	if (temps.asSeconds() <= 3)							//lumière rouge
	{
		_texture.loadFromFile(_nom + "Rouge.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}

	else if (temps.asSeconds() <= 5)					//lumière jaune
	{
		_texture.loadFromFile(_nom + "Jaune.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}
	else if (temps.asSeconds() <= 6)					//lumière verte
	{
		_texture.loadFromFile(_nom + "Verte.png", IntRect(0, 0, 200, 137));
		

		_sprite.setTexture(_texture);
	}
}

//get le sprite
Sprite trafficLights::getSprite()
{
	return _sprite;
}

//set la position du sprite
void trafficLights::setPosition(int x, int y)
{
	_sprite.setPosition(x, y);
}
