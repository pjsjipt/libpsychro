#ifndef _Ashrae_h
#define _Ashrae_h

#include "gas_perfeito.h"

/*! \file Ashrae.h

\brief Arquivo de inclusão onde está definida a classe Ashrae
*/




/*! \brief Classe que implementa o modelo de mistura ar-vapor da Psycrhometrics: Theory and Practice publicada pela Ashrae em 1996.

A class Ashrae implementa todas as funções necessárias para o cálculo das propriedades do ar úmido segundo o livro:

[1] Psychrometrics: Theory and Practice, publicado pela ASHRAE em 1996. 

Na verdade este modelo de ar-vapor é baseado em dois artigos:

[2] R. W. Hyland e A. Wexler, "Formulations for the thermodynamic properties of dry air from 173.15K to 473.15K and of saturated moist air from 173.15K to 372.15K at pressures to 5MPa", ASHRAE Transactions 89(2A):520-535, 1983.

[3] R. W. Hyland e A. Wexler, "Formulations for the thermodynamic properties of the saturated phases of \f$H_2O\f$", ASHRAE Transactions 89(2A):500:519, 1983.

Outros artigos consultados e referenciados que podem ser importantes na implementação dos métodos aqui apresentados são:

[4] R. B. Stewart, R. T. Jacobsen e J. H. Becker; "Formulations for thermodynamic properties of moist air at low pressures as used for construction of new ASHRAE SI unit psychrometric charts", ASHRAE Transactions 89(2A):536-548, 1983.

[5] D. M. Himmelblau; "Solubilities of inert Gases in water: 0oC to near critical point of water", Journal of Chemical Engineering Data 5, 1960.

[6] George S. Kell, "Density, thermal expansivity, and compressibility of liquid water from 0oC to 150oC: correlations and tables for atmospheric pressure and saturation reviewed and expressed on 1968 temperature scale", Journal of chemical and engineering data Vol 20, No 1, 1975.

De uma maneira geral, os métodos aqui implementados valem para uma ampla faixa: -100oC - 200oC e de 0 a 5MPa. A equação de estado é uma equação virial. Na documentação dos elementos da classe, serpa utilizada a numeração acima para referenciar a bibliografia. É interessante notar que, para facilitar a implementação, foi utilizado um sistema de unidades único que pode diferir da maneira documentada nas referências acima.

*/
class Ashrae: public GasPerfeito{
 public:
  

  Ashrae();
  virtual void set(double T, char ch, double umidade, double P);
  virtual double Z(double T, double P, double xv); // Compressibilidade
  
  

  // Funções de saída (calculam os parâmetros de saída
  virtual double ENTHALPY(double T, double P);  	// Entalpia J/kg de ar seco
  virtual double VOLUME(double T, double P);		// Volume m3/kg de ar seco
  virtual double DENSITY(double T, double P);		// Massa específica kg/m3
  //virtual double ENTROPY(double T, double P);		// Entropia
  
  virtual double WETBULB(double T, double P);		// Temperatura de bulbo úmido
  virtual double DEWPOINT(double T, double P);  	// Ponto de orvalho
  virtual double HUMRAT();		// Teor de umidade
  virtual double RELHUM(double T, double P);    	// Umidade relativa;
  virtual double MOLFRAC();		// Fração molar de vapor
  virtual int ERROR();   		// Código de erro.
  

  // Funções auxiliares:
  virtual double eFactor(double T, double P);	// Enhancement factor
  virtual double Pws(double T);  	// Pressão de saturação de vapor
  virtual double Tws(double P);         // Temperatura de saturação de vapor

  //virtual double Pws_s(double T);	// Pressão de saturação de vapor
  //virtual double Pws_l(double T);	// Pressão de saturação de vapor

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
  


  // Funções auxiliares
  /// Compressibilidade isotérmica do gelo 1/Pa
  virtual double kappa_s(double T);
  /// Compressibilidade isotérmica da água 1/Pa
  virtual double kappa_l(double T);
  /// Compressibilidade isotérmica da agua (T>273.15) ou gelo (T<273.15) 1/Pa
  virtual double kappa_f(double T);

  /// Constante de Henry para o ar seco 1/Pa
  virtual double henryk (double T); 
  /// Constante de Henry do nitrogênio 1/Pa
  virtual double henryk_N2 (double T);
  /// Constante de Henry do oxigênio 1/Pa
  virtual double henryk_O2 (double T);

  /// Função auxilar para o cálculo do enhancement factor
  virtual double lnf(double Tk, double P, double xas);



  /// Coeficiente virial do ar puro
  virtual double Baa(double T);
  /// Constante virial da água pura
  virtual double Bww(double T);
  /// Segundo coeficiente virial cruzado ar-agua
  virtual double Baw(double T);
  /// Terceiro coeficiente virial do ar puro
  virtual double Caaa(double T);
  /// Terceiro coeficiente virial da água pura
  virtual double Cwww(double T);
  /// Terceiro coeficiente virial cruzado ar-água
  virtual double Caaw(double T);
  /// Terceiro coeficiente virial cruzado ar-água
  virtual double Caww(double T);
  
  /// Derivada do coeficiente virial do ar puro
  virtual double dBaa(double T);
  /// Derivada do constante virial da água pura
  virtual double dBww(double T);
  /// Derivada do segundo coeficiente virial cruzado ar-agua
  virtual double dBaw(double T);

  /// Derivada do terceiro coeficiente virial do ar puro
  virtual double dCaaa(double T);
  /// Derivada do terceiro coeficiente virial da água pura
  virtual double dCwww(double T);
  /// Derivada do terceiro coeficiente virial cruzado ar-água
  virtual double dCaaw(double T);
  /// Derivada do terceiro coeficiente virial cruzado ar-água
  virtual double dCaww(double T);

  /// Terceiro coeficiente virial da água pura
  virtual double Clinha(double T);
  /// Constante virial da água pura
  virtual double Blinha(double T);
  /// Derivada do constante virial da água pura
  virtual double dBlinha(double T);
  /// Derivada do terceiro coeficiente virial da água pura
  virtual double dClinha(double T);

  /// Coeficiente virial da mistura ar-agua
  virtual double Bm(double T, double xv);
  /// Terceiro coeficiente virial da mistura ar-água
  virtual double Cm(double T, double xv);
  
  /// Pressão de vapor saturado em equilíbrio com gelo
  virtual double Pws_s(double T);  	// Pressão de saturação de vapor
  /// Pressão de vapor saturado em equilíbrio com água
  virtual double Pws_l(double T);  	// Pressão de saturação de vapor

  /// Derivada da pressão de vapor saturado em equilíbrio com gelo
  virtual double dPws_s(double T);  	// Pressão de saturação de vapor
  /// Derivada da pressão de vapor saturado em equilíbrio com água
  virtual double dPws_l(double T);  	// Pressão de saturação de vapor
  /// Derivada da pressão de vapor saturado 
  virtual double dPws(double T);  	// Pressão de saturação de vapor



  
  // Funções auxiliares:
  /// Função auxiliar para o cálculo do teor de umidade dado e a temperatura de bulbo úmido
  double CalcWfromB(double T, double B, double P);
  /// Função auxiliar para o cálculo do bulbo úmido
  double AuxWB(double w, double T, double B, double P);
  
  

};


#endif
