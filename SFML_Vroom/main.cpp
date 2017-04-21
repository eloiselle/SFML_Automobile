
#include <SFML/Graphics.hpp>
using namespace sf;	//SFML

//Constantes
const double PI = atan(1) * 4;

//Prototypes
double getRads(double degre);

int main()
{
	//Initialisation SFML
	RenderWindow window(VideoMode(800, 600), "Vroooom!!!");
	Texture texture;
	RenderTexture;
	Sprite sprite;
	Event event;

	//Variables
	double degree = 90;
	double radian = 0;
	double angleInc = 0.01;

	//Chargement de la texture de l'auto
	texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16));

	//Insertion de la texture dans le sprite
	sprite.setTexture(texture);

	//Initialisation  auto
	sprite.setPosition(100, 100);
	sprite.rotate(degree);

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
		degree -= angleInc;
		sprite.rotate(-angleInc);

		sprite.move(cos(getRads(degree)) / 100, sin(getRads(degree)) / 100);
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}

double getRads(double degre)
{
	return 2 * PI * (degre / 360);
}