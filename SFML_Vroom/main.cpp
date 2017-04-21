
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

#define _USE_MATH_DEFINES

const double PI = atan(1) * 4;

double getRads(double degre);

int main()
{
	RenderWindow window(VideoMode(800, 600), "Vroooom!!!");

	double degre = 90;
	double radian = 0;
	double angleInc = 0.01;

	Texture texture;
	RenderTexture;
	Sprite sprite;
	if (!texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16)))
	{
		cout << "error loading";
		system("pause>0");
	}

	sprite.setTexture(texture);

	sprite.setPosition(100, 100);
	sprite.rotate(degre);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		degre -= angleInc;
		sprite.rotate(-angleInc);

		sprite.move(cos(getRads(degre)) / 100, sin(getRads(degre)) / 100);
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