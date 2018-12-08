#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HN 3
#define N 9
#define N2 (N*N)
typedef int (*SUDO)[N];


int ip(int i,int j){return HN*(i/HN)+j/HN;}
int jv(int i,int j){return HN*(i%HN)+j%HN;}
int sudopk(SUDO sudo,int p,int k){return sudo[ip(p,k)][jv(p,k)];}
int check(int e,int t){return e&(1<<t);}
int single(int e){return (e&(e-1))==0;}
int log2(int e){
	if(e==1)return 0;
	else return 1+log2(e>>1);
}

SUDO makesudo(){
	int i,j;
	SUDO sudo=(SUDO)malloc(N*N*sizeof(int));
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			sudo[i][j]=(1<<N)-1;
		}
	}
	return sudo;
}
int sure(SUDO,int,int,int);
SUDO input(FILE* fp){
	int i,j;char s[N];
	SUDO sudo=makesudo();
	for(i=0;i<N;i++){
		fscanf(fp,"%s",s);	
		for(j=0;j<N;j++){
			if(s[j]!='='){
				if(0==sure(sudo,i,j,s[j]-'1')){
					puts("input wrong!");
					free(sudo);
					return NULL;
				}
			}
		}
	}
	return sudo;
}
void print(SUDO sudo){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d ",log2(sudo[i][j])+1);
		}
		putchar('\n');
	}
	putchar('\n');
}


int checkrow(SUDO sudo,int i,int j,int t,int j0){
	if(j==N)return j0;
	else if(check(sudo[i][j],t)==0)return checkrow(sudo,i,j+1,t,j0);
	else if(j0!=-1)return -1;
	else return checkrow(sudo,i,j+1,t,j);
}
int checkcol(SUDO sudo,int i,int j,int t,int i0){
	if(i==N)return i0;
	else if(check(sudo[i][j],t)==0)return checkcol(sudo,i+1,j,t,i0);
	else if(i0!=-1)return -1;
	else return checkcol(sudo,i+1,j,t,i);
}
int checkpal(SUDO sudo,int p,int k,int t,int k0){
	if(k==N)return k0;
	else if(check(sudopk(sudo,p,k),t)==0)return checkpal(sudo,p,k+1,t,k0);
	else if(k0!=-1)return -1;
	else return checkpal(sudo,p,k+1,t,k);
}


int exclude(SUDO sudo,int r,int c,int t){
	int p,q,temp;
	p=ip(r,c);
	
	if(check(sudo[r][c],t)==0)return 1;
	else{
		temp=sudo[r][c]&(~(1<<t));
		if(temp==0)return 0;
		else{
			if(single(temp)){if(0==sure(sudo,r,c,log2(temp)))return 0;}
			else sudo[r][c]=temp;
			
			q=checkrow(sudo,r,0,t,-1);
			if(q!=-1)if(0==sure(sudo,r,q,t))return 0;
			
			q=checkcol(sudo,0,c,t,-1);
			if(q!=-1)if(0==sure(sudo,q,c,t))return 0;
			
			q=checkpal(sudo,p,0,t,-1);
			if(q!=-1)if(0==sure(sudo,ip(p,q),jv(p,q),t))return 0;
			
			return 1;
		}
	}
}
int sure(SUDO sudo,int r,int c,int t){
	int i,j,k;int p,v;
	p=ip(r,c);v=jv(r,c);
	if(sudo[r][c]==1<<t)return 1;
	else if(check(sudo[r][c],t)==0)return 0;
	else{
		sudo[r][c]=1<<t;
		for(j=0;j<N;j++)if(j!=c)if(0==exclude(sudo,r,j,t))return 0;
		for(i=0;i<N;i++)if(i!=r)if(0==exclude(sudo,i,c,t))return 0;
		for(k=0;k<N;k++)if(k!=v)if(0==exclude(sudo,ip(p,k),jv(p,k),t))return 0;
		return 1;
	}
}
SUDO sucopy(SUDO sudo){
	SUDO su;
	su=(SUDO)malloc(N*N*sizeof(int));
	memcpy(su,sudo,N*N*sizeof(int));
	return su;
}


SUDO track(SUDO,int,int,int);
SUDO atexclude(SUDO sudo,int r,int c,int d){
	SUDO result;
	if(0==exclude(sudo,r,c,d)){free(sudo);return NULL;}
	else{
		result=track(sudo,r,c+1,0);
		if(result!=NULL)return result;
		else return NULL;
	}
}
SUDO atsure(SUDO sudo,int r,int c,int d){
	SUDO result;
	if(0==sure(sudo,r,c,d)){free(sudo);return NULL;}
	else{
		result=track(sudo,r,c+1,0);
		if(result!=NULL)return result;
		else return NULL;
	}
}


SUDO track(SUDO sudo,int r,int c,int d){
	SUDO result;
	if(r==N)return sudo;
	else if(c==N)
		return track(sudo,r+1,0,d);
	else if(single(sudo[r][c]))
		return track(sudo,r,c+1,0);
	else if(check(sudo[r][c],d)==0)
		return track(sudo,r,c,d+1);
	else{
		result=atsure(sucopy(sudo),r,c,d);
		if(result!=NULL)return result;
		else{
			result=atexclude(sucopy(sudo),r,c,d);
			if(result!=NULL)return result;
			else{free(sudo);return NULL;}
		}
	}
}

void main(){
	SUDO sudo;
	puts("input:");
	sudo=input(stdin);
	sudo=track(sudo,0,0,0);
	puts("output:");
	print(sudo);
	
}