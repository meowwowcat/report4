#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ndat 20 
#define ntry 1e7
#define entry 1e3
#define RANGE 0.5

/**************funcの定義***********************:*/
float func(float t,float a, float v, float x0)
{
   float y = -0.5*a*t*t +v*t + x0;
   return y;
}

/***************calc_chi2の定義***********************/
float calc_chi2(float t[], float x[],float s[], float a, float b, float c)
{
  float chi2 = 0;
  int i;
  for(i=0;i<ndat;i++){
          float diff = x[i] - func(t[i], a, b, c);
          chi2 += diff * diff / (s[i] * s[i]);
  }
  return chi2;
}

/****************main()******************************/

int main(void)
{
   FILE*fp;

   float t[ndat],x[ndat],y[ndat],s[ndat],exp_y[ndat];
   float para_a,para_v,para_y0,ini_a,ini_v,ini_y0;   
   float best_a,best_v,best_y0;
   float chi2,min_chi2;
   int i,ih,try;

   fp= fopen("u1.dat","r");

   for(i=0;i<ndat;i++){
          fscanf(fp,"%f, %f, %f, %f, %f",&t[i],&x[i],&y[i],&exp_y[i],&s[i]);
          s[i] = 0.5;
   }
   fclose(fp);
   
   /*----------set initial parameters-----------------*/
   ini_a = 9.8;
   ini_v = 6;
   ini_y0 = 5;

   min_chi2 = 1e20;

   for(try=0;try<ntry;try++){
           para_a = (float)rand()/ RAND_MAX * (2*ini_a * RANGE) + ini_a * (1-RANGE);
           para_v = (float)rand() / RAND_MAX * (2*ini_v * RANGE) + ini_v * (1- RANGE);
           para_y0 = (float)rand() / RAND_MAX * (2*ini_y0 * RANGE) + ini_y0 *(1-RANGE);
           chi2 = calc_chi2(t,y,s,para_a,para_v,para_y0);
           if(chi2<min_chi2){
                   min_chi2 = chi2;
                   best_a = para_a;
                   best_v = para_v;
                   best_y0 = para_y0;
           }
   }

   /****************search error region*************************/
   int ncount = 0;
   float min_a=1e10, max_a=1e-10, min_v=1e10, max_v=1e-10, min_y0=1e10, max_y0=1e-10, err_a, err_v, err_y0;

   for(try=0;ncount<entry;try++){
/*           para_v = (float)rand() / RAND_MAX * (2*ini_v*RANGE) + ini_v * (1-RANGE);*/
             para_a = (float)rand() / RAND_MAX * (2* ini_a * RANGE) + ini_a *(1-RANGE);
             para_v = (float)rand() / RAND_MAX * (2*ini_v * RANGE) + ini_v * (1- RANGE);
             para_y0 = (float)rand() / RAND_MAX * (2*ini_y0 * RANGE) + ini_y0 *(1-RANGE);
           chi2 = calc_chi2(t,y,s,para_a,para_v,para_y0);
           if(chi2<min_chi2+1){
                  ncount++; 
                   if(para_a<min_a)min_a = para_a;
                   if(para_a>max_a)max_a = para_a;
                   if(para_v<min_v)min_v = para_v;
                   if(para_v>max_v)max_v=para_v;
                   if(para_y0<min_y0)min_y0=para_y0;
                   if(para_y0>max_y0)max_y0=para_y0;
           }
           
   }
 /*  printf("%f,%f",min_v,min_y0) ;*/
   err_a = (max_a - min_a) / 2;
   err_v = (max_v - min_v) / 2;
   err_y0 = (max_y0 -min_y0) / 2;
   printf("a = %f +- %f,v= %f +-%f, y0 = %f +- %f \n",best_a,err_a,best_v,err_v,best_y0,err_y0);

   return 0;

}

