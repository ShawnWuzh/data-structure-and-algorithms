// # written by Zongheng Wu for DS


#include <stdio.h>
#define MAXPOINTS 100
#define NOCONNEC -1


typedef struct _queue{
  int data[MAXPOINTS];
  int first;
  int tail;
}Queue;
typedef Queue* pq;

int Top(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],int Eearlist[MAXPOINTS],int N,pq q);
void EnQueue(pq p,int element);
int Dequeue(pq p);
void GetIndegree(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],int N);
void InitializeGraph(int G[MAXPOINTS][MAXPOINTS],int N);
void BuildGraph(int G[MAXPOINTS][MAXPOINTS],int M);

int main(){
  int N,M;   // N is the number of check_points
             // M is the number of activities
  scanf("%d %d",&N,&M);
  int G[MAXPOINTS][MAXPOINTS]; // use G to save the graph
  int Indegree[MAXPOINTS];  // use Indegree to save the Indegree of each check point
  for(int i=0;i<N;i++){
    Indegree[i] = 0;
  }
  int Eearlist[MAXPOINTS];  // use Eearlist to save the earlist to finish each check point
  for(int i=0;i<N;i++){
    Eearlist[i] = 0;
  }
  InitializeGraph(G,N);
  BuildGraph(G,M);
  GetIndegree(G,Indegree,N);
  Queue q;
  q.first = -1;
  q.tail = -1;
  int top_return = Top(G,Indegree,Eearlist,N,&q);
  if(top_return == 0){
    printf("Impossible\n");
  }
  else{
    int max = -1;
    for(int i=0;i<N;i++){
      if(Eearlist[i] > max){
        max = Eearlist[i];
      }
    }
    printf("%d\n",max);
  }

  return 0;
}

int Top(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],int Eearlist[MAXPOINTS],int N,pq q){
  // first add the first element whose Indegree is 0 to the Queue
  for(int i=0;i<N;i++){
    if(Indegree[i] == 0){
      EnQueue(q,i);
    }
  }
  int cur;
  int cnt = 0;
  while(1){
    if(q->first == q->tail){
      break;
    }
    // every time get a element whose Indegree is 0
    cur = Dequeue(q);
    cnt++;
    for(int i=0;i<N;i++){
      if(G[cur][i] != NOCONNEC){
        if(Eearlist[cur] + G[cur][i] > Eearlist[i]){
          Eearlist[i] = Eearlist[cur] + G[cur][i];
        }
        if(--Indegree[i] == 0){
          EnQueue(q,i);
        }
      }
    }
  }
  if(cnt != N){
    return 0;
  }
  else{
    return 1;
  }
}

void EnQueue(pq p,int element) {
  (p->first)++;
  p->data[p->first] = element;
}

int Dequeue(pq p){
  (p->tail)++;
  return p->data[p->tail];
}

void GetIndegree(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(G[i][j] != NOCONNEC){
        Indegree[j]++;
      }
    }
  }
}

void InitializeGraph(int G[MAXPOINTS][MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      G[i][j] = NOCONNEC;
    }
  }
}

void BuildGraph(int G[MAXPOINTS][MAXPOINTS],int M){
  int start,end,length;
  for(int i=0;i<M;i++){
    scanf("%d %d %d",&start,&end,&length);
    G[start][end] = length;
  }
}
