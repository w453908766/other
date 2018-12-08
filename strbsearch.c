#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define puti(i) printf("%d ",(i))


char* sarr[]={"create","insert","delete","update","select","alter","drop"};
void putstrarr(char** sarr,int n){
	if(n==0)putchar('\n');
	else{
		puts(sarr[0]);
		putstrarr(sarr+1,n-1);
	}
}
int cmp(const void* a,const void* b){
	return strcmp(*(char**)a,*(char**)b);
}
void main(){
	char* s="insert";
	putstrarr(sarr,	7);
	qsort(sarr,7,sizeof(char*),cmp);
	putstrarr(sarr,	7);

	puti((char**)bsearch(&s,sarr,7,sizeof(char*),cmp)-sarr);
}
