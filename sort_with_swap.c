 // wriiten by Zongheng Wu for DS
 // version1 

#include <stdio.h>
#define MAXNUMBER 100000

int FindNotInPosition(int data[MAXNUMBER],int N);
int FindReplace(int data[MAXNUMBER],int N,int replace_value);
int FindZero(int data[MAXNUMBER],int N);
void Swap(int data[MAXNUMBER],int left,int right);

int main(){
  int data[MAXNUMBER];
  int number;
  int N;
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    data[i] = number;
  }
  int position_of_zero = FindZero(data,N);
  int count_swap = 0;
  int replace_position;
  int not_in_position;
  int size = N;
  while(size){
    if(position_of_zero != 0){     // find a circle contains 0
      replace_position = FindReplace(data,N,position_of_zero);
      Swap(data,replace_position,position_of_zero);
      position_of_zero = replace_position;
      count_swap++;
      size--;
    }
    else{     // which means 0 is in the 0 position
      // creat a circle contains 0
      not_in_position = FindNotInPosition(data,N);
      if(not_in_position == -1){
        break;
      }
      Swap(data,not_in_position,position_of_zero);
      position_of_zero = not_in_position;
      count_swap++;
    }
  }
  printf("%d\n",count_swap);
  return 0;
}

int FindNotInPosition(int data[MAXNUMBER],int N){
  for(int i=0;i<N;i++){
    if(data[i] != i){
      return i;
    }
  }
  return -1;
}

int FindReplace(int data[MAXNUMBER],int N,int replace_value){
  for(int i=0;i<N;i++){
    if(data[i] == replace_value){
      return i;
    }
  }
  return -1;
}

int FindZero(int data[MAXNUMBER],int N){
  for(int i=0;i<N;i++){
    if(data[i] == 0){
      return i;
    }
  }
  return -1;
}

void Swap(int data[MAXNUMBER],int left,int right){
  int temp = data[left];
  data[left] = data[right];
  data[right] = temp;
}
