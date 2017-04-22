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

	//Variables
	automobile joueur;

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
		//Attend les événements
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//Si appuie sur X ou Alt+F4
			case Event::Closed:
				window.close();
				break;

				//Si une touche appuyée
			case Event::KeyPressed:
				switch (event.key.code)
				{
					//Escape ferme le jeu
				case sf::Keyboard::Escape:
					window.close();
					break;

					//Gauche
				case sf::Keyboard::Left:
					//Tourne à gauche
					joueur.setDegree(joueur.getDegree() - joueur.getAngleIncrementation());
					break;

					//Droite
				case sf::Keyboard::Right:
					//Tourne à droite
					joueur.setDegree(joueur.getDegree() + joueur.getAngleIncrementation());
					break;
				}
			}
		}

		//Gère les virages
		sprite.setRotation(joueur.getDegree());

		//Gère le mouvement
		sprite.move(cos(joueur.convertDegreeRadian(joueur.getDegree())) / 30, sin(joueur.convertDegreeRadian(joueur.getDegree())) / 30);

		//Gère l'affichage
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}