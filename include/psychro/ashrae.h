#ifndef _Ashrae_h
#define _Ashrae_h

#include "gas_perfeito.h"

/*! \file Ashrae.h

\brief Arquivo de inclus�o onde est� definida a classe Ashrae
*/




/*! \brief Classe que implementa o modelo de mistura ar-vapor da Psycrhometrics: Theory and Practice publicada pela Ashrae em 1996.

A class Ashrae implementa todas as fun��es necess�rias para o c�lculo das propriedades do ar �mido segundo o livro:

[1] Psychrometrics: Theory and Practice, publicado pela ASHRAE em 1996. 

Na verdade este modelo de ar-vapor � baseado em dois artigos:

[2] R. W. Hyland e A. Wexler, "Formulations for the thermodynamic properties of dry air from 173.15K to 473.15K and of saturated moist air from 173.15K to 372.15K at pressures to 5MPa", ASHRAE Transactions 89(2A):520-535, 1983.

[3] R. W. Hyland e A. Wexler, "Formulations for the thermodynamic properties of the saturated phases of \f$H_2O\f$", ASHRAE Transactions 89(2A):500:519, 1983.

Outros artigos consultados e referenciados que podem ser importantes na implementa��o dos m�todos aqui apresentados s�o:

[4] R. B. Stewart, R. T. Jacobsen e J. H. Becker; "Formulations for thermodynamic properties of moist air at low pressures as used for construction of new ASHRAE SI unit psychrometric charts", ASHRAE Transactions 89(2A):536-548, 1983.

[5] D. M. Himmelblau; "Solubilities of inert Gases in water: 0oC to near critical point of water", Journal of Chemical Engineering Data 5, 1960.

[6] George S. Kell, "Density, thermal expansivity, and compressibility of liquid water from 0oC to 150oC: correlations and tables for atmospheric pressure and saturation reviewed and expressed on 1968 temperature scale", Journal of chemical and engineering data Vol 20, No 1, 1975.

De uma maneira geral, os m�todos aqui implementados valem para uma ampla faixa: -100oC - 200oC e de 0 a 5MPa. A equa��o de estado � uma equa��o virial. Na documenta��o dos elementos da classe, serpa utilizada a numera��o acima para referenciar a bibliografia. � interessante notar que, para facilitar a implementa��o, foi utilizado um sistema de unidades �nico que pode diferir da maneira documentada nas refer�ncias acima.

*/
class Ashrae: public GasPerfeito{
 public:
  

  Ashrae();
  virtual void set(double T, char ch, double umidade, double P);
  virtual double Z(double T, double P, double xv); // Compressibilidade
  
  

  // Fun��es de sa�da (calculam os par�metros de sa�da
  virtual double ENTHALPY(double T, double P);  	// Entalpia J/kg de ar seco
  virtual double VOLUME(double T, double P);		// Volume m3/kg de ar seco
  virtual double DENSITY(double T, double P);		// Massa espec�fica kg/m3
  //virtual double ENTROPY(double T, double P);		// Entropia
  
  virtual double WETBULB(double T, double P);		// Temperatura de bulbo �mido
  virtual double DEWPOINT(double T, double P);  	// Ponto de orvalho
  virtual double HUMRAT();		// Teor de umidade
  virtual double RELHUM(double T, double P);    	// Umidade relativa;
  virtual double MOLFRAC();		// Fra��o molar de vapor
  virtual int ERROR();   		// C�digo de erro.
  

  // Fun��es auxiliares:
  virtual double eFactor(double T, double P);	// Enhancement factor
  virtual double Pws(double T);  	// Press�o de satura��o de vapor
  virtual double Tws(double P);         // Temperatura de satura��o de vapor

  //virtual double Pws_s(double T);	// Press�o de satura��o de vapor
  //virtual double Pws_l(double T);	// Press�o de satura��o de vapor

  // Propriedades:
  // Entalpia:
  virtual double h_a_(double T, double P=101325.0);
  virtual double h_v_(double T);
  virtual double h_l_(double T);
  virtual double h_s_(double T);
  virtual double h_f_(double T);
  virtual double h_(double T, double P, double xv);

  // volume:
  virtual double v_a_(double T, double P);
  virtual double v_v_(double T);
  virtual double v_(double T, double P, double xv);
  

  // Volume molar
  virtual double vM_a_(double T, double P);
  virtual double vM_v_(double T);
  virtual double vM_(double T, double P, double xv);

  // Densidade
  // volume:
  virtual double r_a_(double T, double P);
  virtual double r_v_(double T);
  virtual double r_(double T, double P, double xv);
  


  // Fun��es auxiliares
  /// Compressibilidade isot�rmica do gelo 1/Pa
  virtual double kappa_s(double T);
  /// Compressibilidade isot�rmica da �gua 1/Pa
  virtual double kappa_l(double T);
  /// Compressibilidade isot�rmica da agua (T>273.15) ou gelo (T<273.15) 1/Pa
  virtual double kappa_f(double T);

  /// Constante de Henry para o ar seco 1/Pa
  virtual double henryk (double T); 
  /// Constante de Henry do nitrog�nio 1/Pa
  virtual double henryk_N2 (double T);
  /// Constante de Henry do oxig�nio 1/Pa
  virtual double henryk_O2 (double T);

  /// Fun��o auxilar para o c�lculo do enhancement factor
  virtual double lnf(double Tk, double P, double xas);



  /// Coeficiente virial do ar puro
  virtual double Baa(double T);
  /// Constante virial da �gua pura
  virtual double Bww(double T);
  /// Segundo coeficiente virial cruzado ar-agua
  virtual double Baw(double T);
  /// Terceiro coeficiente virial do ar puro
  virtual double Caaa(double T);
  /// Terceiro coeficiente virial da �gua pura
  virtual double Cwww(double T);
  /// Terceiro coeficiente virial cruzado ar-�gua
  virtual double Caaw(double T);
  /// Terceiro coeficiente virial cruzado ar-�gua
  virtual double Caww(double T);
  
  /// Derivada do coeficiente virial do ar puro
  virtual double dBaa(double T);
  /// Derivada do constante virial da �gua pura
  virtual double dBww(double T);
  /// Derivada do segundo coeficiente virial cruzado ar-agua
  virtual double dBaw(double T);

  /// Derivada do terceiro coeficiente virial do ar puro
  virtual double dCaaa(double T);
  /// Derivada do terceiro coeficiente virial da �gua pura
  virtual double dCwww(double T);
  /// Derivada do terceiro coeficiente virial cruzado ar-�gua
  virtual double dCaaw(double T);
  /// Derivada do terceiro coeficiente virial cruzado ar-�gua
  virtual double dCaww(double T);

  /// Terceiro coeficiente virial da �gua pura
  virtual double Clinha(double T);
  /// Constante virial da �gua pura
  virtual double Blinha(double T);
  /// Derivada do constante virial da �gua pura
  virtual double dBlinha(double T);
  /// Derivada do terceiro coeficiente virial da �gua pura
  virtual double dClinha(double T);

  /// Coeficiente virial da mistura ar-agua
  virtual double Bm(double T, double xv);
  /// Terceiro coeficiente virial da mistura ar-�gua
  virtual double Cm(double T, double xv);
  
  /// Press�o de vapor saturado em equil�brio com gelo
  virtual double Pws_s(double T);  	// Press�o de satura��o de vapor
  /// Press�o de vapor saturado em equil�brio com �gua
  virtual double Pws_l(double T);  	// Press�o de satura��o de vapor

  /// Derivada da press�o de vapor saturado em equil�brio com gelo
  virtual double dPws_s(double T);  	// Press�o de satura��o de vapor
  /// Derivada da press�o de vapor saturado em equil�brio com �gua
  virtual double dPws_l(double T);  	// Press�o de satura��o de vapor
  /// Derivada da press�o de vapor saturado 
  virtual double dPws(double T);  	// Press�o de satura��o de vapor



  
  // Fun��es auxiliares:
  /// Fun��o auxiliar para o c�lculo do teor de umidade dado e a temperatura de bulbo �mido
  double CalcWfromB(double T, double B, double P);
  /// Fun��o auxiliar para o c�lculo do bulbo �mido
  double AuxWB(double w, double T, double B, double P);
  
  

};


#endif
