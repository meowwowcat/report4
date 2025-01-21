#include<stdio.h>

#define ndat 11
#define dd 1e-5

float func(float x, float v, float x0);
float calc_chi2(floatx[], float s[], float a, float b);

int main(void)
{
  float t[ndat] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};
  float x[ndat] = {3.2,3.6,4.2,4.1,4.0,4.4,4.9,4.8,5.2,5.1,5.5};
  float s[ndat] = {0.3,0.2,0.4,0.3,0.5,0.2,0.3,0.4,0.4,0.6,0.3};
  float par_v,par_x0;

  int try;

  float chi2_0,chi2_1,chi2_2,chi2_3,chi_4,min_chi2;
  float dv,dx0;
  int min_num,i;

  par_v=2;par_x0=3;

  dv= par_v * dd
  dx0= par_x0 * dd

  chi2_
}
