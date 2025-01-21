#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ndat 20 
#define ntry 1e7
#define entry 1e3
#define RANGE 0.5

/**************funcの定義***********************:*/
float func(float t, float v, float x0)
{
   float x = v*t + x0;
   return x;
}

/***************calc_chi2の定義***********************/
float calc_chi2(float t[], float x[],float s[], float a, float b)
{
  float chi2 = 0;
  int i;
  for(i=0;i<ndat;i++){
          float diff = x[i] - func(t[i], a, b);
          chi2 += diff * diff / (s[i] * s[i]);
  }
  return chi2;
}

/****************main()******************************/

int main(void)
{
   FILE*fp;

   float t[ndat],x[ndat],y[ndat],s[ndat],exp_y[ndat];
   float para_v,para_x0,ini_v,ini_x0;   
   float best_v,best_x0;
   float chi2,min_chi2;
   int i,ih,try;

   fp= fopen("u1.dat","r");

   for(i=0;i<ndat;i++){
          fscanf(fp,"%f, %f, %f, %f, %f",&t[ih],&x[ih],&y[ih],&exp_y[ih],&s[ih]);
          s[ih] = 0.5;
   }
   fclose(fp);
   
   /*----------set initial parameters-----------------*/
   ini_v = 5;
   ini_x0 = 5;

   min_chi2 = 1e20;

   for(try=0;try<ntry;try++){
           para_v = (float)rand() / RAND_MAX * (2*ini_v * RANGE) + ini_v * (1- RANGE);
           para_x0 = (float)rand() / RAND_MAX * (2*ini_x0 * RANGE) + ini_x0 *(1-RANGE);
           chi2 = calc_chi2(t,x,s,para_v,para_x0);
           if(chi2<min_chi2){
                   min_chi2 = chi2;
                   best_v = para_v;
                   best_x0 = para_x0;
           }
   }

   /****************search error region*************************/
   int ncount = 0;
   float min_v = 1e10,max_v = 1e10,min_x0=1e10,max_x0=1e10,err_v,err_x0;

   for(try=0;ncount<entry;try++){
           para_v = (float)rand() / RAND_MAX * (2*ini_v*RANGE) + ini_v * (1-RANGE);
           para_x0 = (float)rand() / RAND_MAX * (2* ini_x0*RANGE) + ini_x0 *(1-RANGE);

           chi2 = calc_chi2(t,x,s,para_v,para_x0);
           if(chi2<min_chi2+1){
                   printf("%f,%f\n",para_v,para_x0);
                   ncount++;
                   if(para_v<min_v)min_v = para_v;
                   if(para_v>max_v)max_v=para_v;
                   if(para_x0<min_x0)min_x0=para_x0;
                   if(para_x0>max_x0)max_x0=para_x0;
           }
   }
   err_v = (max_v - min_v) / 2;
   err_x0 = (max_x0 -min_x0) / 2;
   printf("v= %f +-%f, x0 = %f +- %f \n",best_v,err_v,best_x0,err_x0);

   return 0;

}

