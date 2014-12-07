/* Main file of Stellar Structure. */

#include <fstream> 
#include <iostream>
#include <string>
#include <sstream>
#include "Initialize.h"
#include "SSFunctions.h"
 

	using namespace std; //Mainly because YOLO


int main ( )
	{

//Getting the boundary conditions and other constants from a file
//The numbers are stored in 'numberArray'

	 	double numberArray[10] = { };  
		
		string fileName( "boundaryConditions.txt" );
		
		initialize( fileName , numberArray );

//Outs

		ofstream massOut, pressureOut, densityOut, salidaPotencial;

		//Output files are stored in folder "data"

		massOut.open ("./data/mass.dat");
		pressureOut.open ("./data/pressure.dat");
		densityOut.open ("./data/density.dat");

//Initial values

		double density = numberArray[0];
		double pressure = numberArray[1];
		double totalRadius = numberArray[2];
		double polytropicConstant = numberArray[3];
		double radius = 0;
		double mass = 0;
		
//Print initial values on screen
		
		cout << "Initial Conditions" << endl;
		cout << "Core Density" << "\t" << density << endl;
		cout << "Core Pressure" << "\t" << pressure << endl;
		cout << "Radius" << "\t" << totalRadius << endl;

		int iterationCount = 0, outFilter = 10;
		
		double stepSize = 1e5; //Step size for the RK4
		
		while ( radius <= totalRadius )

			{
				/* Due to the huge amount of calculations this program does, only some calculations will be printed to file.
				 * The program prints data each 'outFilter' cycle */
				
				if ( iterationCount % outFilter == 0 )
					{
						massOut << radius << "\t" << mass << endl;
						densityOut << radius << "\t" << density << endl;
						pressureOut << radius << "\t" << pressure << endl;

						/* Since pressure will approach zero when the radius is near the total radius
						 * it is necessary to adjust the step size to make sure that it is still "small"
						 * compared to the pressure value. Since this chage will create more values
						 * the 'outFilter' gets an adjustment as well. */

						if ( (stepSize / pressure) >= 1e-15 )
							{
								stepSize /= 10;
								outFilter *= 10;
							}
					}

				//Add the step size to the radius and update the counter

				radius += stepSize;
				iterationCount++;

				//Calculate the new values

				density = densityFunction( pressure , polytropicConstant );
				mass = massFunction( radius , mass , density , stepSize );
				pressure = pressureFunction( radius , pressure , mass , density , stepSize );

			}

		cout << "Iteration Count" << "\t" << iterationCount << endl;
		cout << "Final Step Size" << "\t" << stepSize << endl; //Only mere curiosity

		return 0;
	
	}
