#include<stdio.h>
#include<stdlib.h>
#define _TIMESPEC_DEFINED 
#include<pthread.h>

int main()

{
    printf("HELLO IM IN MAIN<<<<<<<<<<<<<<<<");
    
    FILE *cmePtr;
    char cme_type[20], time[20] , result[10];
    double angle , width , velocity ,acc ,ke;

   
    FILE *cmeFinalPtr = fopen("cme_dangerous.txt","w");

    cmePtr = fopen("cme_events.txt","r");

    while(fscanf(cmePtr,"%s %s %lf %lf %lf %lf %lf %s", cme_type,time,&angle,&width,&velocity,&acc,&ke,result) == 8)
    {
       
        
        
        if((width>180.0) && (velocity > 800.0) && (acc < -10.0) && (ke > (10^25)))
        {
        
          printf("%s %s %lf %lf %lf %lf %lf %s\n",  cme_type,time,angle,width,velocity,acc,ke,result);
          fprintf(cmeFinalPtr,"%s %s %lf %lf %lf %lf %lf %s\n", cme_type,time,angle,width,velocity,acc,ke,result);
        
        }
/*
        printf("%s %s %lf %lf %lf %lf %lf %s\n",  cme_type,time,angle,width,velocity,acc,ke,result);
          fprintf(cmeFinalPtr,"%s %s %lf %lf %lf %lf %lf %s\n", cme_type,time,angle,width,velocity,acc,ke,result);
        
   */     

    }

    printf("\n\n\nMAIN END >>>>>>>>>>>"); 
}