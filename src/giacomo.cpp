/*! \file Giacomo.cpp

\brief Implementa a classe Giacomo

Este arquivo possui as reimplementa��es dos m�todos para os quais o artigo de Giacomo[1] possui correla��es

*/

#include <cmath>
#include <psychro/psychro.h>

 
using namespace std;

/*! Fator de compressibilidade do ar �mido.  Rela��o retirada de [1] e v�lida na faixa de 60kPa - 110 kPa e 15oC-27oC. Esta � uma implementa��o expl�cita o que facilita o trabalho
\param T Temperatura K
\param P Press�o Pa
\param xv Fra��o molar de vapor
\return Fator de compressibilidade
*/
double Giacomo::Z(double T, double P, double xv){

  double t = T - 273.15;
  double a0 = 1.62419e-6;
  double a1 = -2.8969e-8;
  double a2 = 1.0880e-10;
  double b0 = 5.757e-6;
  double b1 = -2.589e-8;
  double c0 = 1.9297e-4;
  double c1 = -2.285e-6;
  double d = 1.73e-11;
  double e = -1.034e-8;

  return 1.0 - P/T * (a0 + a1*t + a2*t*t + (b0 + b1*t)*xv +
		      (c0 + c1*t)*xv*xv) + P*P/(T*T)*(d + e*xv*xv);
}


  


/*! Press�o de vapor de satura��o, Equa��o v�lida de 0oC a 27oC
\param T Temperatura em K
\return Press�o de satura��o em Pa
*/
double Giacomo::Pws(double T){

  double A = 1.2811805e-5;
  double B = -1.9509874e-2;
  double C = 34.04926034;
  double D = -6.3536311e3;

  return exp(A*T*T + B*T + C + D/T);
}

/*! Enhancement factor para press�es entre 60 e 110 kPa e temperaturas entre 0 e 30oC
\param T Temperatura K
\param P Press�o Pa
\return Enhancement factor
*/
double Giacomo::eFactor(double T, double P){

  double alfa = 1.00062;
  double beta = 3.14e-8;
  double gama = 5.6e-7;

  double t = T - 273.15;

  return(alfa + beta*P + gama*t*t);
}




