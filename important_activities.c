// written by Zongheng Wu for DS

#include <stdio.h>
#define MAXMISSION 10000
#define MAXPOINTS 100
#define NOCONNEC -9999
#define MAXTIME 99999
#define MINTIME 0


typedef struct _stack{
  int data[MAXMISSION];
  int top;
}Stack;
typedef Stack* pS;

typedef struct _queue{
  int data[MAXPOINTS];
  int first;
  int tail;
}Queue;
typedef Queue* pQ;

typedef struct _input{
  int start;
  int end;
  int length;
  int crucial_tag;
}Input;

void PrintCrucial(Input in[MAXMISSION],int M,int N);
void Push(pS p,int element);
int Pop(pS p);
int IsEmpty(pS p);
void MarkCrucial(int Latest[MAXPOINTS],int Eearlist[MAXPOINTS],Input in[MAXMISSION],int M);
void GetLatest(int G[MAXPOINTS][MAXPOINTS],int Latest[MAXPOINTS],int Outdegree[MAXPOINTS],pQ p,int N,int max);
void EnQueue(pQ p,int element);
int DeQueue(pQ p);
int Top(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],pQ p,int Eearlist[MAXPOINTS],int N);
void InitializeLatest(int Latest[MAXPOINTS],int N);
void InitializeEearlist(int Eearlist[MAXPOINTS],int N);
void GetIndegreeOutdegree(int Indegree[MAXPOINTS],int Outdegree[MAXPOINTS],int G[MAXPOINTS][MAXPOINTS],int N);
void InitializeIndegreeOutdegree(int Indegree[MAXPOINTS],int Outdegree[MAXPOINTS],int N);
void InitializeGraph(int G[MAXPOINTS][MAXPOINTS],int N);
void BuildGraph(int G[MAXPOINTS][MAXPOINTS],int M,Input in[MAXMISSION]);

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  Input in[MAXMISSION];
  Queue q1;
  q1.first = -1;
  q1.tail = -1;
  Queue q2;
  q2.first = -1;
  q2.tail = -1;
  int G[MAXPOINTS][MAXPOINTS];
  InitializeGraph(G,N);
  BuildGraph(G,M,in);
  int Indegree[MAXPOINTS];
  int Outdegree[MAXPOINTS];
  InitializeIndegreeOutdegree(Indegree,Outdegree,N);
  GetIndegreeOutdegree(Indegree,Outdegree,G,N);
  int Eearlist[MAXPOINTS];
  InitializeEearlist(Eearlist,N);
  int Latest[MAXPOINTS];
  InitializeLatest(Latest,N);
  if(Top(G,Indegree,&q1,Eearlist,N)){
    int max = 0;
    for(int i=0;i<N;i++){
      if(Eearlist[i] > max){
        max = Eearlist[i];
      }
    }
    printf("%d\n",max);
    GetLatest(G,Latest,Outdegree,&q2,N,max);
    MarkCrucial(Latest,Eearlist,in,M);
    PrintCrucial(in,M,N);
  }
  else{
    printf("%d\n",0);
  }
  return 0;
}

void PrintCrucial(Input in[MAXMISSION],int M,int N){
  Stack s;
  s.top = -1;
  int index;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(in[j].start == i + 1 && in[j].crucial_tag == 1){
        Push(&s,j);
      }
    }
    while(!IsEmpty(&s)){
      index = Pop(&s);
      printf("%d->%d\n",in[index].start,in[index].end);
    }
  }
}

void Push(pS p,int element){
  p->data[++(p->top)] = element;
}

int Pop(pS p){
  int element;
  element = p->data[p->top];
  (p->top)--;
  return element;
}

int IsEmpty(pS p){
  if(p->top == -1){
    return 1;
  }
  else{
    return 0;
  }
}

void MarkCrucial(int Latest[MAXPOINTS],int Eearlist[MAXPOINTS],Input in[MAXMISSION],int M){
  for(int i=0;i<M;i++){
    if(Latest[in[i].end-1] - in[i].length == Eearlist[in[i].start-1]){
      in[i].crucial_tag = 1;
    }
  }
}

void GetLatest(int G[MAXPOINTS][MAXPOINTS],int Latest[MAXPOINTS],int Outdegree[MAXPOINTS],pQ p,int N,int max){
  for(int i=0;i<N;i++){
    if(Outdegree[i] == 0){
      EnQueue(p,i);
      Latest[i] = max;
    }
  }
  int cur;
  while(p->first != p->tail){
    cur = DeQueue(p);
    for(int i=0;i<N;i++){
      if(G[i][cur] != NOCONNEC){
        if(Latest[cur] - G[i][cur] < Latest[i]){
          Latest[i] = Latest[cur] - G[i][cur];
        }
        if(--Outdegree[i] == 0){
          EnQueue(p,i);
        }
      }
    }
  }
}

void EnQueue(pQ p,int element) {
  (p->first)++;
  p->data[p->first] = element;
}

int DeQueue(pQ p){
  (p->tail)++;
  return p->data[p->tail];
}

int Top(int G[MAXPOINTS][MAXPOINTS],int Indegree[MAXPOINTS],pQ p,int Eearlist[MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    if(Indegree[i] == 0){
      EnQueue(p,i);
    }
  }
  int cur;
  int cnt = 0;
  while(p->first != p->tail){
    cur = DeQueue(p);
    cnt += 1;
    for(int i=0;i<N;i++){
      if(G[cur][i] != NOCONNEC){
        if(G[cur][i] + Eearlist[cur] > Eearlist[i]){
          Eearlist[i] = G[cur][i] + Eearlist[cur];
        }
        if(--Indegree[i] == 0){
          EnQueue(p,i);
        }
      }
    }
  }
  if(cnt < N){
    return 0;
  }
  else{
    return 1;
  }
}

void InitializeLatest(int Latest[MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    Latest[i] = MAXTIME;
  }
}

void InitializeEearlist(int Eearlist[MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    Eearlist[i] = MINTIME;
  }
}

void GetIndegreeOutdegree(int Indegree[MAXPOINTS],int Outdegree[MAXPOINTS],int G[MAXPOINTS][MAXPOINTS],int N) {
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(G[i][j] != NOCONNEC){
        Indegree[j]++;
        Outdegree[i]++;
      }
    }
  }
}

void InitializeIndegreeOutdegree(int Indegree[MAXPOINTS],int Outdegree[MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    Indegree[i] = 0;
    Outdegree[i] = 0;
  }
}

void InitializeGraph(int G[MAXPOINTS][MAXPOINTS],int N){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      G[i][j] = NOCONNEC;
    }
  }
}

void BuildGraph(int G[MAXPOINTS][MAXPOINTS],int M,Input in[MAXMISSION]){
  int start,end,length;
  for(int i=0;i<M;i++){
    scanf("%d %d %d",&start,&end,&length);
    in[i].start = start;
    in[i].end = end;
    in[i].length = length;
    in[i].crucial_tag = 0;
    start--;
    end--;
    G[start][end] = length;
   }
}
