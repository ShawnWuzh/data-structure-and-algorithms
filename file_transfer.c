// written by Zongheng Wu for DS

#include <stdio.h>
#define SetType int
#define MAXNUMBER 10000


void initialization(SetType set[],int N);
void check_connection(SetType set[]);
int Find(SetType set[],int computer);
void connect_computers(SetType set[]);
void Union(SetType set[],int computer1,int computer2);
void count_components(SetType set[],int N);


int main(){
  SetType set[MAXNUMBER];
  int N;
  scanf("%d",&N);
  initialization(set,N);
  char input;
  do{
    scanf("%c",&input);
    switch (input){
      case 'C':check_connection(set);break;
      case 'I':connect_computers(set);break;
      case 'S':count_components(set,N);
    }
  }while(input!='S');
  return 0;
}

void initialization(SetType set[],int N){
  for(int i = 0;i<N;i++){
    set[i] = -1;
  }
}

void check_connection(SetType set[]){
  int computer1,computer2;
  scanf("%d %d",&computer1,&computer2);
  int Root1 = Find(set,computer1-1);
  int Root2 = Find(set,computer2-1);
  if(Root1 == Root2){
    printf("yes\n");
  }
  else{
    printf("no\n");
  }
}

int Find(SetType set[],int computer){
  if(set[computer] < 0){
    return computer;
  }
  else{
    return set[computer] = Find(set,set[computer]);
  }
}

void connect_computers(SetType set[]){
  int computer1,computer2;
  scanf("%d %d",&computer1,&computer2);
  int Root1 = Find(set,computer1-1);
  int Root2 = Find(set,computer2-1);
  if(Root1 != Root2){
    Union(set,Root1,Root2);
  }
}

void Union(SetType set[],int Root1,int Root2){
  if(set[Root1] < set[Root2]){   // this situation is the root1 has more elements
    set[Root1] = set[Root1] + set[Root2];
    set[Root2] = Root1;
  }
  else{
    set[Root2] = set[Root1] + set[Root2];
    set[Root1] = Root2;
  }
}

void count_components(SetType set[],int N){
  int networks = 0;
  for(int i=0;i<N;i++){
    if(set[i] < 0){
      networks++;
    }
  }
  if(networks == 1){
    printf("The network is connected.\n");
  }
  else{
    printf("There are %d components.\n",networks);
  }
}
