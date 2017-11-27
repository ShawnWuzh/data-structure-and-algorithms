// written by Zongheng Wu for Ds

#include <stdio.h>
#define MAXANIMAL 100
#define INFINITY 9999


void Floyd(int MGraph[][MAXANIMAL],int N);
void FindTheAnimal(int MGraph[][MAXANIMAL],int N);
void BuildGraph(int MGraph[][MAXANIMAL],int N,int M);
void InsertEdge(int MGraph[][MAXANIMAL]);
void InitializeGraph(int MGraph[][MAXANIMAL],int N);


int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  int MGraph[MAXANIMAL][MAXANIMAL];
  BuildGraph(MGraph,N,M);
  Floyd(MGraph,N);
  FindTheAnimal(MGraph,N);
  return 0;
}

void Floyd(int MGraph[][MAXANIMAL],int N){
  for(int k=0;k<N;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        if(MGraph[i][j] > MGraph[i][k] + MGraph[k][j]){
          MGraph[i][j] = MGraph[i][k] + MGraph[k][j];
        }
      }
    }
  }
}

void FindTheAnimal(int MGraph[][MAXANIMAL],int N){
  int maxdistance;
  int minanimal;
  int mindistanceofmax = INFINITY;
  for(int i=0;i<N;i++){
    maxdistance = 0;
    for(int j=0;j<N;j++){
      if(MGraph[i][j] > maxdistance){
        maxdistance = MGraph[i][j];
      }
    }
    if(maxdistance == INFINITY){
      printf("%d\n",0);
      return;
    }
    if(maxdistance < mindistanceofmax){
      minanimal = i+1;
      mindistanceofmax = maxdistance;
    }
  }
  printf("%d %d",minanimal,mindistanceofmax);

}

void BuildGraph(int MGraph[][MAXANIMAL],int N,int M){
  InitializeGraph(MGraph,N);
  for(int i=0;i<M;i++){
    InsertEdge(MGraph);
  }
}

void InsertEdge(int MGraph[][MAXANIMAL]){
  int animal1,animal2,length;
  scanf("%d %d %d",&animal1,&animal2,&length);
  animal1--;
  animal2--;
  MGraph[animal1][animal2] = length;  // since the animal index start from 1 but the matrix starts from 0
  MGraph[animal2][animal1] = length;
}

void InitializeGraph(int MGraph[][MAXANIMAL],int N){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(i==j){
        MGraph[i][j] = 0;
      }
      else{
        MGraph[i][j] = INFINITY;
      }
    }
  }
}
