/*En-tête du fichier d'en-tête
================================
Auteurs		: Émile Loiselle et Francis Forest
Nom du .h	: auto.h
Date		: 21 avril 2017
But			: Gérer toutes les variables intéressantes pour une automobile.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

//Constantes
const double PI = atan(1) * 4;

//Classe
class automobile
{

private:

	char _controleHaut;
	char _controleBas;
	char _controleGauche;
	char _controleDroite;

	int _autoRGB[3];

	double _velociteX;
	double _velociteY;
	double _vitesseIncrementation;
	double _vitesseMax;
	double _vitesseAffaiblir;

	double _degree;
	double _radian;
	double _angleIncrementation;

	int _virage;

public:

	//Constructeur / Déconstructeur
	automobile();
	~automobile();

	//Obtient vélocité
	double getVelociteX();
	double getVelociteY();

	//Accélération / Vitesse Max
	double getVitesseIncrementation();
	double getVitesseMax();

	//Obtient Degré / Vitesse de virage
	double getDegre();
	double getAngleIncrementation();
	int getRed();
	int getGreen();
	int getBlue();

	//Change vélocité
	void setVelociteY(double velociteY);
	void setVelociteX(double velociteX);

	//Change Degré / Virage
	void setDegre(double degre);
	void setVirage(int virage);
	void setCouleur(int red, int green, int blue);

	double convertDegreeRadian(double degre);
	void effectuerVirage();
	void effectuerVelocite(int direction, double tempsDelta);
	void velociteAffaiblir();

	void collision();
};

automobile::automobile()
{
	_velociteX = 0;					//La vitesse actuelle de l'auto
	_velociteY = 0;
	_vitesseMax = 250;
	_vitesseAffaiblir = 0.995;
	_degree = 90;					//L'angle actuel, en degré, de l'auto
	_radian = 0;					//L'angle actuel, en radian, de l'auto

	_autoRGB[0] = 125;
	_autoRGB[1] = 125;
	_autoRGB[2] = 125;

	_vitesseIncrementation = 0.4;		//La vitesse à laquelle l'auto fais son accélération
	_angleIncrementation = 4;		//La vitesse à laquelle l'auto fais ses virage

	_virage = 0;					//1 = Gauche, 2 = Droite, 0 = Nulle
}

automobile::~automobile()
{

}

//==Get==
#pragma region "Getters"
double automobile::getVelociteX()
{
	return _velociteX;
}

double automobile::getVelociteY()
{
	return _velociteY;
}

double automobile::getVitesseIncrementation()
{
	return _vitesseIncrementation;
}

double automobile::getVitesseMax()
{
	return _vitesseMax;
}

double automobile::getDegre()
{
	return _degree;
}

double automobile::getAngleIncrementation()
{
	return _angleIncrementation;
}

int automobile::getRed()
{
	return _autoRGB[0];
}

int automobile::getGreen()
{
	return _autoRGB[1];
}

int automobile::getBlue()
{
	return _autoRGB[2];
}
#pragma endregion

//==Set==
#pragma region "Setters"
void automobile::setVelociteX(double velociteX)
{
	_velociteX = velociteX;
}

void automobile::setVelociteY(double velociteY)
{
	_velociteY = velociteY;
}

void automobile::setDegre(double degree)
{
	_degree = degree;
}

void automobile::setVirage(int virage)
{
	_virage = virage;
}

//Changes la couleur d'une auto (RGB)
void automobile::setCouleur(int red, int green, int blue)
{
	_autoRGB[0] = red;
	_autoRGB[1] = green;
	_autoRGB[2] = blue;
}
#pragma endregion

//Convertit un angle en degree vers un radian
double automobile::convertDegreeRadian(double degree)
{
	return 2 * PI * (degree / 360);
}

//Effectue un virage selon l'angle actuel et la direction du virage désirée
void automobile::effectuerVirage()
{
	//Gauche
	if (_virage == 1)
	{
		_degree = _degree - _angleIncrementation;
	}
	//Droite
	else if (_virage == 2)
	{
		_degree = _degree + _angleIncrementation;
	}
}

//Ajuste la vélocité basée sur la direction désirée et le temps écoulé
void automobile::effectuerVelocite(int direction, double tempsDelta)
{
	//Si on avance
	if (direction == 1)
	{
		//Si la vélocitée est plus petite que la vitesse maximale
		if (_velociteX < _vitesseMax)
			//On ajoute de la vitesse
			_velociteX += _vitesseIncrementation * tempsDelta;

		//Même chose pour Y
		if (_velociteY < _vitesseMax)
			_velociteY += _vitesseIncrementation * tempsDelta;
	}

	//Si on recule
	else if (direction == 0)
	{
		//Si on a pas atteint la vitesse maximale sur X à reculons
		if (_velociteX > -(_vitesseMax / 2))
			//On recule plus vite
			_velociteX -= (_vitesseIncrementation / 2) * tempsDelta;
		else
			//Sinon la vitesse du reculons est celle maximale
			_velociteX = -(_vitesseMax / 2);

		//Même chose pour le Y
		if (_velociteY > -(_vitesseMax / 2))
			_velociteY -= (_vitesseIncrementation / 2) * tempsDelta;
		else
			_velociteY = -(_vitesseMax / 2);
	}
}

//Modification naturelle de la vélocité
void automobile::velociteAffaiblir()
{
	_velociteX *= _vitesseAffaiblir;
	_velociteY *= _vitesseAffaiblir;

}

//Gère la collision entre 2 autos
void automobile::collision()
{
	if (_velociteX > 0 && _velociteY > 0)
	{
		_velociteX = -(_velociteX / 2);
		_velociteY = -(_velociteY / 2);
	}
}