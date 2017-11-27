// written by Zongheng Wu for DS

#include <stdio.h>
#include <stdlib.h>
#define MAXNUMBER 1001
#define MINELEMENT -10001

typedef struct _heap{
  int data[MAXNUMBER];
  int size;
}Heap;
typedef Heap* pheap;
void insert(pheap p,int element);
void print_path(pheap p,int position);

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  pheap p = (pheap)malloc(sizeof(Heap));
  p->size = 0;
  p->data[0] = MINELEMENT;
  int element;
  for(int i = 0;i<N;i++){
    scanf("%d",&element);
    if(p->size <= MAXNUMBER){
      insert(p,element);
    }
  }
  int position;
  for(int j = 0;j<M;j++){
    scanf("%d",&position);
    print_path(p,position);
  }
  return 0;
}

void insert(pheap p,int element){
  int i;
  for(i = ++(p->size);p->data[i/2] > element;i/=2){
    p->data[i] = p->data[i/2];
  }
  p->data[i] = element;
}

void print_path(pheap p,int position){
  int first = 1;
  for(int j = position;j>=1;j/=2){
    if(first){
      printf("%d",p->data[j]);
      first = 0;
    }
    else{
      printf(" %d", p->data[j]);
    }
  }
  printf("\n");
}
