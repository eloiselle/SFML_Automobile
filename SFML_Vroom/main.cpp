/* En-tête du programme
=========================
Auteurs		: Émile Loiselle et Francis Forest
Nom du CPP	: main.cpp
Date		: 21 avril 2017
But			: Contrôler un automobile sur une piste de course le plus rapidement possible. */

//Directives au pré-processeur
#include <SFML/Graphics.hpp>
using namespace sf;

//Constantes
const double PI = atan(1) * 4;

//Prototypes
double convertDegreeRadian(double degre);

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
	double degreeAuto = 90;
	double radianAuto = 0;
	double angleIncrementation = 0.01;

	//Chargement de la texture de l'auto
	texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));

	//Insertion de la texture dans le sprite
	sprite.setTexture(texture);

	//Initialisation  auto
	sprite.setPosition(100, 100);
	sprite.rotate(degreeAuto);

	//Tant que le jeu roule
	while (window.isOpen())
	{
		//Attend les événements
		while (window.pollEvent(event))
		{
			//Si appuie sur X ou Alt+F4
			if (event.type == Event::Closed)

				//Ferme le jeu
				window.close();
		}

		//Gère les virages
		degreeAuto -= angleIncrementation;
		sprite.rotate(-angleIncrementation);

		sprite.move(cos(convertDegreeRadian(degreeAuto)) / 100, sin(convertDegreeRadian(degreeAuto)) / 100);
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}

//(Fonction) Convertit un angle en degree vers un radian
double convertDegreeRadian(double degree)
{
	return 2 * PI * (degree / 360);
}