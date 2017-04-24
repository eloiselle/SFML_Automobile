
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
//#include <Thor/Shapes/ConcaveShape.hpp>

using namespace std;
using namespace sf;




//const double PI = atan(1) * 4;

//double getRads(double degre);

int main()
{
	RenderWindow window(VideoMode(800, 600), "Vroooom!!!");
	window.setVerticalSyncEnabled(true);
	
	RectangleShape fond;
	fond.setSize(Vector2f(800, 600));
	fond.setPosition(0, 0);
	fond.setFillColor(Color::Cyan);


	RectangleShape test;
	test.setSize(Vector2f(30, 30));
	test.setPosition(100, 100);
	test.setFillColor(Color::Transparent);

	Image carte;
	carte.loadFromFile("map.png");

	Image fondTest;
	fondTest.create(800, 600, Color::Black);

	Color couleur;

	CircleShape dot(1);
	dot.setFillColor(Color::Black);

	const int nofRows = 60;
	const int nofCols = 80;
	const int distance = 10; //distance between dots
	
	const float height = sqrt(pow(distance, 2));

	

	/*thor::ConcaveShape concaveShape;
	concaveShape.setPointCount(5);
	concaveShape.setPoint(0, sf::Vector2f(50, 50));
	concaveShape.setPoint(1, sf::Vector2f(100, 100));
	concaveShape.setPoint(2, sf::Vector2f(150, 50));
	concaveShape.setPoint(3, sf::Vector2f(150, 200));
	concaveShape.setPoint(4, sf::Vector2f(50, 150));
	concaveShape.setOutlineThickness(2.f);
	concaveShape.setFillColor(sf::Color(150, 100, 100));
	concaveShape.setOutlineColor(sf::Color(200, 100, 100));

	*/

	Texture textureMap;
	RenderTexture;

	Sprite map;

	textureMap.loadFromFile("map.png", IntRect(0, 0, 800, 600));

	map.setTexture(textureMap);

	map.setPosition(0, 0);

	carte.copy(carte, 0, 0);

	//Texture texture;
	//RenderTexture;
	//Sprite sprite;
	//if (!texture.loadFromFile("orange32x16.png", IntRect(0, 0, 32, 16)))
	//{
	//	cout << "error loading";
	//	system("pause>0");
	//}

	//sprite.setTexture(texture);

	//sprite.setPosition(100, 100);
	//sprite.rotate(degre);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
		}

		//degre -= angleInc;
		//sprite.rotate(-angleInc);

		//sprite.move(cos(getRads(degre)) / 100, sin(getRads(degre)) / 100);
		
		
		window.clear(Color::Black);
		window.draw(fond);
		//window.draw(carte);
		window.draw(map);

		


		//window.draw(test);

		for (int i = 0; i<nofRows; ++i) {
			for (int j = 0; j<nofCols; ++j) {
				if (i % 2 == 0) dot.setPosition(j*distance, i*height); //even rows
				else dot.setPosition(j*distance, i*height); //odd rows
				window.draw(dot);
			}
		}

		
		
		window.display();
	}

	return 0;
}

//double getRads(double degre)
//{
//	return 2 * PI * (degre / 360);
//}