#include <time.h>
#include<stdio.h>
int f0(int n){
	if(n==0)return 0;
	else return 1+f0(n-1);
}
int f1(int a,int b){
	if(a==0)return b;
	else return f1(a-1,b+1);
}
int f2(int a){
	int b;
	for(b=0;a>0;a--)b=b+1;
	return b;
}
#define N (1<<20)
#define M (1<<30)
void main(){
	clock_t t0,t1;
	int i;
	int n;
	//scanf("%d",&n);
	t0=clock();
	for(i=0;i<M;i++)f0(N);
	t1=clock();
  	printf("%u\n",t1-t0);
  	
  	t0=clock();
	for(i=0;i<M;i++)f1(N,0);
	t1=clock();
  	printf("%u\n",t1-t0);
  	
  	t0=clock();
	for(i=0;i<M;i++)f2(N);
	t1=clock();
  	printf("%u\n",t1-t0);
  	
 }
