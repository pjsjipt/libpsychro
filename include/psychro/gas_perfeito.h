// GasPerfeito.h
// Implementa o modelo de gás perfeito linear para a mistura ar vapor

/*! \file GasPerfeito.h
\brief Modelo de gás perfeito para a mistura ar-vapor

Neste arquivo está a definição da classe GasPerfeito.
*/


#ifndef _gas_perfeito_h
#define _gas_perfeito_h

/*! \brief Modelo de gás perfeito para mistura ar vapor

A class GasPerfeito apresenta o modelo mais simples possível para a mistura ar-vapor. A compressibilidade e o enhancement factor valem 1 e os calores especificos são constantes. As correlações utilizadas serão explicadas onde forem utilizadas.
*/ 
class GasPerfeito: public Psychro{
 public:

  /// Construtor padrão - define as faixas de aplicação do modelo
  GasPerfeito();
  /// Funções básica de entrada de dados. Vai especificar a a mistura ar - vapor.
  virtual void set(double T, char ch, double umidade, double P);
  /// Função para cálculo da compressibilidade do ar úmido
  virtual double Z(double T, double P, double xv); // Compressibilidade
  
  

  // Funções de saída (calculam os parâmetros de saída
  /// Calcula a entalpia em J/kg de uma mistura ar-vapor na temperatura T e pressão P
  virtual double ENTHALPY(double T, double P);	// Entalpia J/kg de ar seco
  /// Calcula o volume específico do ar umido em \f$m^3/kg\f$ de ar seco
  virtual double VOLUME(double T, double P);		// Volume m3/kg de ar seco
  /// Calcula a massa especifica do ar úmido em \f$kg/m^3\f$
  virtual double DENSITY(double T, double P);		// Massa específica kg/m3
  /// Calcula a entropia do ár umido J/(kg.K)
  virtual double ENTROPY(double T, double P);		// Entropia
  /// Calcula a temperatura de bulbo úmido do ar úmido em K
  virtual double WETBULB(double T, double P);		// Temperatura de bulbo úmido
  /// Calcula a temperatura de ponto de orvalho do ar úmido em K
  virtual double DEWPOINT(double T, double P);	// Ponto de orvalho
  /// Calcula o teor de umidade do ar
  virtual double HUMRAT();		// Teor de umidade
  /// Calcula a umidade relativa do ar
  virtual double RELHUM(double T, double P);	// Umidade relativa;
  /// Calcula a fração molar de vapor do ar umido
  virtual double MOLFRAC();		// Fração molar de vapor
  /// Retorna o código de erro atual
  virtual int ERROR();		// Código de erro.
  

  // Funções auxiliares:

  /// Calcula o enhancement factor
  virtual double eFactor(double T, double P);	// Enhancement factor
  /// Calcula a pressão de vapor em Pa do vapor saturado
  virtual double Pws(double T);  	// Pressão de saturação de vapor
  /// Calcula a temperatura de saturação em K do vapor saturado
  virtual double Tws(double P);         // Temperatura de saturação de vapor


  // Propriedades:
  // Entalpia:
  /// Entalpia do ar seco
  virtual double h_a_(double T);
  /// Entalpia do vapor saturado
  virtual double h_v_(double T);
  /// Entalpia da água saturada
  virtual double h_l_(double T);
  /// Entalpia do gelo saturado
  virtual double h_s_(double T);
  /// Entalpia do gelo (T < 273.15K) ou água (T >= 273.15)
  virtual double h_f_(double T);
  /// Entalpia do ar úmido
  virtual double h_(double T, double xv);

  // volume:
  /// Volume específico do ar seco
  virtual double v_a_(double T, double P);
  /// Volume específico do vapor saturado
  virtual double v_v_(double T);
  /// Volume especifico da água saturada
  virtual double v_l_(double T);
  /// Volume especifico do gelo saturado
  virtual double v_s_(double T);
  /// Volume especifico da fase líquida (T>=273.15) ou sólida (T < 273.15) saturada
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
  
  // Entropia...  (ainda não implementado)


  /// Função auxiliar que faz o balanço de energia em um saturador adiabático. Ustilizado para calcular o TBU.
  double BcalcW(double b, double P, double T);
  

};


#endif
