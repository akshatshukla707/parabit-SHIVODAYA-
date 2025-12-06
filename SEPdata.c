#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fptr = NULL , *fptr2= NULL;
    char timeStamp[30]; 
    double ge1Mev , ge5Mev , ge10Mev ,ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev;

    printf("HELLO IM IN MAIN>>>>>>>>>>>\n\n");

    fptr = fopen("solar proton flux codable data.txt","r");
    fptr2= fopen("DANGEROUS SEP EVENT.txt","w+");

    if(fptr==NULL || fptr2==NULL)
    {
        printf("SORRY file DNE");
        return 0;
    }
    
    while(fscanf(fptr, "%s %lf %lf %lf %lf %lf %lf %lf %lf" ,timeStamp, &ge1Mev, &ge5Mev , &ge10Mev , &ge30mEV , &ge50Mev , &ge60Mev , &ge100Mev , &ge500Mev) == 9 )
    {
       
       if(ge10Mev>10.0 || ge10Mev > 10 || ge30mEV >10 || ge50Mev>10 || ge60Mev>10  || ge100Mev>10 || ge500Mev>10)
       {
          if(ge10Mev>10.0)
          {
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

            fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 10 Mev range\n",ge10Mev);
          }
          else
          {
            if(ge30mEV>10.0)
          {
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

            fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 30 Mev range\n",ge30mEV);
            
        }
        else{
            if(ge50Mev>10.0)
          {
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

        fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 50 Mev range\n",ge50Mev);
          
    }
          else
          {
            if(ge60Mev>10.0)
          {
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

          fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 60 Mev range\n",ge60Mev);
          }
          else{
            
          if(ge100Mev>10.0)
          {
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

          fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 100 Mev range\n",ge100Mev);
          }
          else
          {
           
            fprintf(fptr2,"%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);

          fprintf(fptr2,"\nDANGEROURS because %lf value SURPASSES the 10PFU standard in 500 Mev range\n",ge500Mev);
          
          }

          }
          }
        }
    }
          
    printf("%s % lf %lf %lf %lf %lf %lf %lf %lf\n" ,timeStamp, ge1Mev, ge5Mev , ge10Mev , ge30mEV , ge50Mev , ge60Mev , ge100Mev , ge500Mev);
       }
    
    }

    printf("\n\nMAIN END<<<<<<<<<<<");
    return 0; 
} 