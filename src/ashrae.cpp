#include <cmath>
#include <iostream>

#include <psychro/psychro.h>



using namespace std;

/*! A equação de estado proposta pela ASHRAE é válida para pressões inferiores a 5MPa e temperaturas entre -100oC e 200oC
 */
Ashrae::Ashrae(){
  // Esta função estabelece os limites de aplicação do método
  Tmin = 173.15;
  Tmax = 473.15;
  Pmin = 0.0;
  Pmax = 5e6;
}

  
/*! Segundo coeficiente virial do ar puro [2]

\param Tk Temperatura em k
\return Coeficiente virial Baa em \f$m^3/kmol\f$
*/
double Ashrae::Baa(double Tk){
  double B = 0.349568e2 - 0.668772e4/Tk - 0.210141e7/(Tk*Tk) + 0.924746e8/(Tk*Tk*Tk);

  return(B/1e3); //# m3/kmol

}


/*! Segundo coeficiente virial da água pura \f$B'\f$ [3]

\param Tk Temperatura em k
\return Coeficiente virial \f$B'\f$ em 1/Pa
*/
double Ashrae::Blinha(double Tk){
  double B = 0.70e-8 - 0.147184e-8 * exp(1734.29/Tk);// # Pa^(-1)
  return(B);
}

/*! Terceiro coeficiente virial da água pura [3]

\param Tk Temperatura em k
\return Terceiro coeficiente virial \f$C'\f$ em \f$1/Pa^2\f$
*/
double Ashrae::Clinha(double Tk){
  double C = 0.104e-14 - 0.335297e-17*exp(3645.09/Tk);// # Pa^(-2)
  return(C);

}
  
/*! Derivada do segundo coeficiente virial da água pura \f$dB'/dT\f$

\param Tk Temperatura em k
\return derivada do coeficiente virial \f$dB'/dT\f$ em 1/(Pa.K)
*/
double Ashrae::dBlinha(double Tk){
  double dB = 0.255260e-5/(Tk*Tk) * exp(1734.29/Tk);
  return(dB);

}


/*! Derivada do terceiro coeficiente virial da água pura 

\param Tk Temperatura em k
\return Derivada doerceiro coeficiente virial \f$dC'dT\f$ em \f$1/(Pa^2K)\f$
*/
double Ashrae::dClinha(double Tk){
  double dC = 0.122219e-13/(Tk*Tk) * exp(3645.09/Tk);
  return(dC);

}


/*! Segundo coeficiente virial da água pura \f$B_{ww}\f$ [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$B_{ww}\f$ em \f$m^3/kmol\f$
*/
double Ashrae::Bww(double Tk){
  double B = R * Tk * Blinha(Tk);
  return(B);

}


/*! Segundo coeficiente cruzado virial de ar-água \f$B_{aw}\f$ [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$B_{aw}\f$ em \f$m^3/kmol\f$
*/
double Ashrae::Baw(double Tk){
  double B = 0.32366097e2 - 0.141138e5/Tk - 0.1244535e7/(Tk*Tk) - 0.2348789e10/(Tk*Tk*Tk*Tk);

  return(B/1e3);

}

/*! Derivada do segundo coeficiente virial do ar puro [2]

\param Tk Temperatura em k
\return Derivada do coeficiente virial \f$dB_{aa}/dT\f$ em \f$m^3/(kmol\cdot K)\f$
*/
double Ashrae::dBaa(double Tk){
  double dB =  0.668772e4/(Tk*Tk) + 0.420282e7/(Tk*Tk*Tk) - 0.277424e9/(Tk*Tk*Tk*Tk);

  return(dB/1e3);// #m3/kmol.K

}


/*! Derivada do segundo coeficiente virial da água pura \f$dB_{ww}/dT\f$ [2]

\param Tk Temperatura em k
\return Derivada do coeficiente virial \f$dB_{ww}/dT\f$ em \f$m^3/(kmol\cdot K)\f$
*/
double Ashrae::dBww(double Tk){
  double dB = R * (Tk * dBlinha(Tk) + Blinha(Tk));
  return(dB);

}


/*! Derivada do segundo coeficiente cruzado virial de ar-água \f$dB_{aw}/dT\f$ [2]

\param Tk Temperatura em k
\return Derivada do coeficiente virial \f$dB_{aw}/dT\f$ em \f$m^3/(kmol\cdot K)\f$
*/
double Ashrae::dBaw(double Tk){
  double dB = 0.141138e5/(Tk*Tk) + 0.248907e7/(Tk*Tk*Tk) + 0.93951568e10/pow(Tk, 5);
  return(dB / 1e3);

}



/*! Terceiro coeficiente virial do ar puro [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$Caaa\f$ em \f$m^6/kmol^2\f$
*/
double Ashrae::Caaa(double Tk){
  double C = 0.125975e4 - 0.190905e6/Tk + 0.632467e8/(Tk*Tk);
  return(C/1e6);//  #m6/kmol2

}



/*! Terceiro coeficiente virial da água [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$Cwww\f$ em \f$m^6/kmol^2\f$
*/
double Ashrae::Cwww(double Tk){
  double C = R*Tk*R*Tk * (Clinha(Tk) + pow(Blinha(Tk), 2));
  return(C);

}

/*! Terceiro coeficiente virial cruzado de ar-água [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$Caaw\f$ em \f$m^6/kmol^2\f$
*/
double Ashrae::Caaw(double Tk){
  double C = 0.482737e3 + 0.105678e6/Tk - 0.656394e8/(Tk*Tk) + 0.294442e11/(Tk*Tk*Tk)
    - 0.319317e13/(Tk*Tk*Tk*Tk);
  return(C/1e6);

}

/*! Terceiro coeficiente virial cruzado de ar-água [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$Caww\f$ em \f$m^6/kmol^2\f$
*/
double Ashrae::Caww(double Tk){
  double C =  -1e6* exp( -0.10728876e2 + 0.347802e4/Tk - 0.383383e6/(Tk*Tk)
			 + 0.33406e8/(Tk*Tk*Tk));
  return(C/1e6);

}



/*! Derivada do terceiro coeficiente virial do ar puro [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$dC_{aaa}/dT\f$ em \f$m^6/(kmol^2\cdot K)\f$
*/
double Ashrae::dCaaa(double Tk){
  double dC = 0.190905e6/(Tk*Tk) - 0.126493e9/(Tk*Tk*Tk);
  return(dC/1e6);//#m6/kmol2.K

}



/*! Derivada do terceiro coeficiente virial da agua [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$dC_{www}/dT\f$ em \f$m^6/(kmol^2\cdot K)\f$
*/
double Ashrae::dCwww(double Tk){
  double dC = R*Tk*R*Tk * (dClinha(Tk) + 2*Blinha(Tk) * dBlinha(Tk)) +
    (2*R*R*Tk) * (Clinha(Tk) + pow(Blinha(Tk),2));
  return(dC);

}

/*! Derivada do terceiro coeficiente virial cruzado de ar-água [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$dC_{aaw}/dT\f$ em \f$m^6/(kmol^2\cdot K)\f$
*/
double Ashrae::dCaaw(double Tk){
  double dC = -0.105678e6/(Tk*Tk) + 1.312788e8/(Tk*Tk*Tk) - 8.83326e10/pow(Tk,4)
    + 1.277268e13/pow(Tk,5);
  return(dC/1e6);

}

/*! Derivada do terceiro coeficiente virial cruzado de ar-água [2]

\param Tk Temperatura em k
\return Coeficiente virial \f$dC_{aww}/dT\f$ em \f$m^6/(kmol^2\cdot K)\f$
*/
double Ashrae::dCaww(double Tk){
  double dC = -0.347802e4/(Tk*Tk) + 2*0.383383e6/(Tk*Tk*Tk) - 3*0.33406e8/pow(Tk,4);

  return(dC * Caww(Tk));

}


/*! Segundo coeficiente virial da mistura ar-água [2], 
\f[ B_m = x_a^2  B_{aa} + 2x_a x_v B_{aw} + x_v^2 B_{ww} \f]
\param Tk Temperatura em K
\param xv Fração molar de vapor da mistura
\return \f$B_m\f$ em \f$m^3/kmol\f$
*/
double Ashrae::Bm(double Tk, double xv){
  double xa = 1.0-xv;

  return(xa*xa*Baa(Tk) + 2*xa*xv*Baw(Tk) + xv*xv*Bww(Tk));

}


/*! Terceiro coeficiente virial da mistura ar-água [2], 
\f[ C_m = x_a^3  C_{aaa} + 3x_a^2x_v C_{aaw} + 3x_a x_v^2 C_{aww} + x_v^3 C_{www} \f]
\param Tk Temperatura em K
\param xv Fração molar de vapor da mistura
\return \f$C_m\f$ em \f$m^6/kmol^2\f$
*/
double Ashrae::Cm(double Tk, double xv){
  double xa = 1.0-xv;
  return(xa*xa*xa*Caaa(Tk) + 3*xa*xa*xv*Caaw(Tk) +
         3*xa*xv*xv*Caww(Tk) + xv*xv*xv*Cwww(Tk));
         

}




/*! Pressão do vapor saturado em equilíbrio com a água líquida. A equação é válida para 273.15 < T < 473.15. Equação retirada de [3]
\param Tk Temperatura em K, deve ser superior a 273.15
\return Pressão de vapor em Pa
*/
double Ashrae::Pws_l(double Tk){
  // Esta função calcula a pressão de saturação do vapor sobre água:

  double g[] = {-0.58002206e4,
          0.13914993e1,
         -0.48640239e-1,
          0.41764768e-4,
         -0.14452093e-7,
		0.65459673e1};
  

  double lnP = g[0]/Tk + g[1] + g[2]*Tk + g[3]*Tk*Tk + g[4]*Tk*Tk*Tk + g[5]* log(Tk);

  return(exp(lnP));

}

/*! Pressão do vapor saturado em equilíbrio com o gelo. A equação é válida para 173.15 < T < 273.15. Equação retirada de [3]
\param Tk Temperatura em K, deve ser inferior a 273.15
\return Pressão de vapor em Pa
*/
double Ashrae::Pws_s(double Tk){
  // Esta função calcula a pressão de saturação do vapor sobre gelo:
  double m[] = {-0.56745359e4,
          0.63925247e1,
         -0.96778430e-2,
          0.62215701e-6,
          0.20747825e-8,
         -0.94840240e-12,
		0.41635019e1};
  
  
  double lnP = m[0]/Tk + m[1] + m[2]*Tk + m[3]*Tk*Tk + m[4]*Tk*Tk*Tk +
    m[5]*Tk*Tk*Tk*Tk + m[6]* log(Tk);
  return(exp(lnP));

}

/*! Pressão de vapor saturado. Para temperaturas inferiores a 273.15, supõe um equilíbrio com o gelo. Para temperaturas superiores supõe o equilíbrio com a água
\param Tk Temperatura em K
\return Pressão de vapor em Pa
*/
double Ashrae::Pws(double Tk){
  // Esta função calcula a pressão de saturação da água:

  if (Tk < 273.15) return Pws_s(Tk);

  return Pws_l(Tk);



}

/*! Derivada de Pws_s
/param Tk Temperatura K
/return dP/dT Pa/K
*/
double Ashrae::dPws_s(double Tk){
  double termo1 = Pws_s(Tk);
  double termo2 = 0.56745359e4/(Tk*Tk) + 0.41635019e1/Tk - 0.96778430e-2 +
    0.12443140e-5*Tk + 0.62243475e-8 * Tk*Tk - 0.37936096e-11*Tk*Tk*Tk;

  return(termo1 * termo2);

}


/*! Derivada de Pws_l
/param Tk Temperatura K
/return dP/dT Pa/K
*/
double Ashrae::dPws_l(double Tk){
  double termo1 = Pws_l(Tk);
  double termo2 = 0.58002206e4/(Tk*Tk) + 0.65459673e1/Tk - 0.48640239e-1 +
    0.83529536e-4*Tk -0.43356279e-7 * Tk*Tk;

  return(termo1 * termo2);

}


/*! Derivada de Pws
/param Tk Temperatura K
/return dP/dT Pa/K
*/
double Ashrae::dPws(double Tk){
  // Esta função calcula a pressão de saturação da água:

  if (Tk < 273.15) return dPws_s(Tk);

  return dPws_l(Tk);

}





/*! Esta função é a inversa de Pws. Ela é calculada utilizando o método de Newton-Raphson. Para garantir uma boa convergência, um valor inicial bom é adotado: Foi desenvolvida por Paulo José Saiz Jabardo uma correlação da forma:
\f[ T = g_0 + g_1 \ln P + g_2 (\ln P)^2 + g_3 (\ln P)^3 + g_4 (\ln P)^4 + g_5 P \f]
Esta correlação possui erros inferiores a 0,6K. Com este valor, em poucas iterações o método de Newton-Raphsons converge, mesmo para valores próximos a 273.15, onde há uma certa descontinuidade das curvas de pressão de vapor.
\param PP Pressão em Pa
\return Temperatura de saturação do vapor em K
*/
double Ashrae::Tws(double PP){
  // Esta função retorna a pressão de saturação do vapor. Inicialmente, será utilizada uma
  // aproximação construída a partir de um ajuste de curva dos dados obtidos de Pws. Este
  // valor será utilizado como chute inicial (muito próximo para uma iteração de Newton-Raphson

  double g[]={2.127925e2,
	      7.305398e0,
	      1.969953e-1,
	      1.103701e-2,
	      1.849307e-3,
	      5.145087e-6};
  double lnP = log(PP);

  double T = g[0] + g[1]*lnP + g[2]*lnP*lnP + g[3]*lnP*lnP*lnP +
    g[4]*lnP*lnP*lnP*lnP + g[5] * PP;

  const double NMAX=100;
  const double EPS=1e-8;

  double f, df, dT;
  double Tnovo;
  
  for(int iter=0; iter < NMAX; ++iter){
    f = PP-Pws(T);
    df = - dPws(T);
    dT = - f/df;

    T += dT;

    if (fabs(dT) < EPS) return T;
    
  }
  errorcode = 106;
  
  return T;
}




/*! Volume molar da mistura ar-vapor. Calculado a partir do coeficiente de compressibilidade.
\param Tk Temperatura em K
\param P Pressão em Pa
\param xv Fração molar de vapor
\return Volume molar da mistura ar-vapor em \f$m^3/kmol\f$
*/
double Ashrae::vM_(double Tk, double P, double xv){

  return Z(Tk, P, xv) * R*Tk/P;
  
}


/*! Volume específico do vapor saturado.
\param Tk Temperatura em K
\return v em \f$m^3/kg\f$
*/
double Ashrae::v_v_(double Tk){
  return(vM_v_(Tk)/Mv);
  
}

/*! Densidade do vapor saturado.
\param Tk Temperatura em K
\return \f$\rho\f$ em \f$kg/m^3\f$
*/
double Ashrae::r_v_(double T){
  return 1.0/v_v_(T);
}


/*! Fator de compressibilidade do ar úmido. Calculado a partir dos coeficientes viriais. Esta é uma equação implícita que deve ser iterada a partir de chute inicial que neste caso vale 1 (gás perfeito). Z é a relação entre o volume do gás e o volume do gás se fosse perfeito:
\f[ Z = \frac{v_m}{v_{mi}} \f]

A equação virial de [2] tem a seguinte forma:
\f[ \frac{P v_m}{RT} = 1 + \frac{B_m}{v_m} + \frac{C_m}{v_m^2} \f]
Nesta equação, os coeficientes Bm e Cm são funções da temperatura e podem ser calculadas com as funções implementadas neste arquivo. Após calcular o volume molar, dividi-se este valor pelo volume do gás perfeito e assim calcula-se a compressibilidade Z do gás.

\param Tk Temperatura em K
\param P Pressão em Pa
\param xv Fração molar de vapor
\return Z
*/
double Ashrae::Z(double Tk, double P, double xv){
  double xa = 1.0-xv;

  double vmi =  R*Tk/P;
  double vm  = vmi;
  double vmn;
  double b = Bm(Tk, xv);
  double c = Cm(Tk, xv);
  const double NMAX = 100;
  const double EPS=1e-8;
  double erro;
  for (int iter = 0; iter < NMAX; ++iter){
    vmn = R*Tk/P * (1 + b/vm + c/(vm*vm));
    erro = fabs(vmn - vm);
    vm = vmn;

    if (erro < EPS) return vm/vmi;
  }
  errorcode = 107;
  return(vm/vmi);


}


/*! Esta função calcula o enhacement factor f. O fator f é utilizado para determinar a fração molar de saturação de uma mistura ar-vapor saturada. Caso o gás fosse perfeito, a fração molar de saturação valeria
\f[x_{sv} = \frac{P_{ws}}{P} \f]. No caso de gases perfeitos, a compressibilidade da fase não gasosa (líquida ou sólida) e a solubilidade desta mesma fase, além de outros efeitos, fazem com que a relação anterior não seja válida. Um fator de correção conhecido como enhancement factor corrige esta diferença. Desta maneira, 

\f[ x_{sv} = f(T,P) \frac{P_{ws}(T)}{P} \f]
Este fator é uma expressão grande está apresentada em [2]. Cuidado com a referência [1] pois há um pequeno erro na expressão apresentada. Outro ponto é que a expressão para f(T,P) não é explícita e portanto é necessário iterar. Nesta implementação, a iteração utiliza a função auxiliar lnf. É interessante notar que em alguns casos o problema não converge ou converge para um valor estranho. Nestes casos, adotou-se o critério f=1 (quando estes problemas ocorrem, isto é bem próximo da realidade)

\param Tk Temperatura em K
\param P Pressão em Pa
\return Enhancement Factor
*/
double Ashrae::eFactor(double Tk, double P){
  // Chute inicial para f: 1
  double f = 1.0;
  const double EPS = 1e-7;
  const int NMAX = 50;
  double xas;
  double fnovo, m1;

  for(int iter=0; iter < NMAX; ++iter){
    
    xas = (P-f*Pws(Tk))/P;
    fnovo = exp(lnf(Tk, P, xas));

    if (fabs(fnovo - f) < EPS) {
      if (fnovo < 1.0) fnovo = 1.0;
    
      return(fnovo);
    }
    

    f = fnovo;
  }

  if (fnovo < 1.0) fnovo = 1.0;
  return fnovo;

}


/*! Cálculo da entalpia do ar úmido. Como o gás é real, o problema não é tão simples quanto o caso para gás perfeito. Não basta somar as contribuições do ar e do vapor. A referência [3] possui uma expressão, que utiliza os coeficientes viriais, para o cálculo da entalpia.
\param Tk Temperatura em K
\param P Pressão em Pa
\xv Fração molar
\return Entalpia em J/kg
*/
double Ashrae::h_(double Tk, double P, double xv){

  double  xa = 1.0 - xv;

  double a[] = {0.63290874e1,
         0.28709015e2,
         0.26431805e-2,
         -0.10405863e-4,
         0.18660410e-7,
		-0.9784331e-11};
  double d[] = {-0.5008e-2,
         0.32491829e2,
         0.65576345e-2,
         -0.26442147e-4,
         0.51751789e-7,
		-0.31541624e-10};

  // Cálculo dos coeficientes
  double B = xa*xa * Baa(Tk) + 2*xa*xv*Baw(Tk) + xv*xv * Bww(Tk);
  double C = xa*xa*xa*Caaa(Tk) + 3*xa*xa*xv*Caaw(Tk) + 3*xa*xv*xv*Caww(Tk) + xv*xv*xv*Cwww(Tk);

  double dB = xa*xa * dBaa(Tk) + 2*xa*xv*dBaw(Tk) + xv*xv * dBww(Tk);
  double dC = xa*xa*xa*dCaaa(Tk) + 3*xa*xa*xv*dCaaw(Tk) + 3*xa*xv*xv*dCaww(Tk) +
    xv*xv*xv*dCwww(Tk);


  double ha = -7914.1982;
  double hv = 35994.17;

  
  double termo1 = a[0] + a[1]*Tk + a[2]*Tk*Tk + a[3]*Tk*Tk*Tk +
    a[4]*Tk*Tk*Tk*Tk + a[5]*pow(Tk, 5) + ha;

  

  double termo2 = d[0] + d[1]*Tk + d[2]*Tk*Tk + d[3]*Tk*Tk*Tk +
    d[4]*pow(Tk,4) + d[5]*pow(Tk,5) + hv;

  //# Cálculo do volume molar
  double Vm = vM_(Tk, P, xv);

  
  double termo3 = (B - Tk*dB)/Vm + (C - 0.5*Tk*dC)/(Vm*Vm);

  double hm = xa * termo1 * 1000.0 + xv * termo2 * 1000.0 + R*Tk*termo3;
  
  return hm/(xa * Ma + xv*Mv);

}


/*! Função auxiliar para cálculo do enhancement factor. Esta expressão está errada na referência [1]. 
\param Tk Temp. K
\param P Pressão Pa
\param xas Estimativa da fração molar de saturação do ar
\result Uma estimativa melhor de ln(f)
*/
double Ashrae::lnf(double Tk, double P, double xas){
  double vc = v_f_(Tk) * Mv;
  double kk = kappa_f(Tk);
  double k;
  if (Tk < 273.15)
    k = 0.0;
  else
    k = henryk(Tk);
  
  double RT = R*Tk;
  double p = Pws(Tk);

  double t1 = vc/RT * ( (1 + kk*p)*(P-p) - .5 * kk * (P*P - p*p) );
  
  double t2 = log(1.0 - k*xas*P) + (xas*xas*P/RT)*Baa(Tk) - (2*xas*xas*P/RT)*Baw(Tk);
  
  double t3 = -(P-p-xas*xas*P)/RT*Bww(Tk) + xas*xas*xas*P*P/(RT*RT) * Caaa(Tk);
  
  double t4 = 3*xas*xas*(1.0-2.0*xas)*P*P/(2*RT*RT) * Caaw(Tk) -
    (3*xas*xas*(1-xas)*P*P)/(RT*RT)*Caww(Tk);
  
  double t5 = - ( (1.0+2.0*xas)*pow(1.0-xas, 2) * P*P - p*p)/(2.0*RT*RT) * Cwww(Tk);

  double t6 = -xas*xas*(1.0-3.0*xas)*(1.0-xas)*P*P/(RT*RT) * Baa(Tk) * Bww(Tk) -
    2.0*xas*xas*xas*(2.0-3.0*xas)*P*P/(RT*RT) * Baa(Tk) * Baw(Tk);
  
  double t7 = 6.0*xas*xas*pow(1.0-xas,2)*P*P/(RT*RT)*Bww(Tk)*Baw(Tk) -
    3.0*pow(xas,4)*P*P/(2.0*RT*RT)*pow(Baa(Tk),2);
  
  double  t8 = -2.0*xas*xas*(1.0-xas)*(1.0-3.0*xas)*P*P/(RT*RT) * pow(Baw(Tk),2) -
    ( p*p - (1.0+3.0*xas)*pow(1.0-xas,3)*P*P) / (2*RT*RT) * pow(Bww(Tk),2);
  

  return t1+t2+t3+t4+t5+t6+t7+t8;
}


/*! Calcula o coeficiente de Henry do oxigênio [5]
\param Tk Temp. K
\return k (1/Pa)
*/
double Ashrae::henryk_O2(double Tk){

  double tau = 1000/Tk;
  double alfa = -0.0005943;
  double beta = -0.1470;
  double gama = -0.05120;
  double delta = -0.1076;
  double eps = 0.8447;
    
  double a2 = alfa;
  double a1 = gama*tau + delta;
  double a0 = beta*tau*tau + eps*tau - 1.0;
    

  // Resolver o sistema ax^2+bx+c=0 onde x=log10(k)

  double raizes = (-a1 - sqrt(a1*a1 - 4.0*a2*a0)) / (2.0*a2);
  return pow(10,raizes);
  
}


/*! Calcula o coeficiente de Henry do nitrogênio [5]
\param Tk Temp. K
\return k (1/Pa)
*/
double Ashrae::henryk_N2(double Tk){

  double  tau = 1000/Tk;
  double  alfa = -0.1021;
  double  beta = -0.1482;
  double  gama = -0.019;
  double  delta = -0.03741;
  double eps = 0.851;

  double a2 = alfa;
  double a1 = gama*tau + delta;
  double a0 = beta*tau*tau + eps*tau - 1.0;
    

  // Resolver o sistema ax^2+bx+c=0 onde x=log10(k)

  double raizes = (-a1 - sqrt(a1*a1 - 4.0*a2*a0)) / (2.0*a2);
  return pow(10,raizes);

}

/*! Calcula o coeficiente de Henry do ar [5]:
\f[ \frac{1}{k} = \frac{1}{k_{N_2}} + \frac{1}{k_{O_2}} \f]

\param Tk Temp. K
\return k (1/Pa)
*/
double Ashrae::henryk(double Tk){
  double kO2 = henryk_O2(Tk);
  double kN2 = henryk_N2(Tk);
  double xO2 = 0.22;
  double xN2 = 0.78;
  
  double k = 1.0 / (xO2/kO2 + xN2/kN2);
  k = 1e-4/k * 1.0/101325.0;
  
  return k;

}



/*! Compressibilidade isotérmica da água na pressão atmosférica, retirado de [6]. Válido para 273.15 < T < 473.15.
\param Tk Temp. K
\return \f$\kappa\f$ (1/Pa)
*/
double Ashrae::kappa_l(double Tk){
  
  double Tc = Tk - 273.15;
  
  double k;

  if (Tc < 100.0)
    k = (50.88496 + 0.6163813*Tc + 1.459187e-3*Tc*Tc + 20.08438e-6*Tc*Tc*Tc -
	 58.47727e-9*pow(Tc,4) + 410.4110e-12 * pow(Tc,5)) / (1.0 + 19.67348e-3*Tc);
  else 
    k =  (50.884917 + 0.62590623*Tc + 1.3848668e-3*Tc*Tc + 21.603427e-6*Tc*Tc*Tc -
	  72.087667e-9*pow(Tc,4) + 465.45054e-12 * pow(Tc,5)) / (1 + 19.859983e-3*Tc);

  return(k * 1e-11);  // 1/Pa

}

/*! Compressibilidade isotérmica do gelo na pressão atmosférica, retirado de [2]. Válido para 173.15 < T < 273.15.
\param Tk Temp. K
\return \f$\kappa\f$ (1/Pa)
*/
double Ashrae::kappa_s(double Tk){
  return (8.875 + 0.0165 * Tk) * 1e-11;

}

/*! Compressibilidade isotérmica da fase não gasosa: T<273.15 - kappa_s, T>273.15 kappa_l
\param Tk Temp. K
\return \f$\kappa\f$
*/
double Ashrae::kappa_f(double Tk){
  if (Tk < 273.15)
    return kappa_s(Tk);
  else
    return kappa_l(Tk);
}





void Ashrae::set(double T, char ch, double umidade, double P){
  double B, Rel, D, XSV;
  // Verificar faixa de temperatura, caso dê pau, usar 25oC
  if (!FaixaT(T)){
    errorcode = 10;
  }
  if (!FaixaP(P)){
    errorcode = 11;
  }

  switch(ch){
  case 'X':			// Fração molar de vapor
    XV = umidade;
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
    XV = Rel * eFactor(T, P) * Pws(T) / P;
    W = Mv/Ma * XV/(1.0 - XV);
    break;
    
  case 'B':			// Temp. de bulbo úmido
    // A aproximação linear facilita mesmo estes cálculos...
    
    B = umidade;
    if (B > T){
      errorcode = 14; B = T;
    }
    W = CalcWfromB(T,B,P);	
    XV = W / (Mv/Ma + W);
    break;
  case 'D':			// Ponto de orvalho
    D = umidade;
    if (D > T){
      errorcode = 13; D = T;
    }
    XV = eFactor(D,P) * Pws(D)/P;
    W = Mv/Ma * XV/(1.0 - XV);
    break;

  };

  M = XV * Mv + (1.0 - XV) * Ma;


}

/*! Volume molar do ar seco. Utilizando os coeficientes viriais implementados neste trabalho.
\param Tk Temp. K
\param P Pressão Pa
\return Volume molar \f$m^3/kmol\f$
*/
double Ashrae::vM_a_(double Tk, double P){
  double xa = 1.0;

  double vmi =  R*Tk/P;
  double vm  = vmi;
  double vmn;
  double b = Baa(Tk);
  double c = Caaa(Tk);
  const double NMAX = 100;
  const double EPS=1e-8;
  double erro;
  for (int iter = 0; iter < NMAX; ++iter){
    vmn = R*Tk/P * (1 + b/vm + c/(vm*vm));
    erro = fabs(vmn - vm);
    vm = vmn;

    if (erro < EPS) return vm;
  }
  errorcode = 102;
  return(vm);
  
}



/*! Volume específico do ar seco. 
\param Tk Temp. K
\param P Pressão Pa
\return Volume molar \f$m^3/kg\f$
*/
double Ashrae::v_a_(double T, double P){
  return vM_a_(T, P) / Ma;
}

double Ashrae::r_a_(double T, double P){
  return 1/v_a_(T,P);
}



// Implementação das entalpias
/*! Entalpia do ar seco, [2]
\param Tk Temp. K
\param P Pressão Pa
\return Entalpia, J/kg
*/
double Ashrae::h_a_(double Tk, double P){
  double b[] = {-0.79078691e4,
         0.28709015e2,
         0.26431805e-2,
         -0.10405863e-4,
         0.18660410e-7,
		-0.97843331e-11};

  double B = Baa(Tk);
  double C = Caaa(Tk);
  double dB = dBaa(Tk);
  double dC = dCaaa(Tk);
  
  double Vm = vM_a_(Tk, P);

  double ha = 1000*(b[0] + b[1]*Tk + b[2]*Tk*Tk + b[3]*Tk*Tk*Tk +
		    b[4]*pow(Tk,4) + b[5]*pow(Tk,5));
  
  ha = ha + R*Tk * ( (B - Tk*dB)/Vm + (C - 0.5*Tk*dC)/(Vm*Vm)  );
  return ha/Ma;

}  



/*! Volume molar do vapor [3]
\param Tk Temp. K
\return Volume molar \f$m^3/kmol\f$
*/
double Ashrae::vM_v_(double Tk){
  double P = Pws(Tk);
  double vmi =  R*Tk/P;
  double vm  = vmi;
  double vmn;
  double b = Bww(Tk);
  double c = Cwww(Tk);
  const double NMAX = 200;
  const double EPS=1e-9;
  double erro;
  for (int iter = 0; iter < NMAX; ++iter){
    vmn = R*Tk/P * (1 + b/vm + c/(vm*vm));
    erro = fabs(vmn - vm);
    vm = vmn; 

    if (erro < EPS) return vm;
  }
  errorcode = 101;
  return(vm);
  
}




double Ashrae::v_(double T, double P, double xv){
  return vM_(T, P, xv) / ((1.0-xv)*Ma + xv * Mv);
}


double Ashrae::r_(double T, double P, double xv){
  return 1.0/v_(T, P, xv);
}






/*! Entalpia do gelo saturado. Retirado de [3] 173.15 < T < 273.15.
\param Tk Temp. K
\return Entalpia J/kg
*/
double Ashrae::h_s_(double Tk){
  double D[] = {-0.647595E3,
         0.274292e0,
         0.2910583e-2,
         0.1083437e-5,
		0.107e-5};

  return 1000.0 * (D[0] + D[1]*Tk + D[2]*Tk*Tk + D[3]*Tk*Tk*Tk + D[4]*Pws(Tk));
  

}


/*! Entalpia da água saturada. Retirado de [3] 273.15 < T < 473.15.
\param Tk Temp. K
\return Entalpia J/kg
*/
double Ashrae::h_l_(double Tk){
  double beta0 = Tk * v_l_(273.15) * dPws(273.15);
  double beta = Tk * v_l_(Tk) * dPws(Tk) - beta0;
  double L[] = {-0.11411380e4,
         0.41930463e1,
         -0.8134865e-4,
         0.1451133e-6,
         -0.1005230e-9,
         -0.563473,
		-0.036};

  double M[] = {-0.1141837121e4,
		0.4194325677e1,
		-0.6908894163e-4,
		0.105555302e-6,
		-0.7111382234e-10,
		0.6059e-6};
  
  double alfa;
  if (Tk < 373.125){
    
    alfa = L[0] + L[1]*Tk + L[2]*Tk*Tk + L[3]*Tk*Tk*Tk + L[4]*Tk*Tk*Tk*Tk +
      L[5] * pow(10,L[6] * (Tk- 273.15));
  }else if (373.125 < Tk && Tk <= 403.128){
    alfa = M[0] + M[1]*Tk + M[2]*Tk*Tk + M[3]*Tk*Tk*Tk + M[4]*Tk*Tk*Tk*Tk;
    
  }else{
    alfa = M[0] + M[1]*Tk + M[2]*Tk*Tk + M[3]*Tk*Tk*Tk +
      M[4]*Tk*Tk*Tk*Tk - M[5]*pow(Tk - 403.128, 3.1);
  }

  return 1000.0 * alfa + beta;
}



/*! Entalpia da fase não gasosa (T < 273.15 - h_s_, T > 273.15 - h_l_)
\param Tk Temp. K
\return Entalpia em J/kg
*/
double Ashrae::h_f_(double Tk){
  if (Tk < 273.15)
    return h_s_(Tk);
  else
    return h_l_(Tk);
}


/*! Entalpia do vapor saturado, Existe algum problema com a implementação do artigo [3]. Portanto utilizei a implementação análoga com a de h_ mas para pressão adotei a pressão de vapor a temperatura T. Os resultados coincidiram com os resultados publicados em [1] e [3].
\param Tk Temp. K
\return Entalpia J/kg
*/
double Ashrae::h_v_(double Tk){
  double xv = 1.0;
  double  xa = 0.0;

  double P = Pws(Tk);
  double a[] = {0.63290874e1,
         0.28709015e2,
         0.26431805e-2,
         -0.10405863e-4,
         0.18660410e-7,
		-0.9784331e-11};
  double d[] = {-0.5008e-2,
         0.32491829e2,
         0.65576345e-2,
         -0.26442147e-4,
         0.51751789e-7,
		-0.31541624e-10};

  // Cálculo dos coeficientes
  double B = Bww(Tk); 
  double C = Cwww(Tk); 

  double dB = dBww(Tk); 
  double dC = dCwww(Tk); 


  double hv = 35994.17;

  

  

  double termo2 = d[0] + d[1]*Tk + d[2]*Tk*Tk + d[3]*Tk*Tk*Tk +
    d[4]*pow(Tk,4) + d[5]*pow(Tk,5) + hv;

  //# Cálculo do volume molar
  double Vm = vM_v_(Tk);

  
  double termo3 = (B - Tk*dB)/Vm + (C - 0.5*Tk*dC)/(Vm*Vm);

  double hm =  termo2 * 1000.0 + R*Tk*termo3;
  
  return hm/Mv;

}



/*! Função auxiliar para cálculos que envolvem a temperatura de bulbo úmido. Esta função simplesmente faz o balanço de energia. Se o balanço é satisfeito, a função retorna 0:

\f[ (1 + \omega) \cdot h(T, P, \omega) + (\omega' - \omega)\cdot h_f(B) - (1 + \omega')\cdot h(B,P,\omega') = 0\f]

\param w Teor de umidade na entrada do saturador adiabático kg de vapor/kg de ar seco
\param T Temperatura do ar úmido K
\param B Temperatura de bulbo úmido do ar K
\param P Pressão Pa
\return Erro no balanço de energia
*/
double Ashrae::AuxWB(double w, double T, double B, double P){
  // Função auxiliar para calcular W de B
  double f1, f2;
  double xv1, xv2, w2;

  xv1 = w / (Mv/Ma + w);
  xv2 = eFactor(B, P) * Pws(B) / P;

  w2 = Mv / Ma * xv2 / (1 - xv2);

  return (1.0 + w)*h_(T, P, xv1) + (w2 - w) * h_f_(B) - (1.0 + w2) * h_(B,P,xv2);
}

/*! Dada a temperatura de bulbo úmido, esta função calcula o teor de umidade utilizando a função AuxWB e uma iteração de Newton-Raphson.
\param T Temp. K
\param B Temperatura de bulbo úmido K
\param P Pressão Pa
\return Teor de umidade \f$\omega\f$ em kg de vapor / kg de ar seco
*/
double Ashrae::CalcWfromB(double T, double B, double P){
  // Esta função calcula o teor de umidade dado T, B(TBU) e P

  // Caso fosse mistura de gases ideais, seria muito simples. Mas neste caso temos que
  // iterar. Mas usaremos o dado de TBU de gás perfeito como dado inicial.

  double w, w2, xsv, wnovo;
  const double EPS = 1e-8;
  const int NMAX = 100;
  double f, df, dw;

  xsv = eFactor(B, P) * Pws(B) / P;
  w2 = Mv / Ma * xsv / (1 - xsv);

  w = ( h_a_(B) - h_a_(T) - w2 * h_f_(B) + w2 * h_v_(B) ) / ( h_v_(T) - h_f_(B) );
  //return w;
  // Agora com este valor inicial, iterar até conseguir chegar
  for (int iter = 0; iter < NMAX; ++iter){
    f = AuxWB(w, T, B, P);
    df = (AuxWB(w + 1e-4*w2, T, B, P) - f) / (1e-4 * w2);
    
    dw = -f / df;
    w = w + dw;
    //cout << dw << endl;
    if (fabs(dw) < EPS*w2) return w;
  }

  errorcode = 103;
  return w;
}


  
double Ashrae::ENTHALPY(double T, double P){
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return h_(T, P, XV) * (1.0 + W);
}

double Ashrae::VOLUME(double T, double P){
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return v_(T, P, XV) * (1.0 + W);
}

double Ashrae::DENSITY(double T, double P){
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return r_(T, P, XV);
}


double Ashrae::DEWPOINT(double T, double P){
  // Vai ter que iterar... Que merda
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}

  // Chute inicial: Gas perfeito
  double D = Tws(XV * P);
  double Dnovo;
  double f, erro;
  const double EPS=1e-9;
  const int NMAX = 100;

  for (int iter = 0; iter < NMAX; ++iter){
    f = eFactor(D, P);

    // Calcular a nova temperatura de ponto de orvalho
    Dnovo = Tws(XV*P/f);
    erro = fabs(Dnovo - D);
    D = Dnovo;
    if (erro < EPS) return D;
  }

  errorcode = 105;
  return D;
  
      
  
}


double Ashrae::RELHUM(double T, double P){
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}
  return XV * P / (eFactor(T,P) * Pws(T));
}

double Ashrae::WETBULB(double T, double P){
  // Esta função calcula a temperatura de bulbo úmido
  // Este aqui necessariamente tem que ser iterativo. CHute inicial TBS-1
  // A função irá calcular TBU usando a função auxiliar AuxWB
  if (!FaixaT(T)) {errorcode=10;}
  if (!FaixaT(P)) {errorcode=11;}

  
  double B = T - 1.0;
  double f, df, w=W, dB;
  const double EPS=1e-7;
  const int NMAX = 400;
  double xsv;
  
  for (int iter = 0; iter < NMAX; ++iter){

    // Calcular f e df (função auxilar)
    f = AuxWB(w, T, B, P);
    df = (AuxWB(w, T, B + 0.00001, P) - f) / 0.00001;
    dB = -f / df;
    B = B + dB;
    if (fabs(dB) < EPS) return B;
  }

  errorcode = 100;
  return B;
}

    
    

double Ashrae::HUMRAT(){
  return W;
}

double Ashrae::MOLFRAC(){
  return XV;
}

int Ashrae::ERROR(){
  return errorcode;
}



