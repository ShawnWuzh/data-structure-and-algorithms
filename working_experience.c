// written by Zongheng Wu for DS

#include <stdio.h>
#define MAXNUMBER 100000
#define MAXBUCKET 51

int main(){
  int N;
  int data[MAXNUMBER];
  for(int i=0;i<N;i++){
    data[i] = 0;
  }
  scanf("%d",&N);
  int working_experience;
  for(int i=0;i<N;i++){
    scanf("%d",&working_experience);
    data[working_experience]++;
  }
  for(int i=0;i<MAXBUCKET;i++){
    if(data[i]){
      printf("%d:%d\n",i,data[i]);
    }
  }
  return 0;
}
