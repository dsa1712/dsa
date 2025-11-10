#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t rwlock,rlock;
//pthread_mutex_t mutex;
pthread_t rd[10],wt[10];
int rcount,data;
//--------------------------------------------------------------
void initsem()     // initialisen semaphore 
{
sem_init(&rwlock,1,1);
sem_init(&rlock,1,1);
rcount=0;
data=0;
}
//--------------------------------------------------------------

void * reader(void * r)
{
long int rno;
rno=(long int)r;
sem_wait(&rlock);
rcount++;
if(rcount==1)
{
printf("\n This is the first reader");
sem_wait(&rwlock);
}
sem_post(&rlock);
//perform reading
sleep(1);
printf("\nReader R[%ld] reads the data as %d",rno,data);
sem_wait(&rlock);
rcount--;
if(rcount==0)
{
printf("\n This is the last reader");
sem_post(&rwlock);
}
sem_post(&rlock);
pthread_exit(NULL);
}

//--------------------------------------------------------------
void * writer(void * w)
{
long int wno;
wno=(long int)w;
sem_wait(&rwlock);
data=rand()%10;
printf("\n writer W[%ld] update the data as %d",wno,data);
// performwriting
sem_post(&rwlock);
pthread_exit(NULL);
}
//--------------------------------------------------------------
int main()
{
int n1,n2;
long int i;
initsem();
printf("\n Enter the number of readers");
scanf("%d",&n1);
printf("\n Enter the number of writer");
scanf("%d",&n2);
for(i=0;i<n1;i++)
{
pthread_create(&rd[i],NULL,reader,(void *)i);
}
for(i=0;i<n1;i++)
{
pthread_join(rd[i],NULL);
}

for(i=0;i<n2;i++)
{
pthread_create(&wt[i],NULL,writer,(void *)i);
}
for(i=0;i<n2;i++)
{
pthread_join(wt[i],NULL);
}
return 0;
}
