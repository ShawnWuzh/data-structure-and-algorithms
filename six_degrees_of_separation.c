// written by Zongheng WU for DS
#include <stdio.h>
#define MAXNUMBER 10001
#include <stdlib.h>

typedef struct _node{
  int value;
  int visited;
  struct _node* next;
}Node;
typedef Node* pnode;

typedef struct _queue{
  int data[MAXNUMBER];
  int first;
  int tail;
}Queue;
typedef Queue* pQ;

int BFS(int start_point,Node Graph[],int N,pQ pq);
void ResetGraph(Node Graph[],int N);
void Reset(pnode p);
void BuildGraph(Node Graph[],int M);
void AddNewNode(pnode p,int neighbour);
void Enqueue(pQ p,int element);
int Dequeue(pQ p);

int main(){
  int N,M;
  int six_degree;
  scanf("%d %d\n",&N,&M);
  Node Graph[MAXNUMBER];
  for(int i =0;i<N;i++){
    Graph[i].value = i+1;
    Graph[i].next = NULL;
    Graph[i].visited = 0;
  }
  BuildGraph(Graph,M);
  pQ pq = (pQ)malloc(sizeof(Queue));
  pq->first = -1;
  pq->tail = -1;

  for(int i=0;i<N;i++){
    six_degree = BFS(i,Graph,N,pq);
    printf("%d: %.2f%%\n",i+1,(double)(six_degree)/N*100);
    ResetGraph(Graph,N);
    pq->first = -1;
    pq->tail = -1;
  }
  return 0;
}

int BFS(int start_point,Node Graph[],int N,pQ pq){
  int element = 0;
  int tail = 0;
  int count = 1;
  int level = 0;
  int last = 0;
  Enqueue(pq,Graph[start_point].value);
  last = Graph[start_point].value;
  Graph[start_point].visited = 1;
  while(pq->first != pq->tail){
    element = Dequeue(pq);
    pnode curp = Graph[element-1].next;
    while(curp){
      if(Graph[curp->value-1].visited == 0){
        Enqueue(pq,curp->value);
        count++;
        Graph[(curp->value)-1].visited = 1;
        tail = curp->value;
      }
      curp = curp->next;
    }
    if(element == last){
      level++;
      last = tail;
    }
    if(level == 6){
      break;
    }
  }
  return count;
}

void ResetGraph(Node Graph[],int N){
  for(int i=0;i<N;i++){
    Graph[i].visited = 0;
  }
}

void BuildGraph(Node Graph[],int M){
  int point1 = 0;
  int point2 = 0;
  for(int i=0;i<M;i++){
    scanf("%d %d",&point1,&point2);
    AddNewNode(&Graph[point1-1],point2);
    AddNewNode(&Graph[point2-1],point1);
  }
}

void AddNewNode(pnode p,int neighbour){
  pnode cur = p;
  while(cur->next){
    cur = cur->next;
  }
  pnode new = (pnode)malloc(sizeof(Node));
  new->value = neighbour;
  new->next = NULL;
  new->visited = 0;
  cur->next = new;
}

void Enqueue(pQ p,int element){
  p->data[++(p->first)] = element;
}

int Dequeue(pQ p){
  return p->data[++(p->tail)];
}
