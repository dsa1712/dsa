#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
sem_t full,empty;
pthread_mutex_t mutex;
pthread_t tidp[10],tidc[10];
int item,counter,size=10;
int buffer[10];
//--------------------------------------------------------------
void initsem()     // initialisen semaphore 
{
sem_init(&full,1,0);
sem_init(&empty,1,size);
pthread_mutex_init(&mutex,NULL);
counter=0;
}
//--------------------------------------------------------------

void * producer(void * p)
{
long int pno;
pno=(long int)p;
item=rand()%10;
sem_wait(&empty);
pthread_mutex_lock(&mutex);
printf("\n producer P[%ld] has produced item %d",pno,item);
buffer[counter++]=item;
pthread_mutex_unlock(&mutex);
sem_post(&full);
pthread_exit(NULL);
}

//--------------------------------------------------------------
void * consumer(void * c)
{
long int cno;
cno=(long int)c;
sem_wait(&full);
pthread_mutex_lock(&mutex);
item=buffer[--counter];
printf("\n consumer C[%ld] has consume item %d",cno,item);
pthread_mutex_unlock(&mutex);
sem_post(&empty);
pthread_exit(NULL);
}
//--------------------------------------------------------------
int main()
{
int n;
long int i;
initsem();
printf("\n Enter the size of buffer");
scanf("%d",&n);
for(i=0;i<n;i++)
{
pthread_create(&tidp[i],NULL,producer,(void *)i);
}
for(i=0;i<n;i++)
{
pthread_join(tidp[i],NULL);
}

for(i=0;i<n;i++)
{
pthread_create(&tidc[i],NULL,consumer,(void *)i);
}
for(i=0;i<n;i++)
{
pthread_join(tidc[i],NULL);
}
return 0;
}
