#pragma once

#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class cScreen
{
public:
	cScreen();
	~cScreen();
	virtual int Run(RenderWindow &app) = 0;

private:

};

cScreen::cScreen()
{
}

cScreen::~cScreen()
{
}