// written by Zongheng Wu for DS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXCHAR 11
#define MAXLENGTH 5

typedef struct _node{         // the node is for saving the value
  int count;
  char tele_num[MAXCHAR+1];
  struct _node* next;
}Node;
typedef  Node* pNode;
typedef  Node* List;

typedef struct _HashNode{
  int table_size;
  List thecells;
}HashNode;

typedef HashNode* HashTable;


void DestroyTable(HashTable h);
void ScanAndOutput(HashTable h);
void Insert(HashTable h,char key[MAXCHAR+1]);
pNode Find(HashTable h,char key[MAXCHAR+1]);
int Hash(int n,int size);
HashTable CreateHashTabel(int size);
int NextPrime(int start);

int main(){
  int N;
  char key[MAXCHAR+1];
  scanf("%d",&N);
  HashTable h = CreateHashTabel(N * 2);
  for(int i=0;i<N;i++){
    scanf("%s",key);
    Insert(h,key);
    scanf("%s",key);
    Insert(h,key);
  }
  ScanAndOutput(h);
  DestroyTable(h);
  return 0;
}

void DestroyTable(HashTable h){
  int size = h->table_size;
  pNode temp;
  pNode temp1;
  for(int i=0;i<size;i++){
    temp = h->thecells[i].next;
    while(temp){
      temp1 = temp;
      temp = temp->next;
      free(temp1);
    }
  }
  free(h->thecells);
  HashTable H = h;
  free(H);
}

void ScanAndOutput(HashTable h){
  pNode temp;
  int crazy_count = 0;
  int max_count = 0;
  char min_phone[MAXCHAR+1];
  min_phone[0] = '\0';
  for(int i=0;i<h->table_size;i++){
    temp = h->thecells[i].next;
    while(temp){
      if(temp->count > max_count){
        max_count = temp->count;
        strcpy(min_phone,temp->tele_num);
        crazy_count = 1;
      }
      else if(temp->count == max_count){
        if(strcmp(min_phone,temp->tele_num) > 0){
          strcpy(min_phone,temp->tele_num);
        }
        crazy_count++;
      }
      temp = temp->next;
    }
  }
  if(crazy_count > 1){
    printf("%s %d %d\n",min_phone,max_count,crazy_count);
  }
  else{
    printf("%s %d\n",min_phone,max_count);
  }
}

void Insert(HashTable h,char key[MAXCHAR+1]){
  pNode pos;
  pNode new;
  int index;
  pos = Find(h,key);
  if(!pos){
    index = Hash(atoi(key + MAXCHAR - MAXLENGTH),h->table_size);
    new = (pNode)malloc(sizeof(Node));
    new->count = 1;
    strcpy(new->tele_num,key);
    new->next = h->thecells[index].next;
    h->thecells[index].next = new;
  }
  else{
    pos->count++;
  }
}

pNode Find(HashTable h,char key[MAXCHAR+1]){
  int index;
  index = Hash(atoi(key + MAXCHAR - MAXLENGTH),h->table_size);
  pNode p = h->thecells[index].next;
  while(p && strcmp(p->tele_num,key) != 0){
    p = p->next;
  }
  return p;
}

int Hash(int n,int size){
  return n % size;
}

HashTable CreateHashTabel(int size){
  HashTable h = (HashTable)malloc(sizeof(HashNode));
  h->table_size = NextPrime(2 * size);
  h->thecells = (pNode)malloc(sizeof(Node) * h->table_size);
  for(int i=0;i<h->table_size;i++){
    h->thecells[i].count = 0;
    h->thecells[i].next = NULL;
    h->thecells[i].tele_num[0] = '\0';
  }
  return h;
}

int NextPrime(int start){
  int i = (start % 2)? start+2:start+1;
  int isprime;
  while(1){
    isprime = 1;
    for(int j = 2;j<(int)sqrt(i) + 1;j++){
      if(i % j == 0){
        isprime = 0;
        break;
      }
    }
    if(isprime == 1){
      return i;
    }
    else{
      i += 2;
    }
  }
}
