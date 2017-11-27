// written by Zongheng WU for DS
// the application of Dijkstra Algorithm


// first you need to have a distance array to store the
// distance of each vertex from souce to each vertex in
// the graph.And also you initialize a cloud(a set which
// saves the vertex which gets the minanimal distance done)
// each time you scan the distance array,find the minimal distance
// vertex who is not in the cloud.By doing this again and again, until
// all the vertex are pulled into the cloud.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXCROCO 101
#define INFI 9999


typedef struct _position{
  int x;
  int y;
}Position;   // use Position struct to save the x,y coordinates

int FindTheMinJump(int D[],Position G[],int Di,int N,int P[]);
void PrintPath(int P[],Position G[],int last_cro);
void  Dijkstra(int D[],int P[],int C[],int N,Position G[],int Di);
int FindTheMin(int D[],int N,int C[]);
double ComputeDistance(Position A,Position B);
void GetCrocodiles(Position G[],int N);
int FindTheFirstJump(int P[],Position G[],int last_cro);

int main(){
  int N,Di;
  scanf("%d %d",&N,&Di);
  if(Di + 7.5 >= 50){
    printf("%d\n",1);
  }
  else{
    Position G[MAXCROCO]; // use index to indicate each crocodile
    int D[MAXCROCO]; // use D to save the minimal distance from the souce to each vertex
    D[0] = 0;      // set the distance of the source to 0
    for(int i=1;i<N+1;i++){
      D[i] = INFI;
    }
    int P[MAXCROCO];  // use P to save the path to the vertex
    int C[MAXCROCO];  // use C to indicate the Cloud
    for(int i=0;i<N+1;i++){
      C[i] = -1;   // first initialize the vertix in cloud ,all to not in cloud
      P[i] = -1;   // path initialize to -1
    }
    C[0] = 1;      // add the center to the cloud which is the source vertix
    GetCrocodiles(G,N);
    for(int i=1;i<N+1;i++){
      if(ComputeDistance(G[0],G[i]) - 7.5 <= Di){
        D[i] = 1;  // the vertex is now one jump away from the center of the island
      }
    }
    Dijkstra(D,P,C,N,G,Di);
    int last_cro = FindTheMinJump(D,G,Di,N,P);
    if(last_cro == -1){
      printf("%d\n",0);
    }
    else{
      printf("%d\n",D[last_cro] + 1);
      PrintPath(P,G,last_cro);
    }
  }
  return 0;
}

int FindTheMinJump(int D[],Position G[],int Di,int N,int P[]){
  int last_cro = -1;
  int min_jump = INFI;
  int first_jump_dis = 0;
  int minimal_first_jump = INFI;
  for(int i=1;i<N+1;i++){
    if((50 - abs(G[i].x)) <= Di || (50 - abs(G[i].y)) <= Di){
      if(D[i] < min_jump){
        min_jump = D[i];
        last_cro = i;
        first_jump_dis = ComputeDistance(G[0],G[FindTheFirstJump(P,G,last_cro)]);
        minimal_first_jump = first_jump_dis;
      }
      else if(D[i] != INFI && D[i] == min_jump){
        // check the first_jump
        first_jump_dis = ComputeDistance(G[0],G[FindTheFirstJump(P,G,i)]);
        if(first_jump_dis < minimal_first_jump){
          last_cro = i;
          minimal_first_jump = first_jump_dis;
        }
      }
    }
  }
  return last_cro;
}

int FindTheFirstJump(int P[],Position G[],int last_cro){
  int i = last_cro;
  while(P[i] != -1){
    i = P[i];
  }
  return i;
}

void PrintPath(int P[],Position G[],int last_cro){
  if(P[last_cro] == -1){
    printf("%d %d\n",G[last_cro].x,G[last_cro].y);
  }
  else{
    PrintPath(P,G,P[last_cro]);
    printf("%d %d\n",G[last_cro].x,G[last_cro].y);
  }
}

                // now its time for the Dijkstra to show his power
void  Dijkstra(int D[],int P[],int C[],int N,Position G[],int Di){
  int min_crocodile;
  while(1){
    min_crocodile = FindTheMin(D,N,C);
    if(min_crocodile == -1){  // means we cannot find another min_crocodile
      break;
    }
    C[min_crocodile] = 1;  // add the min_crocodile to the cloud
    for(int i=1;i<N+1;i++){
      // check the adjacent vertex of current vertex
      if(i != min_crocodile && (ComputeDistance(G[min_crocodile],G[i]) <= Di)){
        // now it's time to update the distance of the adjacent vertex of the vertex
        // which was pulled into the cloud just now
        if(D[i] > D[min_crocodile] + 1){
          D[i] = D[min_crocodile] + 1;
          P[i] = min_crocodile;
        }
      }
    }
  }
}

int FindTheMin(int D[],int N,int C[]){
  int mindis = INFI;
  int min_crocodile = -1;
  for(int i=1;i<N+1;i++){
    if(D[i] < mindis && C[i] != 1){   // the vertix which is not in the cloud
      mindis = D[i];
      min_crocodile = i;
    }
  }
  return min_crocodile;
}

double ComputeDistance(Position A,Position B){
  double XDiff = A.x - B.x;
  double YDiff = A.y - B.y;
  double distance = sqrt(pow(XDiff,2)+pow(YDiff,2));
  return distance;
}

void GetCrocodiles(Position G[],int N){
  G[0].x = 0;
  G[0].y = 0;
  for(int i=1;i<N+1;i++){
    scanf("%d %d",&(G[i].x),&(G[i].y));
  }
}
