#include<stdio.h>
#include<stdlib.h>
#include<bool.h>
#define _TIMESPEC_DEFINED 
#include<pthread.h>

void *xrayFlux(char *cme_type)
{
   FILE *xrayPtr = fopen("xray_flux_series","r");
   char cme_typeX[20], time[30];
   int t =0;
   double value;
   
   while(fscanf(xrayPtr,"%s %s %lf" , cme_typeX, time , &value)
   {
       if(cme_typeX == cme_type)
       {
          if(value>5.0e-5)
          {
              bool = true;
          }
       }
       else
       {
        break;
       }

    }

    

}



int main()

{
    printf("HELLO IM IN MAIN<<<<<<<<<<<<<<<<");
       FILE *finalResult = fopen("result.txt","w");


    pthread_t xrayT , protonT , radioBT , solarWT ;  

    static boolean bool = FALSE;
    
    FILE *cmePtr;
    char cme_type[20], time[30] , result[10];
    double angle , width , velocity ,acc ,ke;

   
    FILE *cmeFinalPtr = fopen("cme_dangerous.txt","w");

    cmePtr = fopen("cme_events.txt","r");

    while(fscanf(cmePtr,"%s %s %lf %lf %lf %lf %lf %s", cme_type,time,&angle,&width,&velocity,&acc,&ke,result) == 8)
    {
       
        
        
        if((width>180.0) && (velocity > 800.0) && (acc < -10.0) && (ke > (1e25)))
        {
        
          printf("%s %s %lf %lf %lf %lf %lf %s\n",  cme_type,time,angle,width,velocity,acc,ke,result);
          fprintf(cmeFinalPtr,"%s %s %lf %lf %lf %lf %lf %s\n", cme_type,time,angle,width,velocity,acc,ke,result);
        
        }

    }
    
    rewind(cmeFinalPtr);
    char c;

    while(fscanf(cmeFinalPtr,"%s",cme_type)==1;)
    {
       pthread_create(xrayT,NULL ,xrayFlux, cme_type);
       
       pthread_join(xrayT,NULL);

       if(bool==TRUE)
       {
          fprintf(finalResult,"%s is DANGEROUS",cme_type)
       }

       bool=FALSE;
      
      
      while(c=(char)fgetc(cmeFinalPtr) != '\n' && c!=EOF)

    }

    printf("\n\n\nMAIN END >>>>>>>>>>>"); 
}