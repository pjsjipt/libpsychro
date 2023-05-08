// Interface excel para a biblioteca de psicrometria


//#include <windows.h>
#include "Giacomo.h"
//#include <cstdio>


#ifdef _WIN32

  /* You should define ADD_EXPORTS *only* when building the DLL. */
  #ifdef ADD_EXPORTS
    #define PSYCHROAPI __declspec(dllexport)
  #else
    #define PSYCHROAPI __declspec(dllimport)
  #endif

  /* Define calling convention in one place, for convenience. */
  #define PSYCHROCALL __stdcall

#else /* _WIN32 not defined. */

  /* Define with no value on non-Windows OSes. */
  #define PSYCHROAPI
  #define PSYCHROCALL

#endif




using namespace std;
Ashrae g;
Giacomo iso;

const int R=0, B=1, D=2, W=3, X=4;
char cc[]={'R', 'B', 'D', 'W', 'X'};
extern "C" {

  PSYCHROAPI void PSYCHROCALL psychro_density(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    double soma;
    char c=cc[*ch];
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade + soma, *p * 1000.0);
    *r = g.DENSITY(*t + 273.15, *p * 1000.0);
    
	
  }
  

  PSYCHROAPI void PSYCHROCALL psychro_volume(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.VOLUME(*t + 273.15, *p * 1000.0);
    
    
    // Teste
    //char t1[1000];
    //char t2[1000];
    //sprintf(t1, "%lf", *r);
    //sprintf(t2, "Par = %c  :  T = %lf  :  umidade = %lf  :  press = %lf", c, *t, *umidade, *p);
    //MessageBox(0, t2, t1, MB_ICONEXCLAMATION | MB_OK);
	
  }


  PSYCHROAPI void PSYCHROCALL psychro_enthalpy(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.ENTHALPY(*t + 273.15, *p * 1000.0);
    
	
  }

  PSYCHROAPI void PSYCHROCALL psychro_wetbulb(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.WETBULB(*t + 273.15, *p * 1000.0) - 273.15;
    
	
  }

  PSYCHROAPI void PSYCHROCALL psychro_dewpoint(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.DEWPOINT(*t + 273.15, *p * 1000.0) - 273.15;
    
	
  }
  

  PSYCHROAPI void PSYCHROCALL psychro_relhum(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.RELHUM(*t + 273.15, *p * 1000.0);
    
	
  }


  PSYCHROAPI void PSYCHROCALL psychro_humrat(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.HUMRAT();
  }


  PSYCHROAPI void PSYCHROCALL psychro_molfrac(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.MOLFRAC();
  }
  
  PSYCHROAPI void PSYCHROCALL psychro_Z(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    g.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = g.Z(*t+273.15, *p * 1000.0, g.XV);
  }
  
  PSYCHROAPI void PSYCHROCALL psychro_psat(double *t, double *r)
  {
    *r = g.Pws(*t + 273.15)/1000.0;
  }
  
  PSYCHROAPI void PSYCHROCALL psychro_tsat(double *p, double *r)
  {
    *r = g.Tws(*p * 1000.0) - 273.15;
  }

  

  PSYCHROAPI void PSYCHROCALL psychro_efactor(double *t, double *p, double *r)
  {
    *r = g.eFactor(*t+273.15, *p * 1000.0);
  }

  //////////////////////////////////////////////////////////////////////////////////////
  ///   GIACOMO



  PSYCHROAPI void PSYCHROCALL iso_density(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    double soma;
    char c=cc[*ch];
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade + soma, *p * 1000.0);
    *r = iso.DENSITY(*t + 273.15, *p * 1000.0);
    
	
  }
  

  PSYCHROAPI void PSYCHROCALL iso_volume(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.VOLUME(*t + 273.15, *p * 1000.0);
    
    
    // Teste
    //char t1[1000];
    //char t2[1000];
    //sprintf(t1, "%lf", *r);
    //sprintf(t2, "Par = %c  :  T = %lf  :  umidade = %lf  :  press = %lf", c, *t, *umidade, *p);
    //MessageBox(0, t2, t1, MB_ICONEXCLAMATION | MB_OK);
	
  }


  PSYCHROAPI void PSYCHROCALL iso_enthalpy(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.ENTHALPY(*t + 273.15, *p * 1000.0);
    
	
  }

  PSYCHROAPI void PSYCHROCALL iso_wetbulb(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.WETBULB(*t + 273.15, *p * 1000.0) - 273.15;
    
	
  }

  PSYCHROAPI void PSYCHROCALL iso_dewpoint(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.DEWPOINT(*t + 273.15, *p * 1000.0) - 273.15;
    
	
  }
  

  PSYCHROAPI void PSYCHROCALL iso_relhum(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.RELHUM(*t + 273.15, *p * 1000.0);
    
	
  }


  PSYCHROAPI void PSYCHROCALL iso_humrat(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.HUMRAT();
  }


  PSYCHROAPI void PSYCHROCALL iso_molfrac(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.MOLFRAC();
  }
  
  PSYCHROAPI void PSYCHROCALL iso_Z(int *ch, double *t, 
		       double *umidade, double *p, double *r)
  {
    char c = cc[*ch];
    double soma;
    soma = 0.0;
    if (c == 'B' || c == 'D') soma = 273.15;
    iso.set((*t+273.15), c, *umidade+soma, *p*1000.0);
    *r = iso.Z(*t+273.15, *p * 1000.0, iso.XV);
  }
  
  PSYCHROAPI void PSYCHROCALL iso_psat(double *t, double *r)
  {
    *r = iso.Pws(*t + 273.15)/1000.0;
  }
  
  PSYCHROAPI void PSYCHROCALL iso_tsat(double *p, double *r)
  {
    *r = iso.Tws(*p * 1000.0) - 273.15;
  }

  

  PSYCHROAPI void PSYCHROCALL iso_efactor(double *t, double *p, double *r)
  {
    *r = iso.eFactor(*t+273.15, *p * 1000.0);
  }


}
