// written by Zongheng WU for DS

#include <stdio.h>
#define MAXNUMBER 11
#include <stdlib.h>

typedef struct _queue{
  int data[MAXNUMBER];
  int front;
  int tail;
}Queue;
typedef Queue* pQ;

void BuildGraph(int Graph1[][MAXNUMBER],int Graph2[][MAXNUMBER],int E);
void DFS(int Graph[][MAXNUMBER],int door,int N,int Vertix1[]);
void BFS(int Graph[][MAXNUMBER],int door,int N,int Vertix2[]);
void Enqueue(pQ p,int element);
int Dequeue(pQ p);

int main(){
  int N,E;
  scanf("%d %d",&N,&E);
  int Vertix1[MAXNUMBER] = {0};
  int Vertix2[MAXNUMBER] = {0};
  for(int i=0;i<N;i++){
    Vertix1[i] = 1;
    Vertix2[i] = 1;
  }
  int Graph1[MAXNUMBER][MAXNUMBER] = {0};
  int Graph2[MAXNUMBER][MAXNUMBER] = {0};
  BuildGraph(Graph1,Graph2,E);
  for(int i=0;i<N;i++){
    if(Vertix1[i] != -1){
      printf("{ ");
      printf("%d ",i);
      Vertix1[i] = -1;
      DFS(Graph1,i,N,Vertix1);
      printf("}\n");
    }
  }
  for(int i=0;i<N;i++){
    if(Vertix2[i] != -1){
      printf("{ ");
      Vertix2[i] = -1;
      BFS(Graph2,i,N,Vertix2);
      printf("}\n");
    }
  }
  return 0;
}

void BuildGraph(int Graph1[][MAXNUMBER],int Graph2[][MAXNUMBER],int E){
  int i=0;
  int j=0;
  for(int count=0;count<E;count++){
    scanf("%d %d",&i,&j);
    Graph1[i][j] = 1;
    Graph1[j][i] = 1;
    Graph2[i][j] = 1;
    Graph2[j][i] = 1;
  }
}

void DFS(int Graph[][MAXNUMBER],int door,int N,int Vertix1[]){
  for(int i = 0;i < N;i++){
    if(Graph[i][door] != 0 && Vertix1[i] != -1){
      printf("%d ",i);
      Graph[door][i] = 0;
      Graph[i][door] = 0;
      Vertix1[i] = -1;
      DFS(Graph,i,N,Vertix1);
    }
  }
}

void BFS(int Graph[][MAXNUMBER],int door,int N,int Vertix2[]){
  pQ p = (pQ)malloc(sizeof(Queue));
  p->front = -1;
  p->tail = -1;
  Enqueue(p,door);
  while(p->front != p->tail){
    int element = Dequeue(p);
    printf("%d ",element);
    for(int i=0;i<N;i++){
      if(Graph[i][element] && Vertix2[i] != -1){
        Enqueue(p,i);
        Graph[element][i] = 0;
        Graph[i][element] = 0;
        Vertix2[i] = -1;
      }
    }
}
}

void Enqueue(pQ p,int element){
  p->data[++(p->tail)] = element;
}

int Dequeue(pQ p){
  int element;
  element = p->data[++(p->front)];
  return element;
}
