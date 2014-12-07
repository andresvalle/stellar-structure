/* These are the prototypes of the functions for Stellar Structure */

#ifndef SSFUNCTIONS_H
#define SSFUNCTIONS_H

//Constants
double step; //Step size for the RK4
double polytropicConstant;
const double pi = 3.141592653589793238463;
const double gravitationalConstant = 6.67384e-11;
const double polytropicIndex = 0.6; //It is actually the inverse of the Index. This value is valid for main sequence stars, see ReadMe file.


//Prototypes
double massFunction( double , double , double );
double massDerivative( double , double , double );
double densityFunction( double );
double pressureFunction( double , double , double , double );
double pressureDerivative( double , double , double , double );

#endif
