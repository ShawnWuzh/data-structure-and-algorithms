// written by Zongheng WU for DS

#include <stdio.h>
#define MAXNUMBER 100

int InsertionSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);
int Check(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);
void Print(int data[MAXNUMBER],int N);
int Merge_pass(int data[MAXNUMBER],int sorted[MAXNUMBER],int part_sorted[MAXNUMBER],int length,int N);
void Merge_Sort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);
void Merge(int data[MAXNUMBER],int sorted[MAXNUMBER],int L,int R,int rightend);


int main(){
  int N;
  scanf("%d",&N);
  int data[MAXNUMBER];
  int data1[MAXNUMBER];
  int part_sorted[MAXNUMBER];
  int number;
  for(int i=0;i<N;i++){
    scanf("%d", &number);
    data[i] = number;
    data1[i] = number;
  }
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    part_sorted[i] = number;
  }
  if(InsertionSort(data,part_sorted,N)){
    printf("Insertion Sort\n");
    Print(data,N);
  }
  else{
    printf("Merge Sort\n");
    Merge_Sort(data1,part_sorted,N);
    Print(data1,N);
  }
  return 0;
}

void Print(int data[MAXNUMBER],int N){
  printf("%d",data[0]);
  for(int i=1;i<N;i++){
    printf(" %d",data[i]);
  }
  printf("\n");
}

int InsertionSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  // set the first element in the sorted list
  int new;
  int insertion_flag = 0;
  int i,j;
  for(i=1;i < N;i++){
    new = data[i];
    for(j =i;j>0 && new < data[j-1];j--){
      data[j] = data[j-1];
    }
    data[j] = new;
    if(insertion_flag){
      break;
    }
    if(Check(data,part_sorted,N)){
      insertion_flag = 1;
    }
  }
  return insertion_flag;
}


int Check(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  for(int i=0;i<N;i++){
    if(data[i] != part_sorted[i]){
      return 0;
    }
  }
  return 1;
}

// this is the procedure of merge_pass, basically it is to do the split jon manually
int Merge_pass(int data[MAXNUMBER],int sorted[MAXNUMBER],int part_sorted[MAXNUMBER],int length,int N){
  // length is the length of each sublist
  int i;
  for(i=0;i<N - 2 * length;i += 2 * length){   // merge the ajacent sublist
    Merge(data,sorted,i,i+length,i+2*length - 1);
  }
  if(i+length < N){      // merge the last two sublist pair
    Merge(data,sorted,i,i+length,N-1);
  }
  else{
    for(int j=i;j<N;j++){
      sorted[j] = data[j];
    }
  }
  if(Check(sorted,part_sorted,N)){
    return 1;
  }
  else{
    return 0;
  }
}

void Merge_Sort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  int sorted[MAXNUMBER];
  int length = 1;
  int merge_flag = 0;
  while(length < N){
    if(!merge_flag){
      if(Merge_pass(data,sorted,part_sorted,length,N)){
        merge_flag = 1;
      }
    }
    else{
      Merge_pass(data,sorted,part_sorted,length,N);
      for(int i=0;i<N;i++){
        data[i] = sorted[i];
      }
      break;
    }
    length *= 2;
    if(!merge_flag){
      if(Merge_pass(sorted,data,part_sorted,length,N)){
        merge_flag = 1;
      }
    }
    else{
      Merge_pass(sorted,data,part_sorted,length,N);
      break;
    }
    length *= 2;
  }
}

void Merge(int data[MAXNUMBER],int sorted[MAXNUMBER],int L,int R,int rightend){
  int start = L; // use the start to indicate the start of the sorted array
  int leftend = R - 1;
  int NumOfElements = rightend - L + 1;
  while(L <= leftend && R <= rightend){
    if(data[L] < data[R]){
      sorted[start++] = data[L++];
    }
    else if(data[L] > data[R]){
      sorted[start++] = data[R++];
    }
  }
  // either L is empty or R is empty
  while(L <= leftend){
    sorted[start++] = data[L++];
  }
  while(R <= rightend){
    sorted[start++] = data[R++];
  }
}
