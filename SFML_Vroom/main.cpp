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
	Texture textureRedLight;
	Texture textureYellowLight;
	Texture textureGreenLight;
	RenderTexture;

	Sprite car;
	Sprite map;
	Sprite redLight;
	Sprite yellowLight;
	Sprite greenLight;

	Clock horlogeDelta;			//https://en.wikipedia.org/wiki/%CE%94T
	Clock clock2;
	Time temps2;
	float secondes;

	Event event;

	//Variables
	automobile joueur;
	bool canDrive = false;

	//Limite le nombre d'images par secondes
	window.setFramerateLimit(60);

	//Chargement des textures
	texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));

	textureMap.loadFromFile("map.png", IntRect(0, 0, 1280, 720));

	textureRedLight.loadFromFile("redLight.png", IntRect(0, 0, 200, 137));
	textureYellowLight.loadFromFile("yellowLight.png", IntRect(0, 0, 60, 137));
	textureGreenLight.loadFromFile("greenLight.png", IntRect(0, 0, 60, 137));

	//Insertion des textures dans leur sprite réspectifs
	car.setTexture(texture);
	map.setTexture(textureMap);
	redLight.setTexture(textureRedLight);
	yellowLight.setTexture(textureYellowLight);
	greenLight.setTexture(textureGreenLight);
	
	car.setOrigin(12, 8);

	//Initialisation auto
	car.setPosition(181, 395);
	car.rotate(joueur.getDegre());

	//Traffics Lights centrées
	redLight.setPosition(575, 300);
	yellowLight.setPosition(575, 300);
	greenLight.setPosition(575, 300);
	
	//Tant que le jeu roule
	while (window.isOpen())
	{
		//Réinitialise l'horloge
		Time tempsDelta = horlogeDelta.restart();

		//Attend les événements
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
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


		temps2 = clock2.getElapsedTime();
		
		if (temps2.asSeconds() >= 5)
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
		window.clear();
		window.draw(map);
		window.draw(car);

		if (temps2.asSeconds() <= 3)
		{
			window.draw(redLight);
		}
		else if (temps2.asSeconds() <= 5)
		{
			window.draw(yellowLight);
		}
		else if (temps2.asSeconds() <= 6)
		{
			window.draw(greenLight);
		}
		window.display();
	}
	return 0;
}