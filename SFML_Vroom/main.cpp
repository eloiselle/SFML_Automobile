/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Directives au pré-processeur
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "auto.h"
#include "piste.h"
using namespace sf;
using namespace std;

ConvexShape creationPolyCollision(ifstream& entree, string nomFichierPoints);

//Programme principal
int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(1280, 768), "Vroooom!!!");					//fenetre
	Texture textureCar;															//texture voiture
	Texture textureRedLight;													//texture lumiere rouge
	Texture textureYellowLight;													//texture lumiere jaune
	Texture textureGreenLight;													//texture lumiere verte
	RenderTexture;				

	piste pisteCourse("points4");												//objet Piste

	Sprite car;																	//sprite voiture
	Sprite redLight;															//sprite lumiere rouge
	Sprite yellowLight;															//sprite lumiere jaune
	Sprite greenLight;															//sprite lumiere verte

	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T
	Clock tempsJeu;																//temps depuis debut partie
	Time temps;																	//utilisé pour prendre le temps de clock tempsJeu
	float secondes;																//utilisé pour changer les lumieres

	automobile joueur;															//premier joueur
	bool canDrive = false;														//voiture peut pas bouger pendant traffic lights

	Event event;

	window.setFramerateLimit(60);												//Limite le nombre d'images par secondes

	textureCar.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));			//Chargement des textures
	textureRedLight.loadFromFile("redLight.png", IntRect(0, 0, 200, 137));
	textureYellowLight.loadFromFile("yellowLight.png", IntRect(0, 0, 60, 137));
	textureGreenLight.loadFromFile("greenLight.png", IntRect(0, 0, 60, 137));

	car.setTexture(textureCar);													//Insertion des textures dans leur sprite réspectifs
	redLight.setTexture(textureRedLight);
	yellowLight.setTexture(textureYellowLight);
	greenLight.setTexture(textureGreenLight);
	
	car.setOrigin(12, 8);														//offre rotation plus juste
	pisteCourse.setPosition(120, 100);

	//Initialisation auto
	car.setPosition(190, 395);
	car.rotate(joueur.getDegre());

	//Traffics Lights centrées
	redLight.setPosition(585, 300);
	yellowLight.setPosition(585, 300);
	greenLight.setPosition(585, 300);
	
	
	while (window.isOpen())														//Tant que le jeu roule
	{
		Time tempsDelta = horlogeDelta.restart();								//Réinitialise l'horloge

		//Attend les événements
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				window.close();

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))						//Gauche
			joueur.setVirage(1);

		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))				//Droite
			joueur.setVirage(2);
	
		else
			joueur.setVirage(0);												//Nulle

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))						//Haut
			joueur.effectuerVelocite(1, tempsDelta.asMilliseconds());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))						//Bas
			joueur.effectuerVelocite(0, tempsDelta.asMilliseconds());

		temps = tempsJeu.getElapsedTime();
		
		if (temps.asSeconds() >= 5)												//pas bouger pendant traffic lights
		{
			canDrive = true;
		}

		//Gère les virages
		if (canDrive == true)
		{
			joueur.effectuerVirage();
			car.setRotation(joueur.getDegre());
			joueur.setVirage(0);

			//Gère le mouvement du véhicule
			car.move(joueur.getVelociteX() * cos(joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds(),
					 joueur.getVelociteY() * sin(joueur.convertDegreeRadian(joueur.getDegre())) * tempsDelta.asSeconds());

			//Affaiblissement de la vélocité
			joueur.velociteAffaiblir();

		}

		//Gère l'affichage
		window.clear(Color(0, 150, 0));
		window.draw(pisteCourse.getSprite());

		for (int i = 0; i < pisteCourse.getNbCollisions(); i++)
		{
			window.draw(pisteCourse.getCollisions(i));
		}
		window.draw(car);

		if (temps.asSeconds() <= 3)			//lumière rouge
		{
			window.draw(redLight);
		}
		else if (temps.asSeconds() <= 5)	//lumière jaune
		{
			window.draw(yellowLight);
		}
		else if (temps.asSeconds() <= 6)	//lumière verte
		{
			window.draw(greenLight);
		}

		window.display();


	}
	return 0;
}
//Creation de polygones convexes à partir de points reccueillis dans un fichier texte, préalablement générer avec le programme getPoints(TM). Retourne une forme convexe
ConvexShape creationPolyCollision(ifstream& entree, string nomFichierPoints)
{
	int nbPoints;								//nb points que la forme contient
	
	Vector2f points[1000];						//coordonnées x et y des points, 1000 est une valeur arbitraire

	ConvexShape shape;							//forme convexe

	entree >> nbPoints;			

	shape.setPointCount(nbPoints);

	for (int i = 0; i < nbPoints; i++)			//pr tous les points de la forme
	{
		entree >> points[i].x >> points[i].y;
	}

	for (int i = 0; i < nbPoints; i++)			//pr tous les points de la forme	
	{
		shape.setPoint(i, points[i]);
	}

	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(4);				
	shape.setOutlineColor(Color::White);

	return shape;

}