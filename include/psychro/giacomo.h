/*! \file Giacomo.h 
\brief Arquivo de inclusão do arquivo Giacomo.h

Este arquivo contém a definição da classe Giacomo.

*/



// Giacomo.h

// Implementa a equação de estado de Giacommo


#ifndef _Giacomo_h
#define _Giacomo_h




// Receberá todas as propriedades de Ashrae mas reimplementará as necessárias...
/*! \brief Classe para cálculos psicrométricos que utilzam a metodologia de Giacomo.

O artigo 

[1] P. Giacomo, "Equation for the Determination of the Density of Moist Air (1981)", Metrologia 18, 33-40, 1982.

possui equações que permitem o cálculo da densidade do ar úmido a partir da temperatura, pressão e temperatura de ponto de orvalho/umidade relativa. Estas equações são válidas para pressões variando de 60kPa a 110kPa e temperaturas variando de 15 a 27 oC.

A metodologia de Giacomo é bem tradicioanal nos meios metrológicos e já foi amplamente testada. No entanto, a faixa é extremamente restrita e num dia de verão quente, no túnel de vento do IPT a temperatura pode facilmente extrapolar estes limites. Outra dificuldade é que os tipos de entrada de dados e saídas são muito restritas. Herdando as características da classe Ashrae, pode-se ter o melhor dos dois mundos: utilizam-se as funções de Giacomo onde possível e no resto adotam-se as equações da ASHRAE.
*/
class Giacomo: public Ashrae{
 public:
  
  virtual double Z(double T, double P, double xv); // Compressibilidade
  virtual double Pws(double T);  	// Pressão de saturação de vapor
  virtual double eFactor(double T, double P);	// Enhancement factor
  
};  
  
#endif
