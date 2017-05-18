#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

class cerclePiste
{

private:
	int _qHautGauche = 0;
	int _qHautDroite = 0;
	int _qBasDroite = 0;
	int _qBasGauche = 0;


public:
	cerclePiste();
	~cerclePiste();
	CircleShape cercle;

	int getqHautGauche();
	int getqHautDroite();
	int getqBasDroite();
	int getqBasGauche();

	CircleShape getCercle();

	void setqHautGauche(int x);
	void setqHautDroite(int x);
	void setqBasDroite(int x);
	void setqBasGauche(int x);
	void setAll(int hg, int hd, int bd, int bg);




};

cerclePiste::cerclePiste()
{
}

cerclePiste::~cerclePiste()
{
}

//getteurs

int cerclePiste ::getqHautGauche()
{
	return _qHautGauche;
}
int cerclePiste ::getqHautDroite()
{
	return _qHautDroite;
}
int cerclePiste ::getqBasDroite()
{
	return _qBasDroite;
}
int cerclePiste::getqBasGauche()
{
	return _qBasGauche;
}

CircleShape cerclePiste::getCercle()
{
	return cercle;
}

void cerclePiste::setqHautGauche(int x)
{
	_qHautGauche = x;
}
void cerclePiste::setqHautDroite(int x)
{
	_qHautDroite = x;
}
void cerclePiste::setqBasDroite(int x)
{
	_qBasDroite = x;
}
void cerclePiste::setqBasGauche(int x)
{
	_qBasGauche = x;
}

void cerclePiste ::setAll(int hg, int hd, int bd, int bg)
{
	_qHautGauche = hg;
	_qHautDroite = hd;
	_qBasDroite = bd;
	_qBasGauche = bg;
}