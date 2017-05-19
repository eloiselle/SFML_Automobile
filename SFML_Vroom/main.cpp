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
float getDistance(CircleShape cercle, Sprite car);

//Programme principal
int main()
{
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

	Text laps;
	int tour = 0;

	bool isCheckPoint1 = false;
	bool jouer = false;
	bool quitter = false;

	//Fonts et text
	font.loadFromFile("Roboto-Italic.ttf");
	chrono.setFont(font);
	chrono.setPosition(40, 40);

	laps.setFont(font);
	laps.setPosition(40, 80);


	trafficLights lights;
	piste pisteCourse("mapFinale2");											//objet Piste
	automobile joueurs[4];


	int nbJoueurs = 4;
	bool canDrive = false;														//voiture peut pas bouger pendant traffic lights

	RectangleShape checkPoint1;
	RectangleShape ligneArivee;

	checkPoint1.setPosition(555, 605);
	checkPoint1.setSize(Vector2f(20, 130));
	checkPoint1.setFillColor(Color::Transparent);
	//checkPoint1.setOutlineThickness(2);
	//checkPoint1.setOutlineColor(Color::White);

	ligneArivee.setPosition(940, 15);
	ligneArivee.setSize(Vector2f(20, 280));
	ligneArivee.setFillColor(Color::Transparent);
	//ligneArivee.setOutlineThickness(2);
	//ligneArivee.setOutlineColor(Color::White);

	//Change les couleures de chaque joueurs
	joueurs[0].setCouleur(0, 255, 0);
	joueurs[1].setCouleur(255, 0, 0);
	joueurs[2].setCouleur(0, 255, 255);
	joueurs[3].setCouleur(255, 255, 0);

	//Applique les touches à utiliser pour chaques joueurs
	joueurs[0].setKeys(Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);
	joueurs[1].setKeys(Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D);
	joueurs[2].setKeys(Keyboard::I, Keyboard::K, Keyboard::J, Keyboard::L);
	joueurs[3].setKeys(Keyboard::T, Keyboard::G, Keyboard::F, Keyboard::H);

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
			//Chargement de la texture pour l'auto spécifiée
			textureCar.loadFromFile("car.png");
			sprJoueur[i].setTexture(textureCar);
			sprJoueur[i].setOrigin(12, 8);
			sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

			//Initialisation automobile
			sprJoueur[i].setPosition(900, 60 + (25 * i));
			sprJoueur[i].rotate(joueurs[i].getDegreAuto());
		}

		joueurs[0].setCouleur(253, 167, 0);

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

				for (int j = 0; j < pisteCourse.getNbCercles(); j++)
				{
					joueurs[i].setMaxSpeed(false);
					pisteCourse.getCercle(j).getCercle().setOutlineColor(Color::White);

					if (sprJoueur[i].getGlobalBounds().intersects(pisteCourse.getCercle(j).getCercle().getGlobalBounds()))
					{

						if (pisteCourse.getCercle(j).getqBasDroite())
						{
							if (pisteCourse.getCercle(j).getCercle().getPosition().x < sprJoueur[i].getPosition().x && pisteCourse.getCercle(j).getCercle().getPosition().y > sprJoueur[i].getPosition().y)
							{
								joueurs[i].setMaxSpeed(true);
								pisteCourse.getCercle(j).getCercle().setOutlineColor(Color::Red);
							
							}
						}
						if (pisteCourse.getCercle(j).getqHautDroite())
						{
							if (pisteCourse.getCercle(j).getCercle().getPosition().x < sprJoueur[i].getPosition().x && pisteCourse.getCercle(j).getCercle().getPosition().y < sprJoueur[i].getPosition().y)
							{
								joueurs[i].setMaxSpeed(true);
								pisteCourse.getCercle(j).getCercle().setOutlineColor(Color::Red);
								
							}
						}
						if (pisteCourse.getCercle(j).getqBasGauche())
						{
							if (pisteCourse.getCercle(j).getCercle().getPosition().x > sprJoueur[i].getPosition().x && pisteCourse.getCercle(j).getCercle().getPosition().y > sprJoueur[i].getPosition().y)
							{
								joueurs[i].setMaxSpeed(true);
								pisteCourse.getCercle(j).getCercle().setOutlineColor(Color::Red);
								
							}
						}
						if (pisteCourse.getCercle(j).getqHautGauche())
						{
							if (pisteCourse.getCercle(j).getCercle().getPosition().x > sprJoueur[i].getPosition().x && pisteCourse.getCercle(j).getCercle().getPosition().y < sprJoueur[i].getPosition().y)
							{
								joueurs[i].setMaxSpeed(true);
								pisteCourse.getCercle(j).getCercle().setOutlineColor(Color::Red);
								
							}
						}
					}
				}

				for (int j = 0; j < pisteCourse.getNbPneus(); j++)
				{
					if (sprJoueur[i].getGlobalBounds().intersects(pisteCourse.getPneu(j).getGlobalBounds()))
					{
						joueurs[i].collisionMurs();
					}
				}

				for (int j = 0; j < pisteCourse.getNbRectangles(); j++)
				{
					if (sprJoueur[i].getGlobalBounds().intersects(pisteCourse.getRectangle(j).getGlobalBounds()))
					{
						
						joueurs[i].setMaxSpeed(300);
					}
				}

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
			for (int i = 0; i < pisteCourse.getNbRectangles(); i++)
				window.draw(pisteCourse.getRectangle(i));

			//Affiche la lumière au départ
			lights.changerLumiere(tempsJeu);

			if (temps.asSeconds() <= 6)
				window.draw(lights.getSprite());

			//Affichage de tous les joueurs
			for (int i = 0; i < nbJoueurs; i++)
				window.draw(sprJoueur[i]);
			laps.setString(to_string(tour) + "/3");
			window.draw(laps);

			window.draw(checkPoint1);
			if (sprJoueur[0].getGlobalBounds().intersects(checkPoint1.getGlobalBounds()))
			{
				isCheckPoint1 = true;
			}

			if (sprJoueur[0].getGlobalBounds().intersects(ligneArivee.getGlobalBounds()) && isCheckPoint1)
			{
				isCheckPoint1 = false;
				tour++;
			}

			for (int i = 0; i < pisteCourse.getNbCercles(); i++)
			{
				window.draw(pisteCourse.getCercle(i).getCercle());
			}

			for (int i = 0; i < pisteCourse.getNbPneus(); i++)
			{
				window.draw(pisteCourse.getPneu(i));
			}

			for (int i = 0; i < pisteCourse.getNbRectangles(); i++)
			{
				window.draw(pisteCourse.getRectangle(i));
			}

			window.draw(ligneArivee);


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
	Text infoNbJrs;
	Text nombreJrs[4];

	Texture txtAuto1;
	Texture txtAuto2;
	Texture txtAuto3;
	Texture txtAuto4;

	Sprite auto1;
	Sprite auto2;
	Sprite auto3;
	Sprite auto4;

	txtAuto1.loadFromFile("auto1.png", IntRect(0, 0, 200, 150));
	txtAuto2.loadFromFile("auto2.png", IntRect(0, 0, 200, 150));
	txtAuto3.loadFromFile("auto3.png", IntRect(0, 0, 200, 150));
	txtAuto4.loadFromFile("auto4.png", IntRect(0, 0, 200, 150));

	auto1.setTexture(txtAuto1);
	auto2.setTexture(txtAuto2);
	auto3.setTexture(txtAuto3);
	auto4.setTexture(txtAuto4);

	for (int i = 0; i < 4; i++)
	{
		nbJoueursSel[i].setSize(sf::Vector2f(200, 150));

		nbJoueursSel[i].setFillColor(Color::Black);
		nbJoueursSel[i].setOutlineThickness(5);
		nbJoueursSel[i].setOutlineColor(sf::Color::Red);
		nbJoueursSel[i].setPosition(200 + (i * 225), (window.getSize().y - nbJoueursSel[i].getSize().y) - 20);
		

		nombreJrs[i].setFont(font);
		nombreJrs[i].setString(to_string(i + 1));

		Vector2f temp = nbJoueursSel[i].getSize();
		temp.x = temp.x / 2 - 10;
		temp.y = temp.y / 2 - 20;

		nombreJrs[i].setPosition(nbJoueursSel[i].getPosition() + temp);

	}

	auto1.setPosition(200, (window.getSize().y - 150) - 20);
	auto2.setPosition(200 + 225, (window.getSize().y - 150) - 20);
	auto3.setPosition(200 + 450, (window.getSize().y - 150) - 20);
	auto4.setPosition(200 + 675, (window.getSize().y - 150) - 20);

	nbJoueursSel[0].setOutlineColor(sf::Color::Green);

	textureMenu.loadFromFile("titleScreen.png");
	spriteMenu.setTexture(textureMenu);

	txtJouer.setFont(font);
	txtJouer.setString("Appuyez sur espace pour jouer");

	infoNbJrs.setFont(font);
	infoNbJrs.setString("Nombre de joueurs: ");
	infoNbJrs.setPosition(200, 600);
	infoNbJrs.setFillColor(Color::Black);

	while (true)
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
			window.draw(nombreJrs[i]);
			window.draw(infoNbJrs);
			window.draw(auto1);
			window.draw(auto2);
			window.draw(auto3);
			window.draw(auto4);
		}
		window.display();
	}
}

float getDistance(CircleShape cercle, Sprite car)
{
	float dx = 0;
	float dy = 0;

	dx = abs(cercle.getPosition().x - car.getPosition().x);
	dy = abs(cercle.getPosition().y - car.getPosition().y);

	return sqrt(dx*dx + dy*dy);
}