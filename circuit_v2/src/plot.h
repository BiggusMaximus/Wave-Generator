#include "Plotter.h"

double x; // global variables
Plotter p; // create plotter

void plotterInitialization(){
    p.Begin(); // start plotter
  p.AddTimeGraph( "Voltage", 1500, "Sample", x );
}

void plot(double x, double y)
{
  x = 10*sin( 2.0*PI*( millis() / 5000.0 ) ); 
  p.Plot(); 
}