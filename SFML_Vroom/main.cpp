/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Lien de discussion instantané: https://tlk.io/sfml_automobile

//Pseudo-code drifts

//Directives au pré-processeur
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "auto.h"
#include "menu.h"
using namespace sf;

//Programme principal
int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 720), "Vroooom!!!");
	Texture texture;
	RenderTexture;
	Sprite sprJoueur[4];
	Event event;
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	//Variables
	int nbJoueurs = 4;

	automobile joueurs[4];

	joueurs[0].setCouleur(0, 255, 0);
	joueurs[1].setCouleur(255, 0, 0);
	joueurs[2].setCouleur(0, 255, 255);
	joueurs[3].setCouleur(255, 255, 0);

	joueurs[0].setKeys(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
	joueurs[1].setKeys(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
	joueurs[2].setKeys(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L);
	joueurs[3].setKeys(Keyboard::Home, Keyboard::End, Keyboard::Delete, Keyboard::PageDown);

	for (int i = 0; i < nbJoueurs; i++)
	{
		//Chargement de la texture pour l'auto spécifiée
		texture.loadFromFile("car.png");
		sprJoueur[i].setTexture(texture);
		sprJoueur[i].setOrigin(12, 8);
		sprJoueur[i].setColor(Color(joueurs[i - 1].getRed(), joueurs[i - 1].getGreen(), joueurs[i - 1].getBlue()));

		//Initialisation auto
		sprJoueur[i].setPosition(100 + (100 * i), 100);
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
			if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();

		for (int i = 0; i < nbJoueurs; i++)
		{
			//Gauche
			if (Keyboard::isKeyPressed(joueurs[i].getLeft()))
				joueurs[i].setVirage(1);

			//Droite
			else if (Keyboard::isKeyPressed(joueurs[i].getRight()))
				joueurs[i].setVirage(2);

			//Nulle
			else
				joueurs[i].setVirage(0);

			//Haut
			if (Keyboard::isKeyPressed(joueurs[i].getUp()))
			{
				joueurs[i].changerDirection(1);
				joueurs[i].effectuerVelocite(tempsDelta.asMilliseconds());
			}

			//Bas
			if (Keyboard::isKeyPressed(joueurs[i].getDown()))
			{
				joueurs[i].changerDirection(0);
				joueurs[i].effectuerVelocite(tempsDelta.asMilliseconds());
			}

			//Gère les collisions entre chaque autos
			for (int j = 0; j < nbJoueurs; j++)
			{
				if (i != j && sprJoueur[i].getGlobalBounds().intersects(sprJoueur[j].getGlobalBounds()))
				{
					joueurs[i].collision();
					break;
				}

				if (j == nbJoueurs-1)
				{
					//Gère les virages
					joueurs[i].effectuerVirage();
					sprJoueur[i].setRotation(joueurs[i].getDegre());
					joueurs[i].setVirage(0);
				}
			}

			//Gère le mouvement du véhicule
			sprJoueur[i].move(
				joueurs[i].getVelociteX() * cos(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds(),
				joueurs[i].getVelociteY() * sin(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds());

			//Affaiblissement de la vélocité
			joueurs[i].velociteAffaiblir(0);

			window.draw(sprJoueur[i]);
		}

		//Rafraîchi l'affichage
		window.display();
	}
	return 0;
}