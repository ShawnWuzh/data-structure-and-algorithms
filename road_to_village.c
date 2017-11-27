// written by Zongheng Wu for DS
 #include <stdio.h>
 #define MAXCITY 1000
 #define INFI 9999

void SetTheFeeOfRootAdja(int Fee[MAXCITY],int G[MAXCITY][MAXCITY],int N,int Parent[MAXCITY]);
int PrimAlgorithm(int G[MAXCITY][MAXCITY],int Parent[MAXCITY],int Fee[MAXCITY],int N);
void BuildTheGraph(int G[MAXCITY][MAXCITY],int M);
int FindTheMin(int Fee[MAXCITY],int N);

 int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  int Parent[MAXCITY];
  int G[MAXCITY][MAXCITY];
  int Fee[MAXCITY];
  // initialize the Fee
  for(int i=0;i<N;i++){
    Fee[i] = INFI;
  }
  //initialize the tree, which is the Parent array
  for(int i=0;i<N;i++){
    Parent[i] = INFI;
  }
  // initializae the graph
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(i==j){
        G[i][j] = 0;
      }
      else{
        G[i][j] = INFI;
      }
    }
  }
  BuildTheGraph(G,M);
  // random choose the #1 city as the root of the minimum spinning tree
  Fee[0] = 0; // set the the fee of city1 to the spinning tree to 0
  Parent[0] = -1;  // set the city1 as the root
  SetTheFeeOfRootAdja(Fee,G,N,Parent);
  if(PrimAlgorithm(G,Parent,Fee,N)){
    int sum = 0;
    int parent_city;
    for(int i=0;i<N;i++){
      parent_city = Parent[i];
      if(parent_city != -1){
        sum += G[i][parent_city];
      }
    }
    printf("%d\n",sum);
  }
  else{
    printf("%d\n",-1);
  }
  return 0;
 }

 int FindTheMin(int Fee[MAXCITY],int N){
   int min_city = -1;
   int min_fee = INFI;
   for(int i=0;i<N;i++){
     if(Fee[i] < min_fee && Fee[i] != 0){
       min_city = i;
       min_fee = Fee[i];
     }
   }
   return min_city;
 }

 void SetTheFeeOfRootAdja(int Fee[MAXCITY],int G[MAXCITY][MAXCITY],int N,int Parent[MAXCITY]){
   for(int i=1;i<N;i++){
     if(Fee[i] > G[0][i]){
       Fee[i] = G[0][i];
       Parent[i] = 0;
     }
   }
 }

 int PrimAlgorithm(int G[MAXCITY][MAXCITY],int Parent[MAXCITY],int Fee[MAXCITY],int N){
   int min_city;
   int cnt = 1;
   while(1){
     min_city = FindTheMin(Fee,N);
     if(min_city == -1){
       break;
     }
     Fee[min_city] = 0;  // add the min_city to the tree
     cnt++;
     // update the neighbor of the city next to the min_city
     for(int i=0;i<N;i++){
       if(Fee[i] > G[min_city][i]){
         Fee[i] = G[min_city][i];
         Parent[i] = min_city;
       }
     }
   }
   if(cnt < N){
     return 0;
   }
   return 1;
 }



 void BuildTheGraph(int G[MAXCITY][MAXCITY],int M){
   int city1,city2,expense;
   for(int i=0;i<M;i++){
     scanf("%d %d %d",&city1,&city2,&expense);
     city1--;
     city2--;
     G[city1][city2] = expense;
     G[city2][city1] = expense;
   }
 }
