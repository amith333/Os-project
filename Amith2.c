
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
int a[100],i,n,sum=0;
float avg;

int min,max;
void *fun1();
void *fun2();
void *fun3();
int main()
{
	pid_t p;
	printf("enter the num of elements:");
	scanf("%d",&n);
	printf("enter  array elements:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	p=fork();
	if(p>0)
	{
	printf("\nparent process is created");
	printf("\n****it has  3 workers****");
	pthread_t th1,th2,th3;
	pthread_create(&th1,NULL,fun1,NULL);
	pthread_create(&th2,NULL,fun2,NULL);
	pthread_create(&th3,NULL,fun3,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	}
}
void *fun1()
{
	for(i=0;i<n;i++)
	{
		sum=sum+a[i];
	}
	avg=(float)sum/5;
	printf("\naverage value of array is :%f",avg);
	
}

void *fun2()
{
	min=a[0];
	for(i=1;i<n;i++)
	{
		if(a[i]<min)
		{
			min=a[i];
		}
	}
	printf("\nmin value in array is :%d",min);
}
void *fun3()
{
	
	max=a[0];
	for(i=1;i<n;i++)
	{
		if(a[i]>max)
		{
			max=a[i];
		}
	}
	printf("\n max value in array  :%d",max);
	
}

