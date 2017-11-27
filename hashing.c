// written by Zongheng WU for DS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct _hashtable{
  int table_size;
  int* List;
}HashNode;

typedef HashNode* HashTable;

void Insert(HashTable H,int num,int* ptime);
int Hash(int num,int table_size);
HashTable CreateTable(int N);
int NextPrime(int N);
void Destroy(HashTable H);

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  int num;
  int insert_time = 0;
  HashTable H = CreateTable(N);
  for(int i=0;i<M;i++){
    scanf("%d",&num);
    Insert(H,num,&insert_time);
  }
  Destroy(H);
  return 0;
}

void Destroy(HashTable H){
  free(H->List);
  free(H);
}

void Insert(HashTable H,int num,int* ptime){
  int insert_time = *ptime;
  int index = Hash(num,H->table_size);
  int cnt_coll = 0;
  if(H->List[index] == -1){
    H->List[index] = num;
    insert_time++;
    if(insert_time == 1){
      printf("%d",index);
    }
    else{
      printf(" %d",index);
    }
    *ptime = insert_time;
  }
  else{      // means that we have the collison, use the quadratic probing
    int cur_index = index;
    while(H->List[cur_index] != -1){
      cnt_coll++;
      cur_index = index + cnt_coll * cnt_coll;
      if(cnt_coll > H->table_size){
        cur_index = -1;
        break;
      }
      while(cur_index >= H->table_size){
        cur_index = cur_index - H->table_size;
      }
    }
    if(cur_index == -1){
      printf(" -");
    }
    else{
      H->List[cur_index] = num;
      insert_time++;
      if(insert_time == 1){
        printf("%d",cur_index);
      }
      else{
        printf(" %d",cur_index);
      }
      *ptime = insert_time;
    }
  }
}

int Hash(int num,int table_size){
  return num % table_size;
}

HashTable CreateTable(int N){
  HashTable H = (HashTable)malloc(sizeof(HashNode));
  H->table_size = NextPrime(N);
  H->List = (int*)malloc(sizeof(int) * H->table_size);
  for(int i=0;i<H->table_size;i++){
    H->List[i] = -1;  // initialize to 0 to -1 indicate that this cell is empty
  }
  return H;
}

int NextPrime(int N){
  int start = (N%2)? N:N+1;
  int isprime = 1;
  if(N == 1){
    return 2;
  }
  if(N == 2){
    return N;
  }
  while(1){
    isprime = 1;
    for(int i=2;i<(int)sqrt(start) + 1;i++){
      if(start % i == 0){
        isprime = 0;
        break;
      }
    }
    if(isprime == 1){
      return start;
    }
    else{
      start += 2;
    }
  }
  return -1;
}
