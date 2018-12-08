#include<stdio.h>
#include<stdlib.h>

typedef struct NODE{
  unsigned size;
  int data;
  struct NODE* trail;
  struct NODE* left;
  struct NODE* right;
}*tree;

unsigned size(tree t){
  return t==NULL?0:t->size;
}

tree makeTree(int data, tree l, tree r, tree trail){
  tree z = (tree)malloc(sizeof(struct NODE));
  z->data = data;
  z->left = l;
  z->right = r;
  z->trail = trail==NULL? z : trail;
  z->trail = trail;
  z->size = size(l)+size(r)+1;
  return z;
}

unsigned _puttree(tree t, unsigned n, unsigned deep, char dir){
	if(t==NULL) return n;
  else {
		unsigned rank = _puttree(t->right, n, deep+1, '/');

		for(unsigned i=0;i<deep;i++) printf("        ");
		  printf("%c %u: %d\n",dir, rank-1, t->data);

		return _puttree(t->left, rank-1, deep+1, '\\');
	}
}

void puttree(tree t){
	_puttree(t, size(t), 0, ' ');
	puts("--------------------------------------------------------------");
}

tree _splay(tree t, tree leftGrand, tree rightGrand, unsigned i, tree footmark){
  tree Guardian; 
  unsigned rank = size(t->left);
  if(i==rank){
    leftGrand->right = t->left;
    rightGrand->left = t->right;
    return makeTree(t->data, NULL, NULL, footmark);
  } else if(i<rank){
    if(footmark->left!=t) {
      Guardian = makeTree(t->data, t->left, t->right, footmark);
      rightGrand->left = Guardian;
      return _splay(t->left, leftGrand, Guardian, i, Guardian);
    } else {
      Guardian = makeTree(rightGrand->data, t->right, rightGrand->right, rightGrand);
      rightGrand->data = t->data;
      rightGrand->right = Guardian;
      return _splay(t->left, leftGrand, rightGrand, i, Guardian);
    }
  } else {
    if(footmark->right!=t){
      Guardian = makeTree(t->data, t->left, t->right, footmark);
      leftGrand->right = Guardian;
      return _splay(t->right, Guardian, rightGrand, i-rank-1, Guardian);
    } else {
      Guardian = makeTree(leftGrand->data, t->left, leftGrand->left, leftGrand);
      leftGrand->data = t->data;
      leftGrand->left = Guardian;
      return _splay(t->right, leftGrand, rightGrand, i-rank-1, Guardian);
    }
  }
}


 
tree splay(tree t, unsigned i){
  tree pope = makeTree(0, NULL, NULL, NULL);
  
  tree tt = _splay(t, pope, pope, i, pope);

  pope->data = tt->data;
  pope->trail = tt->trail;
  free(tt);

  tree swap = pope->left;
  pope->left = pope->right;
  pope->right = swap;


  tree ta=pope->trail;
  do{
    ta->size = 1 + size(ta->left) + size(ta->right);
    ta = ta->trail;
  }while(ta != pope->trail);


  return pope;
}   

void splayfree(tree t){
  tree tmp, ta = t;
  do{
    tmp = ta->trail;
    free(ta);
    ta = tmp;
  }while(ta!=t);
}




int main(){
  tree t0 = makeTree(43, NULL, makeTree(12, NULL, makeTree(22, NULL, makeTree(78, NULL, makeTree(9, NULL, makeTree(54, NULL, NULL, NULL), NULL), NULL), NULL), NULL), NULL);

  tree t1 = splay(t0, 5);
  puttree(t0);
  puttree(t1);

  splayfree(t1);
  puttree(t0);

  puttree(t1);   // will crach
  return 0;
}
