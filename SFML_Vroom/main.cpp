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
#include <iostream>
#include <fstream>
#include <string>
#include "auto.h"
#include "piste.h"
#include "trafficLights.h"
using namespace sf;
using namespace std;

//Prototypes
int afficherMenu(RenderWindow& window, Font font);

//Programme principal
int main()
{
	//Variables
	trafficLights lights;
	piste pisteCourse("mapFinale2");											//Objet Piste
	automobile joueurs[4];

	bool canDrive = false;														//Voiture peut pas bouger pendant traffic lights
	bool jouer = true;
	bool quitter = false;
	bool options = false;

	//Génération de nombres aléatoires (seed)
	srand(time(NULL));

	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 768), "Vroooom!!!");					//Fenêtre
	window.setFramerateLimit(60);												//Limite le nombre d'images par secondes

	Sprite sprJoueur[4];														//Affiche les joueurs
	Texture textureCar;															//Texture voiture

	//Temps et horloges
	Clock horlogeDelta;															//https://en.wikipedia.org/wiki/%CE%94T
	Clock tempsJeu;																//Temps écoulé depuis début partie

	Time temps;																	//Utilisé pour prendre le temps de clock tempsJeu
	Time tempsTest;
	Clock tempsMenu;

	//Event
	Event event;

	//Polices et textes
	Font font;
	Text chrono;

	font.loadFromFile("Roboto-Italic.ttf");
	chrono.setFont(font);
	chrono.setPosition(20, 20);
	lights.setPosition(585, 300);

	//Menu
	while (!quitter)
	{
		//Attend les événements de fermeture
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				quitter = true;
			else
				quitter = false;
		}

		int nbJoueurs = afficherMenu(window, font);
		tempsJeu.restart();

		if (nbJoueurs == 0)
			quitter = true;
		else
			jouer = true;

		//Applique les touches à utiliser pour chaques joueurs
		joueurs[0].setKeys(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
		joueurs[1].setKeys(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
		joueurs[2].setKeys(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L);
		joueurs[3].setKeys(Keyboard::T, Keyboard::G, Keyboard::F, Keyboard::H);

		//Chargement de chaque joueurs
		for (int i = 0; i < nbJoueurs; i++)
		{
			//Génère une couleure aléatoire pour chaque auto
			joueurs[i].setCouleur(rand() % 25 * 10, rand() % 25 * 10, rand() % 25 * 10);

			//Chargement de la texture pour l'auto spécifiée
			textureCar.loadFromFile("car.png");
			sprJoueur[i].setTexture(textureCar);
			sprJoueur[i].setOrigin(12, 8);
			sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

			//Initialisation automobile
			sprJoueur[i].setPosition(100 + (100 * i), 100);
			sprJoueur[i].rotate(joueurs[i].getDegreAuto());
		}

		while (jouer)	//Tant que le jeu roule
		{
			//Attend les événements de fermeture
			while (window.pollEvent(event))
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
					jouer = false;

			//***************************Événements de jeu***************************
			//***********************************************************************

			//Gère la lumière de départ
			temps = tempsJeu.getElapsedTime();

			if (temps.asSeconds() >= 5)
				canDrive = true;
			else
				canDrive = false;

			//Réinitialise l'horloge pour une expérience uniforme sur toutes les plateformes
			Time tempsDelta = horlogeDelta.restart();

			for (int i = 0; i < nbJoueurs; i++)
			{
				//Si le départ n'a pas été lancé
				if (canDrive == false)
					break;

				//***************************Effectue toutes les actions reliées au joueur***************************
				joueurs[i].fonctionnement(sprJoueur[i], tempsDelta);

				//Gère les collisions entre chaque autos
				for (int j = 0; j < nbJoueurs; j++)
					//Si on touche une auto
					if (i != j && sprJoueur[i].getGlobalBounds().intersects(sprJoueur[j].getGlobalBounds()))
					{
						joueurs[i].collisionAuto(joueurs[j]);
						break;
					}
			}

			//***************************Affichage***************************
			//***************************************************************

			//Efface l'affichage précédent
			window.clear(Color(0, 125, 0));

			//Affiche la piste
			window.draw(pisteCourse.getSprite());

			//affiche chrono
			if (temps.asSeconds() >= 5)
			{
				chrono.setString(to_string(temps.asSeconds() - 5));
				window.draw(chrono);
			}

			//Affiche toutes les formes de collisions --> afin de tester collisions
			for (int i = 0; i < pisteCourse.getNbCollisions(); i++)
				window.draw(pisteCourse.getCollisions(i));

			//Affiche la lumière au départ
			lights.changerLumiere(tempsJeu);

			if (temps.asSeconds() <= 6)
				window.draw(lights.getSprite());

			//Affichage de tous les joueurs
			for (int i = 0; i < nbJoueurs; i++)
				window.draw(sprJoueur[i]);

			//Rfraîchi l'affichage
			window.display();
		}

	}
	return 0;
}

//(Fonction) Affiche le menu et attends une réponse du joueur
int afficherMenu(RenderWindow& window, Font font)
{
	int nbJoueurs = 1;

	//Textures et sprites
	Texture textureMenu;
	Sprite spriteMenu;

	RectangleShape nbJoueursSel[4];
	Text txtJouer;

	for (int i = 0; i < 4; i++)
	{
		nbJoueursSel[i].setSize(sf::Vector2f(200, 100));

		nbJoueursSel[i].setFillColor(Color::Black);
		nbJoueursSel[i].setOutlineThickness(5);
		nbJoueursSel[i].setOutlineColor(sf::Color::Red);
		nbJoueursSel[i].setPosition(200 + (i * 225), (window.getSize().y - nbJoueursSel[i].getSize().y) - 20);
	}

	nbJoueursSel[0].setOutlineColor(sf::Color::Green);

	textureMenu.loadFromFile("titleScreen.png");
	spriteMenu.setTexture(textureMenu);

	txtJouer.setFont(font);
	txtJouer.setString("Appuyez sur espace pour jouer");

	while (1)
	{
		//******Affichage******
		window.draw(spriteMenu);
		window.draw(txtJouer);

		if (Keyboard::isKeyPressed(Keyboard::Space))
			return nbJoueurs;

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			return 0;

		//Vérifie quel bouton a été sélectionné, et ajuste le nombre de joueurs désiré
		for (int i = 0; i < 4; i++)
		{
			if (Mouse::isButtonPressed(Mouse::Button::Left) &&
				Mouse::getPosition(window).x > nbJoueursSel[i].getPosition().x && Mouse::getPosition(window).x < (nbJoueursSel[i].getPosition().x + nbJoueursSel[i].getSize().x) &&
				Mouse::getPosition(window).y > nbJoueursSel[i].getPosition().y && Mouse::getPosition(window).y < (nbJoueursSel[i].getPosition().y + nbJoueursSel[i].getSize().y))
			{
				nbJoueurs = i + 1;
				nbJoueursSel[i].setOutlineColor(sf::Color::Green);

				for (int j = 0; j < 4; j++)
					if (j != i)
						nbJoueursSel[j].setOutlineColor(sf::Color::Red);
			}
			window.draw(nbJoueursSel[i]);
		}
		window.display();
	}
}