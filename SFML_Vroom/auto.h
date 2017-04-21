#pragma once

//Constantes
const double PI = atan(1) * 4;

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
	double getDegree();
	double getAngleIncrementation();
	void setDegree(double degree);
	double convertDegreeRadian(double degree);
};

automobile::automobile()
{
	_degree = 90;
	_radian = 0;
	_angleIncrementation = 5;
}

automobile::~automobile()
{

}

//==Get==

double automobile::getAngleIncrementation()
{
	return _angleIncrementation;
}

double automobile::getDegree()
{
	return _degree;
}

//==Set==

void automobile::setDegree(double degree)
{
	_degree = degree;
}

//(Fonction) Convertit un angle en degree vers un radian
double automobile::convertDegreeRadian(double degree)
{
	return 2 * PI * (degree / 360);
}