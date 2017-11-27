// wriiten by Zongheng WU for DS

#include <stdio.h>
#define MAXNUMBER 101
#include <math.h>
#include <stdlib.h>

typedef struct _postion{
  int x;
  int y;
  int visited;
}Position;
typedef Position* pPoint;

int JumpFromIsltoCroco(Position star_point,Position crocodiles[],int D,int N);
int JumpToBank(int head_index,Position crocodiles[],int D,int N);
double ComputePtPDis(Position A,Position B);

int main(){
  int N,D;
  scanf("%d %d",&N,&D);
  // get the crocodiles
  Position crocodiles[MAXNUMBER];
  for(int i=0;i<N;i++){
    scanf("%d %d",&(crocodiles[i].x),&(crocodiles[i].y));
    crocodiles[i].visited = 0;
  }
  // the start_point is center of the island
  Position star_point;
  star_point.x = 0;
  star_point.y = 0;
  if(JumpFromIsltoCroco(star_point,crocodiles,D,N)){
    printf("Yes\n");
  }
  else{
    printf("No\n");
  }
  return 0;
}

int JumpFromIsltoCroco(Position star_point,Position crocodiles[],int D,int N){
  int alive = 0;
  for(int i=0;i<N;i++){
    if(ComputePtPDis(star_point,crocodiles[i]) - 15 <= D){
      if(JumpToBank(i,crocodiles,D,N)){
        alive = 1;
        break;
      }
    }
  }
  return alive;
}

int JumpToBank(int head_index,Position crocodiles[],int D,int N){
  crocodiles[head_index].visited = 1;
  if((50 - abs(crocodiles[head_index].x) <= D) || (50 - abs(crocodiles[head_index].y) <= D)){
    return 1;
  }
  for(int i=0;i<N;i++){
    if(ComputePtPDis(crocodiles[head_index],crocodiles[i]) <= D && crocodiles[i].visited == 0){
      if(JumpToBank(i,crocodiles,D,N)){
        return 1;
      }
    }
  }
  return 0;
}

// ComputePtPDis is for computer the point to point distance
double ComputePtPDis(Position A,Position B){
  double xDiff = A.x - B.x;
  double yDiff = A.y - B.y;
  double distance = sqrt(pow(xDiff,2) + pow(yDiff,2));
  return distance;
}
