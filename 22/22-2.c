/*課題22-2のコードです.*/
/*24cb062h 菅原明*/



#include<stdio.h>

#define ndat 20    /**/
#define dd 1e-5
#define g 9.8


/*float func(float x, float v, float x0);*/
/*float calc_chi2(float t[],float x[],float s[], float a,float b);*/


float func_y(float t,float a, float v, float y0)
{
    float func = - 0.5*a*t*t + v*t + y0;
    return func;
}

float calc_chi2_y(float t[], float y[], float s[], float a, float b, float c)
{
  float chi2 = 0 ;
  for(int i=0;i<ndat;i++){
          if(s[i]==0){
             printf("Error:division by zero\n");
             continue ;
          }
          float diff = y[i]-func_y(t[i],a,b,c);

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
   float para_ay,para_v, para_y0;
   int ih;

   fp = fopen("u1.dat","r");


   for(ih=0;ih < ndat; ih++){
           fscanf(fp,"%f, %f, %f, %f, %f",&t[ih],&x[ih],&y[ih],&exp_y[ih],&s[ih]);
          s[ih] = 0.5;
   }
   fclose(fp);

   int try;


   float chi2_0,chi2_1, chi2_2, chi2_3, chi2_4, chi2_5, chi2_6, min_chi2;
   float  da,dv,dy0;
   int min_num,i;

   /******set initial parameters*******/
   para_ay = 5;
   para_v = 5;
   para_y0 = 5;
   /*****set step size*************/
   da = para_ay * dd;
   dv = para_v * dd;
   dy0 = para_y0 *dd;


   chi2_0 = calc_chi2_y(t, y, s, para_ay, para_v, para_y0);
   printf("chi2_0 = %f\n",chi2_0);
   for(try=0;try<1e8;try++){
           chi2_3 = calc_chi2_y(t,y,s,para_ay,para_v+dv,para_y0);
           chi2_4 = calc_chi2_y(t,y,s,para_ay,para_v-dv,para_y0);
           chi2_5 = calc_chi2_y(t,y,s,para_ay,para_v,para_y0+dy0);
           chi2_6 = calc_chi2_y(t,y,s,para_ay,para_v,para_y0-dy0);
           chi2_1 = calc_chi2_y(t,y,s,para_ay+da,para_v,para_y0);
           chi2_2 = calc_chi2_y(t,y,s,para_ay-da,para_v,para_y0);

           min_chi2 = chi2_1;
           min_num = 1;
           if(chi2_2 < min_chi2){
                   min_chi2 = chi2_2;
                   min_num = 2;
           }
           if(chi2_3 < min_chi2){
                   min_chi2 = chi2_3;
                   min_num = 3;
           }
           if(chi2_4 < min_chi2){
                   min_chi2 = chi2_4;
                   min_num = 4;
           }
           if(chi2_5 < min_chi2){
                   min_chi2 = chi2_5;
                   min_num = 5;
           }
           if(chi2_6 < min_chi2){
                   min_chi2 = chi2_6;
                   min_num = 6;
           }
         /* printf("%f,%f,%f,%f\n",min_chi2,para_ay,para_v,para_y0);*/

           if(min_chi2>chi2_0){
                   printf("reach minimum point\n");
                   break;
           }

           if(min_num == 3){para_v += dv;}
           if(min_num == 4){para_v -= dv;}
           if(min_num == 5){para_y0 += dy0;}
           if(min_num == 6){para_y0 -= dy0;}
           if(min_num == 1){para_ay += da;}
           if(min_num == 2){para_ay -= da;} 

           chi2_0 = min_chi2;
   }

   printf("minimum chi2 = %f\n",min_chi2);
   printf("at best parameters (a,v,y0) = %f,%f,%f\n",para_ay,para_v,para_y0);
   printf("search precision = %f,%f,%f\n",da,dv,dy0);

   

   return 0;
}

