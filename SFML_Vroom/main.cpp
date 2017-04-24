/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Directives au pré-processeur
#include <SFML/Graphics.hpp>
#include "auto.h"
using namespace sf;

//Programme principal
int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 720), "Vroooom!!!");
	Texture texture;
	Texture textureMap;
	RenderTexture;
	Sprite sprite;
	Sprite map;
	Event event;
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T

	//Variables
	automobile joueur;

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	//Chargement de la texture de l'auto
	texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));
	
	textureMap.loadFromFile("map2.png", IntRect(0, 0, 1280, 720));

	//Insertion de la texture dans le sprite et changement du point d'origine
	sprite.setTexture(texture);
	sprite.setOrigin(12, 8);

	map.setTexture(textureMap);

	//Initialisation auto
	sprite.setPosition(100, 100);
	sprite.rotate(joueur.getDegre());

	map.setPosition(0, 0);

	//Tant que le jeu roule
	while (window.isOpen())
	{
		//Réinitialise l'horloge
		Time tempsDelta = horlogeDelta.restart();

		//Attend les événements
		while (window.pollEvent(event))
			if(event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();

		//Gauche
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			joueur.setVirage(1);

		//Droite
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			joueur.setVirage(2);

		//Nulle
		else
			joueur.setVirage(0);

		//Haut
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			joueur.effectuerVelocite(1, tempsDelta.asMilliseconds());

		//Bas
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			joueur.effectuerVelocite(0, tempsDelta.asMilliseconds());

		//Gère les virages
		joueur.effectuerVirage();
		sprite.setRotation(joueur.getDegre());
		joueur.setVirage(0);

		//Gère le mouvement du véhicule
		sprite.move(
			joueur.getVelociteX() * cos(
				joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds() , 
			joueur.getVelociteY() * sin(
				joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds());

		//Affaiblissement de la vélocité
		joueur.velociteAffaiblir();

		//Gère l'affichage
		window.clear();
		window.draw(map);
		window.draw(sprite);
		window.display();
	}
	return 0;
}