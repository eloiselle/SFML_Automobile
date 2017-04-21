#pragma once

//Constantes
const double PI = atan(1) * 4;

//Prototypes


//Classe
class automobile
{
private:
	double _degree;
	double _radian;
	double _angleIncrementation;

public:
	automobile();
	~automobile();
	int getDegree();
	int getAngleIncrementation();
	void setDegree(int degree);
	double convertDegreeRadian(double degree);
};

automobile::automobile()
{
	_degree = 90;
	_radian = 0;
	_angleIncrementation = 0.01;
}

automobile::~automobile()
{

}

//==Get==

int automobile::getAngleIncrementation()
{
	return _angleIncrementation;
}

int automobile::getDegree()
{
	return _degree;
}

//==Set==

void automobile::setDegree(int degree)
{
	_degree = degree;
}

//(Fonction) Convertit un angle en degree vers un radian
double automobile::convertDegreeRadian(double degree)
{
	return 2 * PI * (degree / 360);
}