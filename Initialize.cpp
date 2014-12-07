#include <fstream> 
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "Initialize.h"


	using namespace std;


/* This function reads the initial values in the text file and
 * stores them in a 'double' array.*/

void initialize( string fileName , double * number ) // 'number' is a pointer to the first element of the array
{
	string line;
	ifstream conditionsFile( fileName.c_str() ); 
	int counter = 0;
 	double temp = 0; 

	if ( conditionsFile.is_open() )
		{
			while ( getline ( conditionsFile , line ) )
				{
					// If the line starts with '#', then it is a comment and we ignore the line.
					if( line[0] != '#' )
						{
							//Put the content of each line in 'lineContent'
							istringstream lineContent( line );
							
							//Take each number in 'lineContent' and put it in an element of the array
							while ( lineContent >> temp )
								{
									number[counter] = temp;
									counter++;
								}

						}
				}
			
			conditionsFile.close();
		}
		
	else //If the file cannot be read
		{	
			cout << "Unable to read file.";
			exit(1);
		}
}
