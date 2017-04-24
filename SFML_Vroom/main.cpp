/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Lien de discussion instantané: https://tlk.io/sfml_automobile

//Directives au pré-processeur
#include <SFML/Graphics.hpp>
#include "auto.h"
using namespace sf;

//Programme principal
int main()
{
	int nbJoueurs = 2;

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
	automobile joueurs[4];

	joueurs[0].setCouleur(255, 0, 255);
	joueurs[1].setCouleur(255, 0, 0);
	joueurs[2].setCouleur(0, 0, 255);
	joueurs[3].setCouleur(0, 255, 0);

	for (int i = 1; i < nbJoueurs + 1; i++)
	{
		//Chargement de la texture pour l'auto spécifiée
		texture.loadFromFile("car.png");
		sprJoueur[i].setTexture(texture);
		sprJoueur[i].setOrigin(12, 8);
		sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

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

		for (int i = nbJoueurs; i > 0; i--)
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

			if (sprJoueur[1].getGlobalBounds().intersects(sprJoueur[2].getGlobalBounds()))
			{
				joueurs[1].collision();
			}

			if (sprJoueur[2].getGlobalBounds().intersects(sprJoueur[1].getGlobalBounds()))
			{
				joueurs[2].collision();
			}

			else
			{
				//Gère les virages
				joueurs[i].effectuerVirage();
				sprJoueur[i].setRotation(joueurs[i].getDegre());
				joueurs[i].setVirage(0);
			}

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