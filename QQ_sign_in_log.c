// written by Zongheng WU for DS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXUSERNAME 10
#define MAXPW 16
#define MAXVALUE 99999

typedef struct _node{
  char qq[MAXUSERNAME+1];
  char pw[MAXPW+1];
  struct _node* next;
}Node;

typedef Node* pNode;
typedef Node* List;

typedef struct _hashnode{
  int table_size;
  List thecells;
}HashNode;
typedef HashNode* HashTable;

void DestroyTable(HashTable H);
void Insert(HashTable H,char input_qq[MAXUSERNAME+1],char input_pw[MAXPW+1]);
pNode Find(HashTable H,char input_qq[MAXUSERNAME+1]);
HashTable CreateTable(int N);
int NextPrime(int N);
int Hash(char input_qq[MAXUSERNAME+1],int table_size);


int main(){
  int N;
  scanf("%d",&N);
  scanf("\n");
  char command;
  char input_qq[MAXUSERNAME+1];
  char input_pw[MAXPW + 1];
  HashTable H = CreateTable(N);
  pNode pos;
  for(int i=0;i<N;i++){
    scanf("%c %s %s\n",&command,input_qq,input_pw);
    if(command == 'L'){
      pos = Find(H,input_qq);
      if(!pos){
        printf("ERROR: Not Exist\n");
      }
      else{
        if(strcmp(pos->pw,input_pw) == 0){
          printf("Login: OK\n");
        }
        else{
          printf("ERROR: Wrong PW\n");
        }
      }
    }
    else if(command == 'N'){
      pos = Find(H,input_qq);
      if(!pos){
        Insert(H,input_qq,input_pw);
        printf("New: OK\n");
      }
      else{
        printf("ERROR: Exist\n");
      }
    }
  }
  DestroyTable(H);
  return 0;
}

void DestroyTable(HashTable H){
  for(int i=0;i<H->table_size;i++){
    pNode temp = H->thecells[i].next;
    pNode temp1;
    while (temp) {
      temp1 = temp;
      temp = temp->next;
      free(temp1);
    }
  }
  free(H->thecells);
  free(H);
}

void Insert(HashTable H,char input_qq[MAXUSERNAME+1],char input_pw[MAXPW+1]){
  int index = Hash(input_qq,H->table_size);
  pNode new = (pNode)malloc(sizeof(Node));
  strcpy(new->pw,input_pw);
  strcpy(new->qq,input_qq);
  new->next = H->thecells[index].next;
  H->thecells[index].next = new;
}


pNode Find(HashTable H,char input_qq[MAXUSERNAME+1]){
  int index = Hash(input_qq,H->table_size);
  pNode temp = H->thecells[index].next;
  while(temp){
    if(strcmp(temp->qq,input_qq) == 0){
      break;
    }
    temp = temp->next;
  }
  return temp;
}

int Hash(char input_qq[MAXUSERNAME+1],int table_size){
  int hash_value = 0;
  if(strlen(input_qq) == 4){
    for(int i=0;i<4;i++){
      hash_value = hash_value*10 + input_qq[i] - '0';
    }
  }
  else{
    for(int i=0;i<5;i++){
      hash_value = hash_value*10 + input_qq[i] - '0';
    }
  }
  return hash_value;
}

HashTable CreateTable(int N){
  HashTable H = (HashTable)malloc(sizeof(HashNode));
  H->table_size = NextPrime(MAXVALUE);
  H->thecells = (List)malloc(sizeof(Node) * H->table_size);
  for(int i=0;i<H->table_size;i++){
    H->thecells[i].qq[0] = '\0';
    H->thecells[i].pw[0] = '\0';
    H->thecells[i].next = NULL;
  }
  return H;
}

int NextPrime(int N){
  if(N == 1){
    return 2;
  }
  if(N == 2){
    return N;
  }
  else{
    int isprime;
    int start = N % 2? N:N+1;
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
  }
  return -1;
}
