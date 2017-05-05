/*En-tête du fichier d'en-tête
================================
Auteurs		: Émile Loiselle et Francis Forest
Nom du .h	: auto.h
Date		: 21 avril 2017
But			: Gérer toutes les variables intéressantes pour une automobile.*/

//On s'assure que si ce fichier est #include plus d'une fois, il ne sera inclus qu'une seule fois pour tout le programme
#pragma once

using namespace sf;

//Constantes
const double PI = atan(1) * 4;

//Classe
class automobile
{

private:
#pragma region "Variables"
	//Touches pour le joueur
	Keyboard::Key _autoControles[4];

	//États de l'auto
	double _velociteX;
	double _velociteY;
	int _derniereDirection;

	int _virage;
	double _degreVelocite;
	double _degre;
	double _radian;

	//Autres options
	double _vitesseMax;

	//Accélérations
	double _vitesseIncrementation;
	double _angleIncrementation;
	double _vitesseAffaiblir;

	//Couleur de l'auto
	int _autoRGB[3];
#pragma endregion
public:
	
#pragma region "Fonctions"

	//Constructeur
	automobile();


	//Obtient vélocité
	double getVelociteX();
	double getVelociteY();

	//Obtient accélération / vitesse Max
	double getVitesseIncrementation();
	double getVitesseMax();

	//Obtient degré / degré selon la vélocité / vitesse de virage
	double getDegreAuto();
	double getDegreVelocite();
	double getAngleIncrementation();

	//Obtient les couleurs de l'auto (RGB)
	int getRed();
	int getGreen();
	int getBlue();

	//Obtient touches joueur
	Keyboard::Key getUp();
	Keyboard::Key getDown();
	Keyboard::Key getLeft();
	Keyboard::Key getRight();


	//Change vélocité
	void setVelociteY(double velociteY);
	void setVelociteX(double velociteX);
	void changerDirection(int direction);

	//Change Degré / Virage
	void setDegre(double degre);
	void setDegreVelocite(double degree);
	void setVirage(int virage);

	//Couleur de l'auto
	void setCouleur(int red, int green, int blue);

	//Défini les touches du joueur
	void setKeys(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right);


	//Modifications du degré
	void effectuerVirage();
	void calculDrift();
	double convertDegreeRadian(double degre);

	//Modifications de la vélocité
	void effectuerVelocite(double tempsDelta);
	void velociteAffaiblir(float multiple);

	//Gère les collisions
	void collisionMurs();
	void collisionAuto(automobile &destination);

};

automobile::automobile()
{
	//États de l'auto
	_velociteX = 0;					//La vitesse actuelle de l'auto¸(sur l'axe des X)
	_velociteY = 0;					//La vitesse actuelle de l'auto¸(sur l'axe des Y)
	_virage = 0;					//1 = Gauche, 2 = Droite, 0 = Nulle
	_degreVelocite = 0;
	_degre = 0;						//L'angle actuel, en degré, de l'auto
	_radian = 0;					//L'angle actuel, en radian, de l'auto
	_derniereDirection = 1;

	//Autres options
	_vitesseMax = 300;				//Vitesse maximale

	//Accélérations
	_vitesseIncrementation = 0.2;	//La vitesse à laquelle l'auto fais son accélération
	_angleIncrementation = 4;		//La vitesse à laquelle l'auto fais ses virage
	_vitesseAffaiblir = 0.995;		//La vitesse à laquelle l'auto ralenti naturellement

	//Couleur de l'auto
	_autoRGB[0] = 125;
	_autoRGB[1] = 125;
	_autoRGB[2] = 125;

	_virage = 0;					//1 = Gauche, 2 = Droite, 0 = Nulle
}

//==Get==
#pragma region "Getters"

//Informations vitesse
double automobile::getVelociteX() {
	return _velociteX;
}

double automobile::getVelociteY() {
	return _velociteY;
}

double automobile::getVitesseIncrementation() {
	return _vitesseIncrementation;
}

double automobile::getVitesseMax() {
	return _vitesseMax;
}

//Informations d'angle
double automobile::getDegreAuto() {
	return _degre;
}

double automobile::getDegreVelocite() {
	return _degreVelocite;
}

double automobile::getAngleIncrementation() {
	return _angleIncrementation;
}

//Get couleur du véhicule
int automobile::getRed() {
	return _autoRGB[0];
}

int automobile::getGreen() {
	return _autoRGB[1];
}

int automobile::getBlue() {
	return _autoRGB[2];
}

//Get contrôles du véhicule
Keyboard::Key automobile::getUp() {
	return _autoControles[0];
}

Keyboard::Key automobile::getDown() {
	return _autoControles[1];
}

Keyboard::Key automobile::getLeft() {
	return _autoControles[2];
}

Keyboard::Key automobile::getRight() {
	return _autoControles[3];
}
#pragma endregion

//==Set==
#pragma region "Setters"
void automobile::setVelociteX(double velociteX) {
	_velociteX = velociteX;
}

void automobile::setVelociteY(double velociteY) {
	_velociteY = velociteY;
}

void automobile::changerDirection(int direction) {
	_derniereDirection = direction;
}

void automobile::setDegre(double degree) {
	_degre = degree;
}

void automobile::setDegreVelocite(double degreeDrift) {
	_degreVelocite = degreeDrift;
}

void automobile::setVirage(int virage) {
	_virage = virage;
}

void automobile::setKeys(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right)
{
	_autoControles[0] = up;
	_autoControles[1] = down;
	_autoControles[2] = left;
	_autoControles[3] = right;
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
double automobile::convertDegreeRadian(double degree) {
	return 2 * PI * (degree / 360);
}

//Effectue un virage selon l'angle actuel et la direction du virage désirée
void automobile::effectuerVirage()
{
	//Gauche
	if (_virage == 1)
	{
		_degre = _degre - _angleIncrementation;
	}
	//Droite
	else if (_virage == 2)
	{
		_degre = _degre + _angleIncrementation;
	}
}

//Ajuste la vélocité basée sur la direction désirée et le temps écoulé
void automobile::effectuerVelocite(double tempsDelta)
{
	//Si on avance
	if (_derniereDirection == 1)
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
	else if (_derniereDirection == 0)
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

//Décélération naturelle de la vélocité
void automobile::velociteAffaiblir(float multiple)
{
	_velociteX *= (_vitesseAffaiblir - multiple);
	_velociteY *= (_vitesseAffaiblir - multiple);
}

//Gère la collision d'une auto
void automobile::collisionMurs()
{
	if (_derniereDirection == 1)
		if (_velociteX > 0 && _velociteY > 0)
		{
			_velociteX = -(_velociteX / 2);
			_velociteY = -(_velociteY / 2);
		}

		else if (_derniereDirection == 0)
			if (_velociteX < 0 && _velociteY < 0)
			{
				_velociteX = -(_velociteX / 2);
				_velociteY = -(_velociteY / 2);
			}
}

//Gère la collision d'une auto vers une autre auto
void automobile::collisionAuto(automobile &destination)
{
	if (abs(_velociteX) + abs(_velociteY) > abs(destination.getVelociteX()) + abs(destination.getVelociteY()))
	{
		_velociteX -= _velociteX / 2;
		_velociteY -= _velociteY / 2;

		destination.setVelociteX(_velociteX*2);
		destination.setVelociteY(_velociteY*2);
		destination.setDegreVelocite(_degreVelocite);
	}
}

//Applique une simulation de "Drift" à l'auto, selon sa vitesse
void automobile::calculDrift()
{
	double velociteAbsolue = (abs(_velociteX) + abs(_velociteY)) / 2;

	if (velociteAbsolue < 10)
		_degreVelocite = _degre;

	else if (_degreVelocite + 90 < _degre || _degreVelocite - 90 > _degre)
	{
		if (_degreVelocite < _degre && velociteAbsolue != 0)
			_degreVelocite += (350 / (velociteAbsolue / 10));

		if (_degreVelocite > _degre && velociteAbsolue != 0)
			_degreVelocite -= (350 / (velociteAbsolue / 10));
	}

	else
	{
		if (_degreVelocite < _degre && velociteAbsolue != 0)
			_degreVelocite += (350 / (velociteAbsolue / 1.6));

		if (_degreVelocite > _degre && velociteAbsolue != 0)
			_degreVelocite -= (350 / (velociteAbsolue / 1.6));
	}
}