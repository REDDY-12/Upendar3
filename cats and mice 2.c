#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
sem_t numcats,nummice;
int numfood=0,fcount=0;
void *cats(void *arg)
{
  int x;
 x = ((int)arg);
sem_wait(&numcats);
  fcount = fcount + 1;
 numfood++;
  if(fcount==1)
sem_wait(&nummice);
  sem_post(&numcats);
printf("food that is eaten by the cat %d is %d\n",x,numfood);
  sleep(4);
sem_wait(&numcats);
  fcount = fcount - 1;
  if(fcount==0)
 sem_post(&nummice);
  sem_post(&numcats);
  }
 void *mice(void *arg)
  {
int x;
  x = ((int) arg);
  sem_wait(&nummice);
 printf("food that is eaten by the mice %d is %d\n",x,numfood);
  sleep(2);
  sem_post(&nummice);
  }
void   main()
  {
  int i;
  pthread_t t1[5],t2[5];
 sem_init(&numcats,0,1);
  sem_init(&nummice,0,1);
for(i=0;i<=2;i++)
 {
  pthread_create(&t1[i],NULL,cats,(void *)i);
  pthread_create(&t2[i],NULL,mice,(void *)i);
  }
for(i=0;i<=2;i++)
  {
  pthread_join(t1[i],NULL);
  pthread_join(t2[i],NULL);
  }
}
