// # written by Zongheng WU for DS

#include <stdio.h>
#define MAXNUMBER 100


void HeapSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);
void SwapMax(int data[MAXNUMBER],int* psize);
void MaxHeapify(int data[MAXNUMBER],int parent,int N);
void Print(int data[MAXNUMBER],int N);
int Check(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);
int InsertionSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N);



int main(){
  int N;
  scanf("%d",&N);
  int data1[MAXNUMBER];
  int data2[MAXNUMBER];
  int number;
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    data1[i] = number;
    data2[i] = number;
  }
  int part_sorted[MAXNUMBER];
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    part_sorted[i] = number;
  }
  if(InsertionSort(data1,part_sorted,N)){
    printf("Insertion Sort\n");
    Print(data1,N);
  }
  else{
    printf("Heap Sort\n");
    HeapSort(data2,part_sorted,N);
    Print(data2,N);
  }
  return 0;
}

void HeapSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  int size = N;
  int heap_sort_flag = 0;
  for(int i = N/2 -1;i>=0;i--){
    MaxHeapify(data,i,N);
  }
  while(size){
    if(!heap_sort_flag){
      SwapMax(data,&size);
      if(Check(data,part_sorted,N)){
        heap_sort_flag = 1;
      }
    }
    else{
      SwapMax(data,&size);
      break;
    }
  }
}

void SwapMax(int data[MAXNUMBER],int* psize){
  int temp = data[0];
  int size = *psize;
  data[0] = data[size-1];
  data[size-1] = temp;
  size--;
  MaxHeapify(data,0,size);
  *psize = size;
}

void MaxHeapify(int data[MAXNUMBER],int p,int N){
  int child,root_value;
  int parent;
  root_value = data[p];
  for(parent = p;(parent * 2 + 1) < N;parent = child){
    child = 2 * parent + 1;
    if(child + 1 < N && data[child] < data[child + 1]){
      child += 1;
    }
    if(root_value >= data[child]){
      break;
    }
    else{
      data[parent] = data[child];
    }
  }
  data[parent] = root_value;
}

void Print(int data[MAXNUMBER],int N){
  printf("%d",data[0]);
  for(int i=1;i<N;i++){
    printf(" %d",data[i]);
  }
  printf("\n");
}

int Check(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  for(int i=0;i<N;i++){
    if(data[i] != part_sorted[i]){
      return 0;
    }
  }
  return 1;
}

int InsertionSort(int data[MAXNUMBER],int part_sorted[MAXNUMBER],int N){
  int new;
  int insertionflag = 0;
  int i,j;
  for(i=1;i<N;i++){
    new = data[i];
    for(j=i;j>0 && data[j-1] > new;j--){
      data[j] = data[j-1];
    }
    data[j] = new;
    if(insertionflag){
      break;
    }
    if(Check(data,part_sorted,N)){
      insertionflag = 1;
    }
  }
  return insertionflag;
}
