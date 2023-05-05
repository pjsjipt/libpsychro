#include <cmath>

#include <psychro/psychro.h>

/*! \file GasPerfeito.cpp
  \brief Este arquivo implementa as classe GasPerfeito

Este arquivo implementa a classe g�s perfeito que implementa um modelo de g�s perfeito para uma mistura vapor-ar. Este � um modelo muito simples mas apresenta resultados bons em algumas circunst�ncias
*/



using namespace std;

/*!
  Construtor padr�o. Serve apenas para estabelecer os limites de aplia��o. Os limites na temperatura s�o dados pela correla��o de temperatura de satura��o de vapor. Observe que este � um modelo aproximado que sup�e o ar �mido uma mistura de gases perfeitos, ou seja, n�o existe um limite para a press�o. Arbitrariamente foi estabelecido um limite de 10MPa.
*/
GasPerfeito::GasPerfeito(){
  Tmin = 213.15;
  Tmax = 647.15;
  Pmin = 0.0;
  Pmax = 10e6;
}


/*!
  A compressibilidade do g�s perfeito �, por defini��o 1. Portanto, esta fun��o n�o � usada
  \param TT Temperatura em K
  \param PP Press�o em Pa
  \param xv Fra��o molar
  \return Compressibilidade do g�s
*/
double GasPerfeito::Z(double TT, double PP, double xv){
  return 1.0;
}

/*! Esta fun��o retorna o enhancement factor que neste caso vale 1 (g�s perfeito). Implementado apenas para manter a estrutura da biblioteca.
  \param TT Temperatura do ar �mido em K
  \param PP Press�o em Pa
  \return Retorna o enhancement factor. Neste caso, g�s perfeito, retorna 1
 */
double GasPerfeito::eFactor(double TT, double PP){
  return 1.0;
}


// Entalpia do ar �mido (linear)

/*! Entalpia do ar seco em J/kg. Apenas um ajuste linear dos valores pr�ximos a 273.15K
  \param T Temperatura em K
  \return A entalpia do ar seco em J/kg
 */
double GasPerfeito::h_a_(double T){
  return 1006*(T - 273.15);
}


// Entalpia do vapor   
/*! Entalpia do vapor saturado em J/kg. Ajuste linear de valores pr�ximos � temperatura ambiente
  \param T Temperatura em K
  \return A entalpia do vapor saturado em J/kg
 */
double GasPerfeito::h_v_(double T){
  return 1000.0 * (2501.0 + 1.805*(T-273.15));
}

// Entalpia do ar �mido
/*! Entalpia do ar �mido. Soma as contribui��es do vapor saturado e ar seco
\param T Temperatura em K
\param xv Fra��o molar de vapor
  \return A entalpia do ar �mido em J/kg
*/
double GasPerfeito::h_(double T, double xv){
  double xa = 1.0 - xv;
  double M = xa * Ma + xv * Mv;
  
  return (xa * h_a_(T) * Ma + xv * h_v_(T) * Mv) / (xa*Ma + xv*Mv);
  
}

/*! Entalpia do gelo. V�lido para T < 273.15
\param T Temperatura em K
  \return A entalpia do gelo saturado em J/kg
*/
double GasPerfeito::h_s_(double T){
      return 1000.0 * (334.402 + 1.95645*(T-273.15));  // Gelo
}

/*! Entalpia da �gua l�quida saturada, T > 273.15
  \param T Temperatura em K
  \return A entalpia da �gua saturada em J/kg
*/
double GasPerfeito::h_l_(double T){
      return 1000.0 * (334.402 + 1.95645*(T-273.15));  // Gelo
}
 
/*! Entalpia da fase n�o gasosa em J/kg. Para T<273.15, isto corresponde ao gelo. Para T > 273.15, a fase n�o gasosa corresponde � �gua.
  \param T Temperatura em K
  \return A entalpia da fase n�o gasosa da �gua em J/kg
*/
double GasPerfeito::h_f_(double T){
    if (T<273.15)
      return 1000.0 * (334.402 + 1.95645*(T-273.15));  // Gelo
    else
      return (4186*(T-273.15));	// �gua
}




/*! Esta fun��o calcula a temperatura de satura��o de vapor em K. Neste caso, a correla��o foi retirada de
ASHRAE, Psychrometrics: Theory and Practice, 1996 (Tabela 16).

Cuidado com erros no livro. Modifica��es feitas por Paulo Jos� Saiz Jabardo, IPT em 15/02/2002

A correla��o � v�lida para p = 1 Pa a p = 1555099
\param p Press�o do vapor saturado em Pa
\return Temperatura do vapor saturado em K
*/
double GasPerfeito::Tws(double p)
{
  double P = p;
  double beta, T;
  double E, F, G, H, K;

  if ( 1.0 <= P && P < 611.0)
    {
      E = 0.1004926534E-2;
      F = 0.1392917633E-2;
      G = 0.2815151574E0;
      H = 0.7311621119E1;
      K = 0.2125893734E3;
    }
  else if (611.0 <= P && P < 12350.0)
    {
      E = 0.5031062503E-2;
      F = -0.8826779380E-1;
      G = 0.1243688446E1;
      H = 0.3388534296E1;
      K = 0.2150077993E3;
    }
  else if (12350.0 <= P && P < 101420.0)
    {
      E = 0.0121404;
      F = -0.356801;
      G = 5.06151;
      H = -20.8232;
      K = 272.789;
    }

  else if (101420.0 <= P && P < 476207.0)
    {
      E = 0.2467291016E-1;
      F = -0.9367112883E0;
      G = 0.1514142334E2;
      H = -0.9882417501E2;
      K = 0.4995092948E3;
    }
  else if (476207.0 <= P && P < 1555099.0)
    {
      E = 0.2748402484E-1;
      F = -0.1068661307E1;
      G = 0.1742964962E2;
      H = -0.1161208532E3;
      K = 0.5472618120E3;
    }
  else if (1555099.0 <= P && P <22089000.0)
    {
      E = 0.0;
      F = 0.428138;
      G = -12.6338;
      H = 146.784;
      K = -292.288;
    }
  else
    {
      // Fora dos limites
    }
  beta = log(P);

  T = E*beta*beta*beta*beta + F*beta*beta*beta + G*beta*beta + H*beta + K;
  return T;
  
  
}

/***************************************
 *               Pws                   *
 ***************************************/
// Esta fun��o retorna a press�o de satura��o da �gua em
// kPa (-50 a +100oC sobre �gua l�quida)

/*! Esta fun��o calcula a press�o de satura��o de vapor em Pa. Neste caso, a correla��o foi retirada de
ASHRAE, Psychrometrics: Theory and Practice, 1996 (Tabela 15).

Correla��o v�lida para temperaturas entre 213.15K e 473.15K e depois espandida at� 647.15K por Paulo Jos� Saiz Jabardo em 15/12/2002.
\param T Temperatura do vapor saturado em K
\return Press�o do vapor saturado em Pa
*/
double GasPerfeito::Pws(double T)
{



  // C�lculo da press�o de satura��o do vapor d�gua, tabela 15, ASHRAE
  double T_k;
  double A, B, C, D, alfa;

  T_k = T;
  

  if ( 213.149 <= T_k && T_k < 273.15)
    {
      A = -0.7297593707E-5;
      B = 0.5397420727E-2;
      C = 0.2069880620E2;
      D = -0.604227518E4;
    }
  else if (273.149 <= T_k && T_k < 322.15)
    {
      A = 0.1255001965E-4;
      B = -0.1923595289E-1;
      C = 0.2705101899E2;
      D = -0.6344011577E4;
    }
  else if (322.149 <= T_k && T_k < 373.15)
    {
      A = 0.1246732157E-4;
      B = -0.1915465806E-1;
      C = 0.2702388315E2;
      D = -0.6340941639E4;
    }
  else if (373.149 <= T_k && T_k < 423.15)
    {
      A = 0.1204507646E-4;
      B = -0.1866650553E-1;
      C = 0.2683629403E2;
      D = -0.6316972063E4;
    }
  else if (423.15 <= T_k && T_k < 473.15)
    {
      A = 0.1069730183E-4;
      B = -0.1698965754E-1;
      C = 0.2614073298E2;
      D = -0.622078230E4;
    }
  else if (473.149 <= T_k && T_k < 647.15)
    {
      A = 1.20064E-5;
      B = -0.0193912;
      C = 27.539;
      D = -6483.51;
    }


  alfa = A*T_k*T_k + B*T_k + C + D/T_k;
  return 1000*exp(alfa);
  
  
  
}



/*! Volume espec�fico do ar �mido. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \param xv Fra��o molar do vapor
  \return Volume espec�fico do ar �mido em \f$m^3/kg\f$
*/
double GasPerfeito::v_(double T, double P, double xv){
  double M = (1.0 - xv) * Ma + xv * Mv;
  return R*T/(P * M);
}

/*! Densidade do ar �mido. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \param xv Fra��o molar do vapor
  \return Densidade do ar �mido em \f$kg/m^3\f$
*/
double GasPerfeito::r_(double T, double P, double xv){
  return 1/v_(T,P, xv);
}

/*! Volume molar do ar �mido. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \param xv Fra��o molar do vapor
  \return Volume molar do ar �mido em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_(double T, double P, double xv){
  return R*T/P;
}

/*! Volume espec�fico do ar seco. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \return Volume espec�fico do ar seco em \f$m^3/kg\f$
*/
double GasPerfeito::v_a_(double T, double P){
  return R*T/(P*Ma);
}


/*! Densidade do ar seco. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \return Densidade do ar seco em \f$kg/m^3\f$
*/
double GasPerfeito::r_a_(double T, double P){
  return 1/v_a_(T,P);
}


/*! Volume molar do ar seco. 
  \param T Temperatura em K
  \param P Press�o em Pa
  \return Volume molar do ar seco em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_a_(double T, double P){
  return R*T/P;
}


/*! Volume espec�fico do vapor saturado. 
  \param T Temperatura em K
  \return Volume espec�fico em \f$m^3/kg\f$
*/
double GasPerfeito::v_v_(double T){
  double P = Pws(T);
  return R*T/(P*Mv);
}

/*! Densidade do vapor saturado. 
  \param T Temperatura em K
  \return Densidade em \f$kg/m^3\f$
*/
double GasPerfeito::r_v_(double T){
  return 1/v_v_(T);
}

/*! Volume molar do vapor saturado. 
  \param T Temperatura em K
  \return Volume  em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_v_(double T){
  return R*T/Pws(T);
}



/*! Volume espec�fico da �gua l�quida saturada para  273.15 < Tk < 473.15. 
  \param Tk Temperatura em K
  return Volume espec�fico em \f$m^3\f$
*/
double GasPerfeito::v_l_(double Tk){
  return 1/r_l_(Tk);
  
}

/*! Densidade da �gua l�quida saturada para  273.15 < Tk < 473.15. Correla��o retirada de 

R. W. Hyland e A. Wexler, Formulations for the Thermodynamic properties of the saturated phases of H2O from 173.15K to 473.15K, ASHRAE Transactions 89(2A):500-519.

\param Tk Temperatura em K
\return Densidade em \f$kg/m^3\f$
*/
double GasPerfeito::r_l_(double Tk){
  double termo1 = -0.2403360201e4 - 0.140758895e1*Tk + 0.1068287657e0*Tk*Tk -
    0.2914492351e-3*pow(Tk,3) + 0.373497936e-6*pow(Tk,4) - 0.21203787e-9*pow(Tk,5);

  double termo2 =  -0.3424442728e1 + 0.1619785e-1*Tk;

  return termo1 / termo2;

}

/*! Volume molar da �gua l�quida saturada, 273.15 < T < 473.15
  \param T Temperatura em K
  \return Volume molar em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_l_(double T){
  return v_l_(T) * Mv;
}

/*! Volume espec�fico do gelo saturado para  173.15 < Tk < 273.15. Correla��o retirada de 

R. W. Hyland e A. Wexler, Formulations for the Thermodynamic properties of the saturated phases of H2O from 173.15K to 473.15K, ASHRAE Transactions 89(2A):500-519.

\param Tk Temperatura em K
\return Volume espec�fico em \f$m^3/kg\f$
*/
double GasPerfeito::v_s_(double Tk){

  return 0.1070003e-2 - 0.249936e-7*Tk + 0.371611e-9*Tk*Tk;

}

/*! Volume molar do gelo saturado, 173.15 < T < 273.15
\param T Temperatura em K
\return Volume molar em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_s_(double T){
  return v_s_(T) * Mv;
}

/*! Densidade do gelo saturado, 173.15 < Tk < 273.15
\param Tk Temperatura em K
\return Densidade em \f$kg/m^3\f$
*/
double GasPerfeito::r_s_(double Tk){
  return 1/v_s_(Tk);
}


/*! Volume espec�fico da fase n�o gasosa saturada
\param Tk Temperatura em K
\return Volume espec�fico em \f$m^3/kg\f$
*/
double GasPerfeito::v_f_(double Tk){
  if (Tk < 273.15)
    return v_s_(Tk);
  else
    return v_l_(Tk);
}


/*! Volume molar da fase n�o gasosa saturada
\param Tk Temperatura em K
\return Volume molar em \f$m^3/kmol\f$
*/
double GasPerfeito::vM_f_(double T){
  return v_f_(T) * Mv;
}

/*! Densidade da fase n�o gasosa saturada
\param Tk Temperatura em K
\return Densidade em \f$kg/m^3\f$
*/
double GasPerfeito::r_f_(double Tk){
  return 1/v_f_(Tk);
}


/*! Defini��o do ar �mido. Este fun��o especifica o ar �mido. Novas fun��es podem ser criadas para fazerem as tarefas desta fun��o. Atualmente, esta fun��o tem quatro argumentos e no final calcula o teor de umidade (kg_vapor / kg_arseco) e a fra��o molar de vapor. Observe que com estes par�metros e as fun��es definidas acima � poss�vel calcular qualquer outro par�metro de interesse, ou seja, o estado do ar est� especificado.

\param T Temperatura do ar em K, temperatura de bulbo seco (TBS)
\param ch Character que determina como a umidade ser� especificada. No momento pode ser 'R' para umidade relativa, 'W' para o teor de umidade, 'D' para a temperatura de ponto de orvalho, 'B' para a temperatura de bulbo �mido e 'X' para a fra��o molar de vapor. Outros par�metros, no futuro, podem ser inclu�dos.
\param umidade A umidade do ar �mido. Vai depender do que foi especificado em ch.
\param P Press�o do ar �mido em Pa
*/
void GasPerfeito::set(double T, char ch, double umidade, double P){
  // 
  double B, Rel, D;

  // Verificar faixa de temperatura, caso d� pau, usar 25oC
  if (!FaixaT(T)){
    errorcode = 10;
  }
  if (!FaixaP(P)){
    errorcode = 11;
  }

  
  double XSV;
  switch(ch){
  case 'X':			// Fra��o molar de vapor
    XV = umidade;
    // Verificar a faixa de fra��o molar
    XSV = eFactor(T, P) * Pws(T) / P;
    if (XV < 0.0 || XV > XSV) {
      errorcode = 16;
    }
    W = Mv/Ma * XV/(1.0 - XV);
    break;
  case 'W':			// Teor de umidade
    W = umidade;
    XV = W / (Mv/Ma + W);
    XSV = eFactor(T, P) * Pws(T) / P;
    if (XV < 0.0 || XV > XSV) {
      errorcode = 15;
    }
    
    break;
  case 'R':			// UMidade relativa
    Rel = umidade;
    if (Rel < 0.0){
      errorcode = 12; Rel = 0.0;
    }
    XV = Rel * Pws(T) / P;
    W = Mv/Ma * XV/(1.0 - XV);
    break;
    
  case 'B':			// Temp. de bulbo �mido
    // A aproxima��o linear facilita mesmo estes c�lculos...
    B = umidade;
    double psat, w2, hs, hw;
    if (B > T){
      errorcode = 14; B = T;
    }
    psat = Pws(B);
    w2 = Mv/Ma * psat / (P - psat);
    hs = h_a_(B) + w2 * h_v_(B);
    hw = h_f_(B);
    W = (hs - h_a_(T) - w2 * hw) / (h_v_(T) - hw);
    XV = W / (Mv/Ma + W);
    
    break;
  case 'D':			// Ponto de orvalho
    D = umidade;
    if (D > T){
      errorcode = 13; D = T;
    }
    XV = Pws(D)/P;
    W = Mv/Ma * XV/(1.0 - XV);
    break;

  };

  M = XV * Mv + (1.0 - XV) * Ma;


}




/*! Volume espec�fico do ar �mido por kg de ar seco. Calculado a partir da densidade da mistura: \f$ v = \frac{1 + \omega}{\rho(T,P)} \f$. � interessante notar que usando a fun��o set, pode-se calcular o volume para diferentes temperaturas e press�es, mas mesma composi��o do ar �mido.
\param T Temperatura em K
\param P Press�o em Pa
\return Volume especifico em \f$m^3/kg\f$ de ar seco.
*/
double GasPerfeito::VOLUME(double T, double P){
  if (!FaixaT(T)) {errorcode=10; T = 293.15;}
  if (!FaixaT(P)) {errorcode=11; P = 101325.0;}
  
  return (1.0+W) / DENSITY(T,P);
}


/*! Densidade (ou massa espec�fica) do ar �mido. Ap�s especificar uma mistura ar-vapor, pode-se calcular para qualquer temperatura ou press�o na faixa de aplica��o do modelo.

\f$rho = P\cdot M / (R\cdot T) \f$


\param T Temperatura em K
\param P Press�o em Pa
\return Densidade em \f$kg/m^3\f$
 */
double GasPerfeito::DENSITY(double T, double P){
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  // Calcula a massa espec�fica do ar �mido
  return P * M / (R*T);
}
    
/*! Calcula o teor de umidade.
\return Teor de umidade kg de vapor / kg de ar seco
*/
double GasPerfeito::HUMRAT(){
  return W;
}

/*!
  Calcula a fra��o molar de vapor 
\return Fra��o molar de vapor
*/
double GasPerfeito::MOLFRAC(){
  return XV;
}


/*! Calcula a temperatura de ponto de orvalho para uma dada mistura ar-vapor (especificada com a fun��o set) para diferentes temperaturas e press�es.

\param T Temperatura em K
\param P Press�o em Pa
\return Temperatura de ponto de orvalho em K
*/
double GasPerfeito::DEWPOINT(double T, double P){
  // Ponto de orvalho
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return Tws(XV * P);
}

/*! Calcula a entalpia de uma mistura ar-vapor para diferentes press�es e temperaturas
\param T Temperatura K
\param P Press�o Pa
\return Entalpia em J/kg de ar seco
*/
double GasPerfeito::ENTHALPY(double T, double P){
  // Ponto de orvalho
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return h_(T, XV)*(1.0 + W);
}

/*! Calcula a entropia de uma mistura ar-vapor para diferentes press�es e temperaturas
\param T Temperatura K
\param P Press�o Pa
\return Entropia em J/kgK de ar seco
*/
double GasPerfeito::ENTROPY(double T, double P){
  // Ponto de orvalho
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return 0;
}

/*! Calcula a umidade relativa de uma mistura ar-vapor para diferentes press�es e temperaturas
\param T Temperatura K
\param P Press�o Pa
\return Umidade relativa
*/
double GasPerfeito::RELHUM(double T, double P){
  // Umidade relativa
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return XV*P/Pws(T);
}


/*! Fun��o auxiliar para a determina��o da temperatura de bulbo �mido. A temperatura de bulbo �mido n�o � calculada diretamente e portanto � necess�rio iterar para calcular este valor. Esta � uma fun��o auxiliar para calular o TBU. Esta fun��o, para uma dada temperatura de bulbo �mido, faz o balan�o de energia dada pela seguinte equa��o:

\f[  (1 + \omega)h(T,P,\omega) + (\omega' - \omega)h_f(B) - (1 + \omega')h(B,P,\omega') = 0 \f]


\param b Estimativa da temperatura de bulbo �mido em K
\param P Press�o em Pa
\param T Temperatura em K
\return O quanto n�o h� balan�o de energia no saturador adiab�tico para a estimativ b da temperatura de bulbo �mido
*/
double GasPerfeito::BcalcW(double b, double P, double T){
  // Calcular w2
  double w2 = Mv / Ma * Pws(b) / (P - Pws(b));

  return -W*(h_v_(T) - h_f_(b)) + h_a_(b) - h_a_(T) + w2*(h_v_(b) - h_f_(b));
}


    
  
/*! Fun��o para c�lculo da temperatura de bulbo �mido de uma mistura ar-vapor com composi��o conhecida a diferentes press�es e temperaturas. Esta fun��o � iterativa, utilizando o m�todo de Newton-Raphson para calcular a temperatura de bulbo �mido. A temperatura de bulbo �mido � calculada a partir do balan�o de energia de um saturador adiab�tico implementada na equa��o BcalcW.
\param T Temperatura em K
\param P Press�o em Pa
\return Temperatura de bulbo �mido em K
*/
double GasPerfeito::WETBULB(double T, double P){
  // Temperatura de bulbo �mido
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}

  // Chute inicial
  double b = T - 1.0, db;
  double f, df;
  const double EPS=1e-7;
  const int NMAX = 100;
  for (int iter = 0; iter < NMAX; ++iter){
    f = BcalcW(b, P, T);
    df = (BcalcW(b+0.0001,P, T)-f) / 0.0001;
    db = - f / df;
    b = b + db;
    if (fabs(db) < EPS) return b;
  }

  errorcode = 100;		// N�o convergiu no n�mero de etapas certas, erro
  return(b);
}
      
    
  
int GasPerfeito::ERROR(){
  return errorcode;
}
