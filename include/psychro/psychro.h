/*! \file Psychro.h

\brief Interface para as classes utilizadas nos c�lculos psicrom�tricos

Este arquivo fornece a classe base utilizada pela biblioteca de psicrometria. 
*/



// psychro.h
//
//
// Interface padr�o para as classes utilizadas na psicrometria (Haver� apenas
// classes virtuais puras

#ifndef _psychro_h
#define _psychro_h

/*! \brief Classe base para todas as classes utilizadas no c�lculo de propriedades do ar

A classe Psychro n�o possui nenhum c�digo execut�vel, apenas possui as interfaces de entrada e sa�da que qualuqer classe utilizada deve ter. Possui tamb�m as constantes b�sicas do c�lculo psicrom�trico. 

Esta biblioteca tem por objetivo ser de f�cil utiliza��o e f�cil expans�o. Novos modelos podem ser implementados e mesmo modelos incompletos (que n�o possuem todas as correla��es necess�rias) podem ser implementados utilizando correla��es de outros modelos j� implementados.

Todas as propriedades e constantes devem estar em unidades SI: kg, m, K, kmol, J, ...
*/
class Psychro{
 public:			// Por enquanto, pode mudar de pois

  // Constantes importantes

  static constexpr double Ma = 28.9635; /// Massa molecular equivalente do ar em kg/kmol, adotado de Giacomo
  static constexpr double Mv = 18.01528; /// Massa molecular da �gua em kg/kmol
  static constexpr double R = 8314.459848; // Constante universal dos gases J/(kmol.K)


  // Par�metros importantes para caracterizar a mistura
  /// Fra��o molar de vapor
  double XV;			
  /// Teor de umidade
  double W;			
  /// Massa molecular m�dia da mistura
  double M;			
  
  // Vari�veis que armazenam os limites de aplica��o do modelo
  /// Temperatura m�nima do modelo (K)
  double Tmin;			
  /// Temperatura m�xima do modelo (K)
  double Tmax;			
  /// Press�o m�nima do modelo (Pa) geralmente 0
  double Pmin;			
  /// Press�o m�xima do modelo (Pa)
  double Pmax;			

  
  /// Vari�vel inteira que armazena o c�digo de erro
  int errorcode;


  /// Fun��es b�sica de entrada de dados. Vai especificar a a mistura ar - vapor.
  virtual void set(double T, char ch, double umidade, double P)=0; 
  /// Fun��o para c�lculo da compressibilidade do ar �mido
  virtual double Z(double T, double P, double xv)=0; // Compressibilidade
  
  

  // Fun��es de sa�da (calculam os par�metros de sa�da

  /// Calcula a entalpia em J/kg de uma mistura ar-vapor na temperatura T e press�o P
  virtual double ENTHALPY(double T, double P)=0;	// Entalpia J/kg de ar seco
  /// Calcula o volume espec�fico do ar umido em \f$m^3/kg\f$ de ar seco
  virtual double VOLUME(double T, double P)=0;		// Volume m3/kg de ar seco
  /// Calcula a massa especifica do ar �mido em \f$kg/m^3\f$
  virtual double DENSITY(double T, double P)=0;		// Massa espec�fica kg/m3
  /// Calcula a entropia do �r umido J/(kg.K)
  virtual double ENTROPY(double T, double P)=0;		// Entropia
  /// Calcula a temperatura de bulbo �mido do ar �mido em K
  virtual double WETBULB(double T, double P)=0;		// Temperatura de bulbo �mido
  /// Calcula a temperatura de ponto de orvalho do ar �mido em K
  virtual double DEWPOINT(double T, double P)=0;	// Ponto de orvalho
  /// Calcula o teor de umidade do ar
  virtual double HUMRAT()=0;		// Teor de umidade
  /// Calcula a umidade relativa do ar
  virtual double RELHUM(double T, double P)=0;	// Umidade relativa;
  /// Calcula a fra��o molar de vapor do ar umido
  virtual double MOLFRAC()=0;		// Fra��o molar de vapor
  /// Retorna o c�digo de erro atual
  virtual int ERROR()=0;		// C�digo de erro.
  

  // Fun��es auxiliares:
  /// Calcula o enhancement factor
  virtual double eFactor(double T, double P)=0;	// Enhancement factor
  /// Calcula a press�o de vapor em Pa do vapor saturado
  virtual double Pws(double T)=0;	// Press�o de satura��o de vapor
  /// Calcula a temperatura de satura��o em K do vapor saturado
  virtual double Tws(double P)=0;	// Temperatura de satura��o de vapor

  int FaixaT(double T){ if (T < Tmin || T > Tmax) return 10; return 0;}
  int FaixaP(double P){ if (P < Pmin || P > Pmax) return 11; return 0;}

  void ClearError(){errorcode = 0;}
};

#include "gas_perfeito.h"
#include "ashrae.h"
#include "giacomo.h"

#endif 

// "





