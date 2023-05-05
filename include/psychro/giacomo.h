/*! \file Giacomo.h 
\brief Arquivo de inclus�o do arquivo Giacomo.h

Este arquivo cont�m a defini��o da classe Giacomo.

*/



// Giacomo.h

// Implementa a equa��o de estado de Giacommo


#ifndef _Giacomo_h
#define _Giacomo_h




// Receber� todas as propriedades de Ashrae mas reimplementar� as necess�rias...
/*! \brief Classe para c�lculos psicrom�tricos que utilzam a metodologia de Giacomo.

O artigo 

[1] P. Giacomo, "Equation for the Determination of the Density of Moist Air (1981)", Metrologia 18, 33-40, 1982.

possui equa��es que permitem o c�lculo da densidade do ar �mido a partir da temperatura, press�o e temperatura de ponto de orvalho/umidade relativa. Estas equa��es s�o v�lidas para press�es variando de 60kPa a 110kPa e temperaturas variando de 15 a 27 oC.

A metodologia de Giacomo � bem tradicioanal nos meios metrol�gicos e j� foi amplamente testada. No entanto, a faixa � extremamente restrita e num dia de ver�o quente, no t�nel de vento do IPT a temperatura pode facilmente extrapolar estes limites. Outra dificuldade � que os tipos de entrada de dados e sa�das s�o muito restritas. Herdando as caracter�sticas da classe Ashrae, pode-se ter o melhor dos dois mundos: utilizam-se as fun��es de Giacomo onde poss�vel e no resto adotam-se as equa��es da ASHRAE.
*/
class Giacomo: public Ashrae{
 public:
  
  virtual double Z(double T, double P, double xv); // Compressibilidade
  virtual double Pws(double T);  	// Press�o de satura��o de vapor
  virtual double eFactor(double T, double P);	// Enhancement factor
  
};  
  
#endif
