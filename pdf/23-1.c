#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ndat 20
#define ntry 1e7
#define RANGE 0.5

/*************funcの定義*****************/
float func(float t,float a, float v, float y0)
{
  float y = -0.5*a*t*t+ v*t + y0;
  return y;
}        
/**********calc_chi2の定義**************/
float calc_chi2(float t[], float x[], float s[], float a, float b, float c)
{
  float chi2 = 0;
  int i;

  for(i=0;i<ndat;i++){
          float diff = x[i]-func(t[i],a,b,c);
          chi2 += diff * diff / (s[i] * s[i]); 
  }
  return chi2;
}

/******************main()のやつ*****************/


int main(void)
{
  FILE*fp;
  /*変数の型*/
  float t[ndat],x[ndat],y[ndat],s[ndat],exp_y[ndat];
  float para_v,para_y0,para_ay,ini_ay,ini_v,ini_y0;
  float chi2,min_chi2,best_ay,best_v,best_y0;
  int ih,i;
  int try;

/******ファイルの読み込み****/
  fp =fopen("u1.dat","r");

  for(ih=0;ih < ndat; ih++){
          fscanf(fp,"%f, %f, %f, %f, %f",&t[ih],&x[ih],&y[ih],&exp_y[ih],&s[ih]);
          s[ih] = 0.5;
  }
  fclose(fp);

  /*-------set initial parameters--------*/
  ini_ay = 8;
  ini_v = 8;
  ini_y0 = 8;

  min_chi2 = 1e20;
  for(try=0;try<ntry;try++){
          para_ay = (float)rand()/ RAND_MAX * (2*ini_ay*RANGE) + ini_ay * (1-RANGE);
          para_v = (float)rand() / RAND_MAX * (2*ini_v*RANGE) + ini_v * (1-RANGE);
          para_y0 = (float)rand() / RAND_MAX * (2*ini_y0*RANGE) + ini_y0*(1-RANGE);

          chi2  = calc_chi2(t,y,s,para_ay,para_v,para_y0);
         /* printf("chi2 = %f\n",chi2);*/
          if(chi2<min_chi2){
                  min_chi2 = chi2;
                  best_ay = para_ay;
                  best_v = para_v;
                  best_y0 = para_y0;
                  printf("%d,%f,%f,%f,%f\n",try,min_chi2,best_ay,best_v,best_y0);
          }
  }
  printf("minimum chi2 = %f\n",min_chi2);
  printf("at best parameters = %f,%f,%f\n",best_ay,best_v,best_y0);

  return 0;
}

