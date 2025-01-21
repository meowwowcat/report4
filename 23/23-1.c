#include<stdio.h>

#define ndat 20
#define ntry 1e7
#define RANGE 0.5


float func(float t, float v, float x0)
{
  float x = v*t + x0;
  return x;
}        

float calc_chi2(float t[], float x[], float s[], float a, float b)
{
  float chi2 = 0;
  int i;

  for(i=0;i<ndat;i++){
          diff = x[i]-func(t[i],a,b);
          chi2 += diff * diff / (s[i] * s[i]); 
  }
  return chi2
}




int main(void)
{
  FILE*fp;
  
  float t[ndat],x[ndat],y[ndat],s[ndat],exp_y[ndat];
  float para_v,para_x0,ini_v,ini_x0;
  float chi2,min_chi2,best_v,best_x0;
  int ih,i;
  int try;


  fp =fopen("u1.dat","r");

  for(ih=0;ih < ndat; ih++){
          fscanf(fp,"%f, %f, %f, %f, %f",&t[ih],&x[ih],&y[ih],&exp_y[ih],&s[ih]);
          s[ih] = 0.1;
  }
  fclose(fp);

  /*************set initial parameters*****************/
  ini_v = 5;
  ini_x0 = 5;

  min_chi2 = 1e20;
  for(try=0;try<ntry;try++){
          para_v = (float)rand() / RAND_MAX * (2*ini_v*RANGE) + ini_v * (1-RANGE);
          para_x0 = (float)rand() / RAND_MAX * (2*ini_x0*RANGE) + ini_x0*(1-RANGE);

          chi2  = calc_chi2(t,x,s,para_v,para_x0);
          if(chi2<min_chi2){
                  min_chi2 = chi2;
                  best_v = para_v;
                  best_x0 = para_x0;
                  printf("%d,%f,%f,%f\n",try,min_chi2,best_v,best_x0);
          }
  }
  printf("minimum chi2 = %f\n",min_chi2);
  printf("at best parameters = %f,%f\n",best_v,best_x0);

  return 0;
}

