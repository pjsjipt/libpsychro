#include "Giacomo.h"
#include <iostream>

using namespace std;


int main(){


  Giacomo g;
  
  double T = 300.15;
  double P = 60000.0;
  double R = 0.1;

  
  g.set(T, 'R', R, P);

  cout << g.Z(T, P, g.XV) << endl;

}





  
