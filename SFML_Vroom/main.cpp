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
using namespace sf;
using namespace std;

//Programme principal
int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 768), "Vroooom!!!");					//fenetre
	Texture textureCar;															//texture voiture
	RenderTexture;				

	piste pisteCourse("points4");												//objet Piste

	Sprite sprJoueur[4];															//sprite voiture
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
		sprJoueur[i].setColor(Color(joueurs[i].getRed(), joueurs[i].getGreen(), joueurs[i].getBlue()));

		//Initialisation auto
		sprJoueur[i].setPosition(100 + (100 * i), 100);
		sprJoueur[i].rotate(joueurs[i].getDegre());
	}
  
	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T
	Clock tempsJeu;																//temps depuis debut partie
	Time temps;																	//utilisé pour prendre le temps de clock tempsJeu

	automobile joueur;															//premier joueur
	bool canDrive = false;														//voiture peut pas bouger pendant traffic lights
	trafficLights lights;

	Event event;

	window.setFramerateLimit(60);												//Limite le nombre d'images par secondes

	textureCar.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));			//Chargement des textures
	
	car.setTexture(textureCar);													//Insertion des textures dans leur sprite réspectifs
	
	car.setOrigin(12, 8);														//offre rotation plus juste
	pisteCourse.setPosition(120, 100);
	lights.setPosition(585, 300);

	car.setPosition(190, 395);													//Initialisation auto
	car.rotate(joueur.getDegre());
	
	while (window.isOpen())														//Tant que le jeu roule
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
      
      sprJoueur[i].move(
				joueurs[i].getVelociteX() * cos(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds(),
				joueurs[i].getVelociteY() * sin(
					joueurs[i].convertDegreeRadian(joueurs[i].getDegre())) * tempsDelta.asSeconds());
      
    window.draw(sprJoueur[i]);
			
		}

		temps = tempsJeu.getElapsedTime();
		
		if (temps.asSeconds() >= 5)												//pas bouger pendant traffic lights
		{
			canDrive = true;
		}

		//Gère l'affichage
		window.clear(Color(0, 150, 0));
		window.draw(pisteCourse.getSprite());						//affiche piste

		for (int i = 0; i < pisteCourse.getNbCollisions(); i++)		//affiche toutes les formes de collisions --> afin de tester collisions
		{
			window.draw(pisteCourse.getCollisions(i));
		}

		window.draw(car);											//affiche voiture

		lights.changerLumiere(tempsJeu);
		window.draw(lights.getSprite());

		window.display();


	}
	return 0;
}
