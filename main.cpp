#include <fstream> 
#include <iomanip> 
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


	using namespace std;


//Constants
double step;
double polytropicConstant;
const double pi = 3.141592653589793238463;
const double gravitationalConstant = 6.67384e-11;
const double polytropicIndex = 0.6;


//Prototipes
double massFunction(double , double , double );
double massDerivative(double , double , double );
double densityFunction( double );
double pressureFunction(double , double , double , double );
double pressureDerivative(double , double , double , double );


int main ( )
	{

//lectura de condiciones iniciales

		string line;
		ifstream conditions("boundaryConditions.txt");
		int counter=0;
	 	double number[20] , temp = 0;  

		if ( conditions.is_open() )
			{
				while ( getline ( conditions , line ) )
					{
						//Si la linea del archivo de condiciones iniciales comienza con
						// ### es un comentario
						if( line[0] != '#' )
							{

								istringstream contenidoLinea( line );
								
								while ( contenidoLinea >> temp )
									{
										number[counter]=temp;
										counter++;
									}

							}
					}
				
				conditions.close();
			}
		
		else 
			{	
				cout << "Unable to read file.";
				return 1;
			}

//Salidas

		ofstream massOut, pressureOut, densityOut, salidaPotencial;

		massOut.open ("mass.dat");
		pressureOut.open ("pressure.dat");
		densityOut.open ("density.dat");

//Valores inciales
//
		double density = number[0];
		double pressure = number[1];
		double totalRadius = number[2];
		polytropicConstant = number[3];
		double radius = 0;
		double mass = 0;
		
//Imprimir valores iniciales en la pantalla
		
		cout << "Condiciones Iniciales" << endl;
		cout << "Densidad en el centro" << "\t" << density << endl;
		cout << "Presión en el centro" << "\t" << pressure << endl;
		cout << "Radio" << "\t" << totalRadius << endl;

		int iterationCount = 0, outFilter = 10;
		step = 1e5;
		
		while ( radius <= totalRadius )

			{
				//Imprimir valores cada n cáclculos
				
				if ( iterationCount % outFilter == 0 )
					{
						massOut << radius << "\t" << mass << endl;
						densityOut << radius << "\t" << density << endl;
						pressureOut << radius << "\t" << pressure << endl;

						if ( (step / pressure) >= 1e-12 )
							{
								step /= 10;
								outFilter *= 10;
							}
					}

				//Sumar el tamaño de step

				radius += step;
				iterationCount++;

				//Calcular nuevos valores

				density = densityFunction( pressure );
				mass = massFunction( radius , mass , density );
				pressure = pressureFunction( radius , pressure , mass , density );

			}

		cout << "Iteraciones Realizadas" << "\t" << iterationCount << endl;
		cout << "Tamaño de step final" << "\t" << step << endl;

		return 0;
	
	}

//Masa

double massDerivative(double radius, double mass, double density)
	{
		double derivative = 4 * ::pi * pow (radius , 2) * density ;
		
		return derivative;
	}

double massFunction(double x, double y, double density)
	{
		double k1,k2,k3,k4;
		double nuevaY;
		
		k1=massDerivative( x , y , density);
		k2=massDerivative(x+0.5* ::step , y+0.5*::step*k1, density);
		k3=massDerivative(x+ 0.5 * ::step, y + 0.5* ::step *k2 , density);
		k4=massDerivative(x+ ::step, y + ::step *k3 , density );
	
		nuevaY = y + (::step/6)*(k1+2*k2+2*k3+k4);

		return nuevaY;
	}

//Presión

double pressureDerivative(double radius, double pressure , double mass, double density)
	{
		double derivative = -1 * ::gravitationalConstant * mass * ( 1 / pow( radius , 2 ) ) * density ;
		
		return derivative;
	}

double pressureFunction(double x, double y, double mass, double density)
	{
		double k1,k2,k3,k4;
		double nuevaY;
		
		k1=pressureDerivative( x , y , mass, density);
		k2=pressureDerivative(x+0.5* ::step, y+ 0.5* ::step * k1, mass, density);
		k3=pressureDerivative(x+ 0.5 * ::step, y + 0.5* ::step *k2, mass , density);
		k4=pressureDerivative(x+ ::step, y + ::step *k3, mass , density );
	
		nuevaY = y + (::step/6)*(k1+2*k2+2*k3+k4);

		return nuevaY;
	}


//Densidad
double densityFunction( double pressure )
	{
		double nuevoValor, base;

		base = ( pressure / polytropicConstant );

		nuevoValor = pow( base , polytropicIndex );
		
		return nuevoValor;
	}
