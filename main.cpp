#include <fstream> 
#include <iomanip> 
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


	using namespace std;


//Constants
double paso;
const double pi=3.141592653589793238463;
const double constanteGravitacional=6.67384e-11;
const double inversoGama=0.6;
const double politropica=247799612;


//Prototipes
double funcionMasa(double , double , double );
double derivadaMasa(double , double , double );
double funcionDensidad( double );
double funcionPresion(double , double , double , double );
double derivadaPresion(double , double , double , double );
double derivadaPotencial ( double , double , double );
double funcionPotencial(double , double , double );


int main ()
	{

//lectura de condiciones iniciales
//
		string linea;
		ifstream condiciones ("initialConditions.txt");
		int contador=0;
	 	double numero[20] , temporal=0;  

		if (condiciones.is_open())
			{
				while ( getline (condiciones,linea) )
					{
						//Si la linea del archivo de condiciones iniciales comienza con
						// ### es un comentario
						if(linea[0] != '#' )
							{

								istringstream contenidoLinea( linea );
								
								while ( contenidoLinea >> temporal )
									{
										numero[contador]=temporal;
										contador++;
									}

							}
					}
				
				condiciones.close();
			}
		
		else cout << "No se pudo abrir el archivo."; 

//Salidas

		ofstream salidaMasa, salidaPresion, salidaDensidad, salidaPotencial;

		salidaMasa.open ("masa.dat");
		salidaPresion.open ("presion.dat");
		salidaDensidad.open ("densidad.dat");
		salidaPotencial.open ("potencial.dat");

//Valores inciales
//
		double densidad = numero[0];
		double presion = numero[1];
		double radioFinal = numero[2];
		double radio = 0;
		double masa = 0;
		double potencial = 9.65098e+11;
		
//Imprimir valores iniciales en la pantalla
		
		cout << "Condiciones Iniciales" << endl;
		cout << "Densidad en el centro" << "\t" << densidad << endl;
		cout << "Presión en el centro" << "\t" << presion << endl;
		cout << "Radio" << "\t" << radioFinal << endl;

		int contadorIteraciones=0, filtrarDatos=10;
		paso=1e5;
		
		while (radio <= radioFinal)

			{
				//Imprimir valores cada n cáclculos
				
				if ( contadorIteraciones % filtrarDatos == 0 )
					{
						salidaMasa << radio << "\t" << masa << endl;
						salidaDensidad << radio << "\t" << densidad << endl;
						salidaPresion << radio << "\t" << presion << endl;
						salidaPotencial << radio << "\t" << potencial << endl;

						if ( (paso / presion) >= 1e-12 )
							{
								paso /= 10;
								filtrarDatos *= 10;
							}
					}

				//Sumar el tamaño de paso

				radio += ::paso;
				contadorIteraciones++;

				//Calcular nuevos valores

				densidad = funcionDensidad( presion );
				masa = funcionMasa( radio , masa , densidad );
				presion = funcionPresion( radio , presion , masa , densidad );
				potencial = funcionPotencial( radio , potencial , masa);

			}

		cout << "Iteraciones Realizadas" << "\t" << contadorIteraciones << endl;
		cout << "Tamaño de paso final" << "\t" << paso << endl;

		return 0;
	
	}

//Masa

double derivadaMasa(double radio, double masa, double densidad)
	{
		double derivada = 4 * ::pi * pow ( radio , 2 ) * densidad ;
		
		return derivada;
	}

double funcionMasa(double x, double y, double densidad)
	{
		double k1,k2,k3,k4;
		double nuevaY;
		
		k1=derivadaMasa( x , y , densidad);
		k2=derivadaMasa(x+0.5* ::paso, y+ 0.5* ::paso * k1, densidad);
		k3=derivadaMasa(x+ 0.5 * ::paso, y + 0.5* ::paso *k2 , densidad);
		k4=derivadaMasa(x+ ::paso, y + ::paso *k3 , densidad );
	
		nuevaY = y + (::paso/6)*(k1+2*k2+2*k3+k4);

		return nuevaY;
	}

//Presión

double derivadaPresion(double radio, double presion , double masa, double densidad)
	{
		double derivada = -1 * ::constanteGravitacional * masa * ( 1 / pow ( radio , 2 ) ) * densidad ;
		
		return derivada;
	}

double funcionPresion(double x, double y, double masa, double densidad)
	{
		double k1,k2,k3,k4;
		double nuevaY;
		
		k1=derivadaPresion( x , y , masa, densidad);
		k2=derivadaPresion(x+0.5* ::paso, y+ 0.5* ::paso * k1, masa, densidad);
		k3=derivadaPresion(x+ 0.5 * ::paso, y + 0.5* ::paso *k2, masa , densidad);
		k4=derivadaPresion(x+ ::paso, y + ::paso *k3, masa , densidad );
	
		nuevaY = y + (::paso/6)*(k1+2*k2+2*k3+k4);

		return nuevaY;
	}


//Densidad
double funcionDensidad( double presion )
	{
		double nuevoValor, base;

		base = (presion / politropica);

		nuevoValor = pow ( base , inversoGama );
		
		return nuevoValor;
	}

//Potencial Gravitacional
double derivadaPotencial ( double radio, double potencial, double masa )
	{
		double derivada = -1 * ::constanteGravitacional * masa * ( 1 / pow ( radio , 2 ) ) ;
		
		return derivada;
	}

double funcionPotencial(double x, double y, double masa)
	{
		double k1,k2,k3,k4;
		double nuevaY;
		
		k1=derivadaPotencial( x , y , masa);
		k2=derivadaPotencial(x+0.5* ::paso, y+ 0.5* ::paso * k1, masa);
		k3=derivadaPotencial(x+ 0.5 * ::paso, y + 0.5* ::paso *k2, masa);
		k4=derivadaPotencial(x+ ::paso, y + ::paso *k3, masa );
	
		nuevaY = y + (::paso/6)*(k1+2*k2+2*k3+k4);

		return nuevaY;
	}
