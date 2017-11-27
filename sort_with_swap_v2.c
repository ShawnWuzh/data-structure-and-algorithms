// wriiten by Zongheng WU for DS
// compare with the solution we used in version1, we just change the way we intialize the array


#include <stdio.h>
#define MAXNUMBER 100000

int FindNotInPosition(int data[MAXNUMBER],int start,int N);

int main(){
  int data[MAXNUMBER];
  int N;
  int number;
  int count = 0;
  int temp;
  int start;
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    data[number] = i;
  }
  int not_in_position = FindNotInPosition(data,1,N);
  while(not_in_position != -1){
    if(data[0] == 0){
      data[0] = data[not_in_position];
      data[not_in_position] = 0;
      count++;
    }
    while(data[0] != 0){
      temp = data[0];
      data[0] = data[temp];
      data[temp] = temp;
      count++;
    }
    start = not_in_position + 1;
    not_in_position = FindNotInPosition(data,start,N);
  }
  printf("%d\n",count);
  return 0;
}

int FindNotInPosition(int data[MAXNUMBER],int start,int N){
  for(int i=start;i<N;i++){
    if(data[i] != i){
      return i;
    }
  }
  return -1;
}
