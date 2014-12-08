# Stellar Structure

A simple yet powerful tool for solving numerically, the fundamental equations of stellar structure. It uses the Runge-Kutta fourth order method (commonly known as RK4) to express the mass, density and pressure as a function of the star's radius.

Throughout this program the following assumptions were made
* Spherical symmetry. So the value of any function at a specific point, depends only in its distance from the center of the star.
* The star is isolated in space. 
* The star is in a state of hydrostatic equilibrium.

## Equations

A comprehensive list of the equations solved and the constants that are required to run the program, can be found [here] (https://www.dropbox.com/s/ilaf5tz9b2flfkv/equations.pdf?dl=0). In regards to density, the star was modeled as a polytrope. Polytropes are self-gravitating gaseous spheres that are very useful as crude approximation to more realistic stellar models. A detailed discussion on polytropes can be found [in this document] (http://www.astro.princeton.edu/~gk/A403/polytrop.pdf "Polytropes").

## How to compile

From the `/stellar-structure` directory (wherever you decide to put it) compile with

```
makefile 
```

To use the program, edit the `boundaryConditions.txt` file with the data of a main sequence star of your choice. Then run

```
./stellarStructure 
```

The provided `boundaryConditions.txt` has the data of the Sun.

## Output

The program generates three ".dat" files, one for each funtion (mass, density, pressure). The file has two columns in the form

| Radius | Function |

You can see a plot of a typical output [here] (https://www.dropbox.com/s/69w10ssrumwlnhx/typicalOutput.pdf?dl=0 "Typical Output").

## To do list

* Add the radiative transfer equation
* Add more functions (such as temperature, luminosity, etc.)

## License
MIT
