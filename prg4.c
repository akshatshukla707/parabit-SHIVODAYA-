#include<stdio.h>
#define _TIMESPEC_DEFINED 
#include<pthread.h>

struct cb
{
    FILE *collab_ptr;
    FILE *ptr;
};

void *cfunct(struct cb *cb1)
{
  char ch;
   
  rewind(cb1->ptr);
  rewind(cb1->collab_ptr);

  do
  {
    ch = (char)fgetc(cb1->ptr);
    fprintf(cb1->collab_ptr,"%c",ch);

  } while (ch!='*');
  
  fclose(cb1->collab_ptr);
  fclose(cb1->ptr);
}

int main()
{
    printf("hello im in main\n");

  FILE *fptr = fopen("file.txt","a+");
   
  rewind(fptr);
        
        fprintf(fptr,"HELLO MY NAME IS AKSHAT*");

      FILE *cptr = fopen("collab1.txt","a+");

        struct cb cb11;

        cb11.collab_ptr= cptr;
        cb11.ptr = fptr;

    pthread_t cThread;

        pthread_create(&cThread , NULL , cfunct ,&cb11);

        pthread_join(cThread,NULL);




    return 0;
}