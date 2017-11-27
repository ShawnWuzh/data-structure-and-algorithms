// written by Zongheng WU for DS

#include <stdio.h>
#define MAXNUMBER 100000

void Print(int data[MAXNUMBER],int N);
void BubbleSort(int data[MAXNUMBER],int N);
void InsertionSort(int data[MAXNUMBER],int N);
void MergeSort(int data[MAXNUMBER],int N);
void Msort(int data[MAXNUMBER],int sorted[MAXNUMBER],int start,int end);
void Merge(int data[MAXNUMBER],int sorted[MAXNUMBER],int L,int R,int rightend);
void Merge_pass(int data[MAXNUMBER],int sorted[MAXNUMBER],int length,int N);
void Merge_Sort_itetative(int data[MAXNUMBER],int N);
void Merge1(int data[MAXNUMBER],int sorted[MAXNUMBER],int L,int R,int rightend);
int Median3(int data[MAXNUMBER],int left,int right);
void Swap(int data[MAXNUMBER],int left,int right);
void QuickSort(int data[MAXNUMBER],int N);
void QS(int data[MAXNUMBER],int left,int right);
void ShellSort(int data[MAXNUMBER],int N);
void HeapSort(int data[MAXNUMBER],int N);
void RadixSort(int data[MAXNUMBER],int N);
void TableSort(int data[MAXNUMBER],int N);



int main(){
  int N;
  int data[MAXNUMBER];
  scanf("%d",&N);
  int number;
  for(int i=0;i<N;i++){
    scanf("%d",&number);
    data[i] = number;
  }
  // BubbleSort(data,N);
  // Print(data,N);
  // InsertionSort(data,N);
  // Print(data,N);
  QuickSort(data,N);
  Print(data,N);
  return 0;
}

void Print(int data[MAXNUMBER],int N){
  printf("%d",data[0]);
  for(int i=1;i<N;i++){
    printf(" %d",data[i]);
  }
  printf("\n");
}

int Median3(int data[MAXNUMBER],int left,int right){
  int median = (left + right) / 2;
  if(data[left] > data[median]){
    Swap(data,left,median);
  }
  if(data[left] > data[right]){
    Swap(data,left,right);
  }
  if(data[median] > data[right]){
    Swap(data,median,right);
  }
  Swap(data,median,right-1);
  return data[right-1];
}

void Swap(int data[MAXNUMBER],int left,int right){
  int temp = data[left];
  data[left] = data[right];
  data[right] = temp;
}

void QuickSort(int data[MAXNUMBER],int N){
  QS(data,0,N-1);
}

void QS(int data[MAXNUMBER],int left,int right){
  int pivot,cutoff,low,high;
  cutoff = 100;
  if(cutoff < right - left){
    pivot = Median3(data,left,right);
    low = left;
    high = right-1;
    while(1){
      while(data[++low] < pivot);
      while(data[--high] > pivot);
      if(low < high){
        Swap(data,low,high);
      }
      else{
        break;
      }
    }
    Swap(data,low,right -1);
    QS(data,left,low-1);
    QS(data,low+1,right);
  }
  else{
    InsertionSort(data+left,right - left + 1);
  }
}

void BubbleSort(int data[MAXNUMBER],int N){
  int temp;
  int flag;
  for(int i=N-1;i>=0;i--){
    flag = 0;
    for(int j = 0;j<i;j++){
      if(data[j] > data[j+1]){
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
        flag = 1;
      }
    }
    if(!flag){
      break;
    }
  }
}

void InsertionSort(int data[MAXNUMBER],int N){
  // set the element in the sorted_list
  int new;
  int i,j;
  for(i=1;i<N;i++){
    new = data[i];
    // then we will insert the new into the sorted list
    for(j=i;j>0 && data[j-1] > new;j--){
      data[j] = data[j-1];
    }
    data[j] = new;
  }
}

void MergeSort(int data[MAXNUMBER],int N){
  int sorted[MAXNUMBER];
  Msort(data,sorted,0,N-1);
}

void Msort(int data[MAXNUMBER],int sorted[MAXNUMBER],int start,int end){
  if(start < end){
    Msort(data,sorted,start,(start + end) / 2);
    Msort(data,sorted,(start + end) / 2 + 1,end);
    Merge(data,sorted,start,(start + end) / 2 + 1,end);
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
  for(int i=0;i<NumOfElements;i++,rightend--){
    data[rightend] = sorted[rightend];
  }
}

// this is the procedure of merge_pass, basically it is to do the split jon manually
void Merge_pass(int data[MAXNUMBER],int sorted[MAXNUMBER],int length,int N){
  // length is the length of each sublist
  int i;
  for(i=0;i<N - 2 * length;i += 2 * length){   // merge the ajacent sublist
    Merge1(data,sorted,i,i+length,i+2*length - 1);
  }
  if(i+length < N){      // merge the last two sublist pair
    Merge1(data,sorted,i,i+length,N-1);
  }
  else{
    for(int j=i;j<N;j++){
      sorted[j] = data[j];
    }
  }
}

void Merge_Sort_itetative(int data[MAXNUMBER],int N){
  int sorted[MAXNUMBER];
  int length = 1;
  while(length < N){
    Merge_pass(data,sorted,length,N);
    length *= 2;
    Merge_pass(sorted,data,length,N);
    length *= 2;
  }
}

void Merge1(int data[MAXNUMBER],int sorted[MAXNUMBER],int L,int R,int rightend){
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
