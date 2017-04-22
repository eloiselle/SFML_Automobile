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
	Texture texture[4];
	RenderTexture;
	Sprite sprJoueur[4];
	Sprite sprJoueur2;
	Event event;
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T

	//Chargement de la texture de l'auto 1
	texture[1].loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));
	//Chargement de la texture de l'auto 2
	texture[2].loadFromFile("blue32x16.png", IntRect(0, 0, 32, 16));

	//Variables
	automobile joueurs[4];

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	int choix = 2;

	for (int i = choix; i > 0; i--)
	{
		//Insertion de la texture dans le sprite et changement du point d'origine
		sprJoueur[i].setTexture(texture[i]);
		sprJoueur[i].setOrigin(12, 8);

		//Initialisation auto
		sprJoueur[i].setPosition(100 * i, 100);
		sprJoueur[i].rotate(joueurs[i].getDegre());
	}

	//Tant que le jeu roule
	while (window.isOpen())
	{
		//Efface l'affichage précédent
		window.clear();

		//Réinitialise l'horloge
		Time tempsDelta = horlogeDelta.restart();

		//Attend les événements
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();

		for (int i = choix; i > 0; i--)
		{
			if (i == 1)
			{
				//Gauche
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					joueurs[i].setVirage(1);

				//Droite
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					joueurs[i].setVirage(2);

				//Nulle
				else
					joueurs[i].setVirage(0);

				//Haut
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					joueurs[i].effectuerVelocite(1, tempsDelta.asMilliseconds());

				//Bas
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					joueurs[i].effectuerVelocite(0, tempsDelta.asMilliseconds());
			}

			else if (i == 2)
			{
				//Gauche
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					joueurs[i].setVirage(1);

				//Droite
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					joueurs[i].setVirage(2);

				//Nulle
				else
					joueurs[i].setVirage(0);

				//Haut
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					joueurs[i].effectuerVelocite(1, tempsDelta.asMilliseconds());

				//Bas
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					joueurs[i].effectuerVelocite(0, tempsDelta.asMilliseconds());
			}

			//Gère les virages
			joueurs[i].effectuerVirage();
			sprJoueur[i].setRotation(joueurs[i].getDegre());
			joueurs[i].setVirage(0);

			//Gère le mouvement du véhicule
			sprJoueur[i].move(
				joueurs[i].getVelociteX() * cos(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds(),
				joueurs[i].getVelociteY() * sin(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds());

			//Affaiblissement de la vélocité
			joueurs[i].velociteAffaiblir();

			window.draw(sprJoueur[i]);
		}

		//Rafraîchi l'affichage
		window.display();
	}
	return 0;
}