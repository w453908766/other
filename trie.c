#include<stdio.h>
#include<stdlib.h>
#include"G:\code\setlib.h"

typedef struct TRIE{
	char c;
	set s;
}*trie;
int cmp(char c,trie t){
	return c-t->c;
}
int cmp1(trie t1,trie t2){
	return t1->c-t2->c;
}
int triesearch(set alphab,char* str){
	trie tt;
	tt=(trie)setsearch(alphab,str[0],cmp);
	if(tt==NULL)return -999;
	else if(str[0]==0)return (int)tt->s;
	else return triesearch(tt->s,str+1);
}
trie maketrie(char* str,int m){
	trie tt;
	tt=(trie)malloc(sizeof(struct TRIE));
	tt->c=str[0];
	if(str[0]==0)tt->s=(set)m;
	else{
		tt->s=makeset();
		setinsert(tt->s,maketrie(str+1,m),cmp1);
	}
	return tt;
}
void trieinsert(set alphab,char* str,int m){
	trie tt;
	tt=(trie)setsearch(alphab,str[0],cmp);
	if(tt==NULL)setinsert(alphab,maketrie(str,m),cmp1);
	else trieinsert(tt->s,str+1,m);
}
#define puti(i) printf("%d ",(i))
void main(){
	set al=makeset();
	trieinsert(al,"abcd",1);
	trieinsert(al,"abd",2);
	trieinsert(al,"bcd",3);
	trieinsert(al,"b",4);
	trieinsert(al,"efg",5);
	trieinsert(al,"hit",6);

	puti(triesearch(al,"abcd"));
	puti(triesearch(al,"abd"));
	puti(triesearch(al,"bcd"));
	puti(triesearch(al,"b"));
	puti(triesearch(al,"efg"));
	puti(triesearch(al,"hit"));
	puti(triesearch(al,"bc"));
	puti(triesearch(al,"bcde"));

}