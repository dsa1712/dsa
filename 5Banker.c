#include<stdio.h>
int i,j,k,ch,n,m,flag,ind=0,pid;
int max[10][10],alloc[10][10],need[10][10],avail[10],f[10],safe[10],work[10],req[10];
int y=0;
//----------------------------------------------------------------------------------
void input()
{
printf("\nEnter the number of process\n");
scanf("%d",&n);
printf("Enter the number of Resources\n");
scanf("%d",&m);
printf("\n please enter the given max matrix\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
scanf("%d",&max[i][j]);
}
}

printf("\n please enter the given allocation matrix\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
scanf("%d",&alloc[i][j]);
}
}

printf("\n please enter the available vector\n");
for(j=0;j<m;j++)
{
scanf("%d",&avail[j]);
}
// calculating need
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
need[i][j]=max[i][j]-alloc[i][j];
}
}

printf("\n calculated need is\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
printf("%d \t",need[i][j]);
}
printf("\n");
}
}
//----------------------------------------------------------------------------------
void safe_seq()
{
printf("\nThis is the safe sequence");
//step 1 of bankers algo
for(i=0;i<n;i++)
{
f[i]=0;
}
for(j=0;j<m;j++)
{
work[j]=avail[j];
}
// step 2 of bankers algo
for(k=0;k<n;k++)
{
for(i=0;i<n;i++)
{
if(f[i]==0)
{
flag=0;

for(j=0;j<m;j++)
{

	if(need[i][j]>work[j])
	{
	flag=1;
	break;
	}
}
	if(flag==0)
	{
	safe[ind]=i;
	ind++;
	for(y=0;y<m;y++)
	{
	work[y]=work[y]+alloc[i][y];
	}
	f[i]=1;
	}
	}
}
}

for(i=0;i<n;i++)
{
if(f[i]==0)
{
printf("system is in unsafe state");
//break;
}
else
{
printf("\n System is in safe state");
printf("\n safe sequennce of execution is=");
for(i=0;i<n;i++)
{
printf("\n P[%d] \t",safe[i]);
}
}

}
}

//----------------------------------------------------------------------------------
void res_req()
{
printf("\n process number who has made additional request");
scanf("%d",&pid);
printf("Enter the additional request of process P[%d]",pid);
for(j=0;j<m;j++)
{
scanf("%d",&req[j]);
}

for(j=0;j<m;j++)
{
if(req[j]>need[pid][j])
{
printf("process exceed maximum claim so unable to process");
break;
}
alloc[pid][j]=alloc[pid][j]+req[j];
need[pid][j]=need[pid][j]-req[j];
avail[j]=avail[j]-req[j];
safe_seq();
}


}
//----------------------------------------------------------------------------------
void main()
{
printf("--------------------------------");
printf("|||||||BANKERS ALGORITH FOR DEADLOCK AVOIDANCE||||||||||");
printf("--------------------------------");
input();
safe_seq();
printf("is there any process who makes additional request if yes(1) or no(0)");
scanf("%d",&ch);
if(ch==1)
{
res_req();
}
else
{
printf("\n");
}
}

