// written by Zongheng Wu for DS
#include <stdio.h>
#include <stdlib.h>
#define MAXNUMBER 1001

void in_order_traversal(int data[],int cur_pos,int sequence[]);
void Print(int data[]);
int N;
int cmp(const void *a,const void *b){
  return (*(int*)a - *(int*)b);
}
int i =0;
int main(){
  scanf("%d",&N);
  int data[MAXNUMBER] = {0};
  int sequence[MAXNUMBER] = {0};
  for(int i = 0;i<N;i++){
    scanf("%d",&sequence[i]);
  }
  qsort(sequence,N,sizeof(int),&cmp);
  in_order_traversal(data,1,sequence);
  Print(data);
  return 0;
}
void in_order_traversal(int data[],int cur_pos,int sequence[]){
  if(cur_pos * 2 <= N){
    in_order_traversal(data,cur_pos * 2,sequence);
  }
  data[cur_pos] = sequence[i++];
  if(cur_pos * 2 + 1 <= N){
    in_order_traversal(data,cur_pos * 2 + 1,sequence);
  }
}
void Print(int data[]){
  int flag = 0;
  for(int i= 1;i<=N;i++){
    if(flag == 0){
      printf("%d",data[i]);
      flag = 1;
    }
    else{
      printf(" %d",data[i]);
    }
  }
}
