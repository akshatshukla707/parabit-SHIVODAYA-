#include<stdio.h>
#include<pthread.h>
#define _TIMESPEC_DEFINED
struct cb
{
    FILE *collab_ptr;
    FILE *ptr;
};

void *collabF(struct cb *cb11)
{
  char ch; 
    do
    {
      ch = (char)fgetc(cb11->ptr);

      fprintf(cb11->collab_ptr,"%d",ch);
    
    }while(ch!='*');
    
  return NULL;  
}

void *writeFile(void **arg)
{
    FILE *fptr = fopen("file.txt","a+");
    
    fprintf(fptr,"Hello My Name Is AKSHAT *");

    rewind(fptr);
    
    *arg = fptr;
}
#include<pthread.h>
int main()
{
   printf("AKSHAT");

   pthread_t thread , collab_thread;
   FILE *fptr;
   
   pthread_create(&thread, NULL , writeFile, &fptr);

   pthread_join(thread,NULL);
   
   FILE *collab_ptr = fopen("collab.txt", "a+");

   struct cb cb11;

   cb11.collab_ptr = collab_ptr;
   cb11.ptr = fptr; 



   pthread_create(&collab_ptr, NULL , collabF, &cb11);

   pthread_join(collab_thread,NULL);

 return 0;

}