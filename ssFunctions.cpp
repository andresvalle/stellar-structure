/* Definition of the Stellar Structure derivatives and their integrations
 * using RK4 */

#include <cmath>
#include "ssFunctions.h"


	using namespace std; //Because YOLO


//Mass

double massDerivative(double radius, double mass, double density)
	{
		double derivative = 4 * ::pi * pow (radius , 2) * density ;
		
		return derivative;
	}

	//RK4 integration
double massFunction(double radius, double mass, double density)
	{
		double k1,k2,k3,k4;
		double newMass;
		
		k1=massDerivative( radius , mass , density);
		k2=massDerivative( radius+0.5 * ::step , mass+0.5*::step*k1 , density);
		k3=massDerivative( radius+ 0.5 * ::step, mass + 0.5* ::step *k2 , density);
		k4=massDerivative( radius+ ::step , mass + ::step *k3 , density );
	
		newMass = mass + (::step/6)*(k1+2*k2+2*k3+k4);

		return newMass;
	}


//Pressure

double pressureDerivative(double radius, double pressure , double mass, double density)
	{
		double derivative = -1 * ::gravitationalConstant * mass * ( 1 / pow( radius , 2 ) ) * density ;
		
		return derivative;
	}

	//RK4 integration
double pressureFunction(double radius, double pressure, double mass, double density)
	{
		double k1,k2,k3,k4;
		double newPressure;
		
		k1=pressureDerivative( radius , pressure , mass , density);
		k2=pressureDerivative(radius+0.5* ::step , pressure+ 0.5* ::step * k1 , mass, density);
		k3=pressureDerivative(radius+ 0.5 * ::step , pressure + 0.5* ::step *k2 , mass , density);
		k4=pressureDerivative(radius+ ::step , pressure + ::step *k3 , mass , density );
	
		newPressure = pressure + (::step/6)*(k1+2*k2+2*k3+k4);

		return newPressure;
	}


//Density, polytropic fluid equation
double densityFunction( double pressure )
	{
		double newValue, base;

		base = ( pressure / polytropicConstant );

		newValue = pow( base , polytropicIndex );
		
		return newValue;
	}
