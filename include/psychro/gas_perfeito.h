// GasPerfeito.h
// Implementa o modelo de g�s perfeito linear para a mistura ar vapor

/*! \file GasPerfeito.h
\brief Modelo de g�s perfeito para a mistura ar-vapor

Neste arquivo est� a defini��o da classe GasPerfeito.
*/


#ifndef _gas_perfeito_h
#define _gas_perfeito_h

/*! \brief Modelo de g�s perfeito para mistura ar vapor

A class GasPerfeito apresenta o modelo mais simples poss�vel para a mistura ar-vapor. A compressibilidade e o enhancement factor valem 1 e os calores especificos s�o constantes. As correla��es utilizadas ser�o explicadas onde forem utilizadas.
*/ 
class GasPerfeito: public Psychro{
 public:

  /// Construtor padr�o - define as faixas de aplica��o do modelo
  GasPerfeito();
  /// Fun��es b�sica de entrada de dados. Vai especificar a a mistura ar - vapor.
  virtual void set(double T, char ch, double umidade, double P);
  /// Fun��o para c�lculo da compressibilidade do ar �mido
  virtual double Z(double T, double P, double xv); // Compressibilidade
  
  

  // Fun��es de sa�da (calculam os par�metros de sa�da
  /// Calcula a entalpia em J/kg de uma mistura ar-vapor na temperatura T e press�o P
  virtual double ENTHALPY(double T, double P);	// Entalpia J/kg de ar seco
  /// Calcula o volume espec�fico do ar umido em \f$m^3/kg\f$ de ar seco
  virtual double VOLUME(double T, double P);		// Volume m3/kg de ar seco
  /// Calcula a massa especifica do ar �mido em \f$kg/m^3\f$
  virtual double DENSITY(double T, double P);		// Massa espec�fica kg/m3
  /// Calcula a entropia do �r umido J/(kg.K)
  virtual double ENTROPY(double T, double P);		// Entropia
  /// Calcula a temperatura de bulbo �mido do ar �mido em K
  virtual double WETBULB(double T, double P);		// Temperatura de bulbo �mido
  /// Calcula a temperatura de ponto de orvalho do ar �mido em K
  virtual double DEWPOINT(double T, double P);	// Ponto de orvalho
  /// Calcula o teor de umidade do ar
  virtual double HUMRAT();		// Teor de umidade
  /// Calcula a umidade relativa do ar
  virtual double RELHUM(double T, double P);	// Umidade relativa;
  /// Calcula a fra��o molar de vapor do ar umido
  virtual double MOLFRAC();		// Fra��o molar de vapor
  /// Retorna o c�digo de erro atual
  virtual int ERROR();		// C�digo de erro.
  

  // Fun��es auxiliares:

  /// Calcula o enhancement factor
  virtual double eFactor(double T, double P);	// Enhancement factor
  /// Calcula a press�o de vapor em Pa do vapor saturado
  virtual double Pws(double T);  	// Press�o de satura��o de vapor
  /// Calcula a temperatura de satura��o em K do vapor saturado
  virtual double Tws(double P);         // Temperatura de satura��o de vapor


  // Propriedades:
  // Entalpia:
  /// Entalpia do ar seco
  virtual double h_a_(double T);
  /// Entalpia do vapor saturado
  virtual double h_v_(double T);
  /// Entalpia da �gua saturada
  virtual double h_l_(double T);
  /// Entalpia do gelo saturado
  virtual double h_s_(double T);
  /// Entalpia do gelo (T < 273.15K) ou �gua (T >= 273.15)
  virtual double h_f_(double T);
  /// Entalpia do ar �mido
  virtual double h_(double T, double xv);

  // volume:
  /// Volume espec�fico do ar seco
  virtual double v_a_(double T, double P);
  /// Volume espec�fico do vapor saturado
  virtual double v_v_(double T);
  /// Volume especifico da �gua saturada
  virtual double v_l_(double T);
  /// Volume especifico do gelo saturado
  virtual double v_s_(double T);
  /// Volume especifico da fase l�quida (T>=273.15) ou s�lida (T < 273.15) saturada
  virtual double v_f_(double T);
  /// Volume especifico do vapor saturado
  virtual double v_(double T, double P, double xv);
  

  // Volume molar
  //
  virtual double vM_a_(double T, double P);
  virtual double vM_v_(double T);
  virtual double vM_l_(double T);
  virtual double vM_s_(double T);
  virtual double vM_f_(double T);
  virtual double vM_(double T, double P, double xv);

  // Densidade
  // volume:
  virtual double r_a_(double T, double P);
  virtual double r_v_(double T);
  virtual double r_l_(double T);
  virtual double r_s_(double T);
  virtual double r_f_(double T);
  virtual double r_(double T, double P, double xv);
  
  // Entropia...  (ainda n�o implementado)


  /// Fun��o auxiliar que faz o balan�o de energia em um saturador adiab�tico. Ustilizado para calcular o TBU.
  double BcalcW(double b, double P, double T);
  

};


#endif
