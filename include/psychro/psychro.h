/*! \file Psychro.h

\brief Interface para as classes utilizadas nos cálculos psicrométricos

Este arquivo fornece a classe base utilizada pela biblioteca de psicrometria. 
*/



// psychro.h
//
//
// Interface padrão para as classes utilizadas na psicrometria (Haverá apenas
// classes virtuais puras

#ifndef _psychro_h
#define _psychro_h

/*! \brief Classe base para todas as classes utilizadas no cálculo de propriedades do ar

A classe Psychro não possui nenhum código executável, apenas possui as interfaces de entrada e saída que qualuqer classe utilizada deve ter. Possui também as constantes básicas do cálculo psicrométrico. 

Esta biblioteca tem por objetivo ser de fácil utilização e fácil expansão. Novos modelos podem ser implementados e mesmo modelos incompletos (que não possuem todas as correlações necessárias) podem ser implementados utilizando correlações de outros modelos já implementados.

Todas as propriedades e constantes devem estar em unidades SI: kg, m, K, kmol, J, ...
*/
class Psychro{
 public:			// Por enquanto, pode mudar de pois

  // Constantes importantes

  static constexpr double Ma = 28.9635; /// Massa molecular equivalente do ar em kg/kmol, adotado de Giacomo
  static constexpr double Mv = 18.01528; /// Massa molecular da água em kg/kmol
  static constexpr double R = 8314.459848; // Constante universal dos gases J/(kmol.K)


  // Parâmetros importantes para caracterizar a mistura
  /// Fração molar de vapor
  double XV;			
  /// Teor de umidade
  double W;			
  /// Massa molecular média da mistura
  double M;			
  
  // Variáveis que armazenam os limites de aplicação do modelo
  /// Temperatura mínima do modelo (K)
  double Tmin;			
  /// Temperatura máxima do modelo (K)
  double Tmax;			
  /// Pressão mínima do modelo (Pa) geralmente 0
  double Pmin;			
  /// Pressão máxima do modelo (Pa)
  double Pmax;			

  
  /// Variável inteira que armazena o código de erro
  int errorcode;


  /// Funções básica de entrada de dados. Vai especificar a a mistura ar - vapor.
  virtual void set(double T, char ch, double umidade, double P)=0; 
  /// Função para cálculo da compressibilidade do ar úmido
  virtual double Z(double T, double P, double xv)=0; // Compressibilidade
  
  

  // Funções de saída (calculam os parâmetros de saída

  /// Calcula a entalpia em J/kg de uma mistura ar-vapor na temperatura T e pressão P
  virtual double ENTHALPY(double T, double P)=0;	// Entalpia J/kg de ar seco
  /// Calcula o volume específico do ar umido em \f$m^3/kg\f$ de ar seco
  virtual double VOLUME(double T, double P)=0;		// Volume m3/kg de ar seco
  /// Calcula a massa especifica do ar úmido em \f$kg/m^3\f$
  virtual double DENSITY(double T, double P)=0;		// Massa específica kg/m3
  /// Calcula a entropia do ár umido J/(kg.K)
  virtual double ENTROPY(double T, double P)=0;		// Entropia
  /// Calcula a temperatura de bulbo úmido do ar úmido em K
  virtual double WETBULB(double T, double P)=0;		// Temperatura de bulbo úmido
  /// Calcula a temperatura de ponto de orvalho do ar úmido em K
  virtual double DEWPOINT(double T, double P)=0;	// Ponto de orvalho
  /// Calcula o teor de umidade do ar
  virtual double HUMRAT()=0;		// Teor de umidade
  /// Calcula a umidade relativa do ar
  virtual double RELHUM(double T, double P)=0;	// Umidade relativa;
  /// Calcula a fração molar de vapor do ar umido
  virtual double MOLFRAC()=0;		// Fração molar de vapor
  /// Retorna o código de erro atual
  virtual int ERROR()=0;		// Código de erro.
  

  // Funções auxiliares:
  /// Calcula o enhancement factor
  virtual double eFactor(double T, double P)=0;	// Enhancement factor
  /// Calcula a pressão de vapor em Pa do vapor saturado
  virtual double Pws(double T)=0;	// Pressão de saturação de vapor
  /// Calcula a temperatura de saturação em K do vapor saturado
  virtual double Tws(double P)=0;	// Temperatura de saturação de vapor

  int FaixaT(double T){ if (T < Tmin || T > Tmax) return 10; return 0;}
  int FaixaP(double P){ if (P < Pmin || P > Pmax) return 11; return 0;}

  void ClearError(){errorcode = 0;}
};

#include "gas_perfeito.h"
#include "ashrae.h"
#include "giacomo.h"

#endif 

// "





