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
	RenderWindow window(VideoMode(800, 600), "Vroooom!!!");
	Texture texture;
	RenderTexture;
	Sprite sprite;
	Event event;
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T

	//Variables
	automobile joueur;

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	//Chargement de la texture de l'auto
	texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));

	//Insertion de la texture dans le sprite
	sprite.setTexture(texture);

	//Initialisation  auto
	sprite.setPosition(100, 100);
	sprite.rotate(joueur.getDegree());

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

		//Gère les virages
		joueur.effectuerVirage();
		sprite.setRotation(joueur.getDegree());
		joueur.setVirage(0);

		//Gère le mouvement, et applique une force dépendament du temps qui s'est écoulé (offre une expérience de jeu constante)
		sprite.move(cos(joueur.convertDegreeRadian(joueur.getDegree())) * tempsDelta.asSeconds() , sin(joueur.convertDegreeRadian(joueur.getDegree())) * tempsDelta.asSeconds());

		//Gère l'affichage
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}