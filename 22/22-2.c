#include<stdio.h>

#define ndat 20    /**/
#define dd 1e-5



/*float func(float x, float v, float x0);*/
/*float calc_chi2(float t[],float x[],float s[], float a,float b);*/


float func(float t, float v, float x0)
{
    float func = v * t + x0;
    return func;
}

float calc_chi2(float t[], float x[], float s[], float a,float b)
{
  float chi2 = 0 ;
  for(int i=0;i<ndat;i++){
          if(s[i]==0){
             printf("Error:division by zero\n");
             continue ;
          }
          float diff = x[i]-func(t[i],a,b);

          chi2 += diff * diff/ (s[i]*s[i]);

          if(chi2 > 1e5){
             printf("Warning: chi2 has become too large\n"); 
             break;
          }
  }  
  return chi2;
}



int main(void)
{
   FILE*fp;
   float t[ndat],x[ndat],s[ndat],y[ndat],exp_y[ndat];
   float para_v, para_x0;
   int ih;

   fp = fopen("u1.dat","r");


   for(ih=0;ih < ndat; ih++){
           fscanf(fp,"%f, %f, %f, %f, %f",&t[ih],&x[ih],&y[ih],&exp_y[ih],&s[ih]);
          s[ih] = 0.1;
   }
   fclose(fp);

   int try;


   float chi2_0,chi2_1, chi2_2, chi2_3, chi2_4, min_chi2;
   float  dv,dx0;
   int min_num,i;

   /******set initial parameters*******/
   para_v = 5;
   para_x0 = 5;
   /*****set step size*************/
   dv = para_v * dd;
   dx0 = para_x0 *dd;


   chi2_0 = calc_chi2(t,x,s,para_v,para_x0);
   printf("chi2_0 = %f\n",chi2_0);
   for(try=0;try<1e8;try++){
           chi2_1 = calc_chi2(t,x,s,para_v+dv,para_x0);
           chi2_2 = calc_chi2(t,x,s,para_v-dv,para_x0);
           chi2_3 = calc_chi2(t,x,s,para_v,para_x0+dx0);
           chi2_4 = calc_chi2(t,x,s,para_v,para_x0-dx0);

           min_chi2 = chi2_1;
           min_num = 1;
           if(chi2_2 < min_chi2){
                   min_chi2 = chi2_2;
                   min_num = 2;
           }
           if(chi2_3<min_chi2){
                   min_chi2 = chi2_3;
                   min_num = 3;
           }
           if(chi2_4<min_chi2){
                   min_chi2 = chi2_4;
                   min_num = 4;
           }
          /* printf("%f,%f,%f\n",min_chi2,para_v,para_x0)*/

           if(min_chi2>chi2_0){
                   printf("reach minimum point\n");
                   break;
           }

           if(min_num == 1){para_v += dv;}
           if(min_num == 2){para_v -= dv;}
           if(min_num == 3){para_x0 += dx0;}
           if(min_num == 4){para_x0 -= dx0;}

           chi2_0 = min_chi2;
   }

   printf("minimum chi2 = %f\n",min_chi2);
   printf("at best parameters = %f,%f\n",para_v,para_x0);
   printf("search precision = %f,%f\n",dv,dx0);

   

   return 0;
}

