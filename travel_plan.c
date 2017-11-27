//written by Zongheng WU

#include <stdio.h>
#define MAXCITY 500
#define INFI 9999

typedef struct _highway{
  int distance;
  int fee;
}Highway;

int FindTheMin(int D[MAXCITY],int C[MAXCITY],int N);
void Dijkstra(Highway G[MAXCITY][MAXCITY],int C[MAXCITY],int D[MAXCITY],int F[MAXCITY],int S,int N);
void InitializeGraph(Highway G[MAXCITY][MAXCITY],int N);
void BuildGraph(Highway G[MAXCITY][MAXCITY],int M);

int main(){
  int N,M,S,Desti;
  scanf("%d %d %d %d",&N,&M,&S,&Desti);
  Highway G[MAXCITY][MAXCITY];
  InitializeGraph(G,N);
  BuildGraph(G,M);
  int D[MAXCITY];
  int F[MAXCITY];
  for(int i=0;i<N;i++){   // use the D to save the minimum distance of the each city
    D[i] = INFI;          // initialize the minimum distnace of each city to the souce city to INFI
    F[i] = INFI;          // initialize the minimum fee of each city from souce to INFI
  }
  D[S] = 0;
  F[S] = 0;
  int C[MAXCITY];         // use the cloud to save the already saved distance of a city
  for(int i=0;i<N;i++){
    C[i] = -1;
  }
  Dijkstra(G,C,D,F,S,N);
  for(int i=0;i<N;i++){
    if(i == Desti){
      printf("%d %d\n",D[i],F[i]);
    }
  }
  return 0;
}

int FindTheMin(int D[MAXCITY],int C[MAXCITY],int N){
  int min_city = -1;
  int min_distance = INFI;
  for(int i= 0;i<N;i++){
    if(C[i] == -1 && D[i] < min_distance){
      min_distance = D[i];
      min_city = i;
    }
  }
  return min_city;
}

void Dijkstra(Highway G[MAXCITY][MAXCITY],int C[MAXCITY],int D[MAXCITY],int F[MAXCITY],int S,int N){
  while(1){
    int min_city = FindTheMin(D,C,N);
    if(min_city == -1){
      break;
    }
    else{
      C[min_city] = 1;
      // update the adjacent city
      for(int i=0;i<N;i++){
        if(D[i] > D[min_city] + G[i][min_city].distance){
          D[i] = D[min_city] + G[i][min_city].distance;
          F[i] = F[min_city] + G[i][min_city].fee;
        }
        else if(D[i] == D[min_city] + G[i][min_city].distance){
          if(F[i] > F[min_city] + G[i][min_city].fee){
            F[i] = F[min_city] + G[i][min_city].fee;
          }
        }
      }
    }
  }
}

void InitializeGraph(Highway G[MAXCITY][MAXCITY],int N){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(i==j){
        G[i][j].distance = 0;
        G[i][j].fee = 0;
      }
      else{
        G[i][j].distance = INFI;
        G[i][j].fee = INFI;
        G[j][i].distance = INFI;
        G[j][i].fee = INFI;
      }
    }
  }
}

void BuildGraph(Highway G[MAXCITY][MAXCITY],int M){
  int city1,city2,dis,fee;
  for(int i=0;i<M;i++){
    scanf("%d %d %d %d",&city1,&city2,&dis,&fee);
    G[city1][city2].distance = dis;
    G[city1][city2].fee = fee;
    G[city2][city1].distance = dis;
    G[city2][city1].fee = fee;
  }
}
