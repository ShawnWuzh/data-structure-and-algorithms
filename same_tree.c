#include <stdio.h>
#include <stdlib.h>
#define MAXNUMNODE 10
#define Tree int
#define Null -1

typedef struct _TreeNode{
  char value;
  Tree left;
  Tree right;
}TreeNode;
TreeNode T1[MAXNUMNODE],T2[MAXNUMNODE];
Tree read(int NumOfNodes,TreeNode T[]);
int check(Tree R1,Tree R2);

int main(){
  Tree R1,R2;
  int NumOfNodes1 = 0;
  int NumOfNodes2 = 0;
  int check_value = 0;
  scanf("%d\n",&NumOfNodes1);
  R1 = read(NumOfNodes1,T1);
  scanf("%d\n",&NumOfNodes2);
  R2 = read(NumOfNodes2,T2);
  check_value = check(R1,R2);
  if(check_value == 0){
    printf("No\n");
  }
  else if(check_value == 1){
    printf("Yes\n");
  }
  return 0;
}
Tree read(int NumOfNodes,TreeNode T[]){
  int check[MAXNUMNODE]={0};
  char left,right;
  Tree Root = Null;
  for(int i = 0;i<NumOfNodes;i++){    // read line by line
    scanf("%c %c %c\n",&(T[i].value),&left,&right);
    if(left == '-' ){
      T[i].left = -1;
    }
    else{
      T[i].left = left - '0';
      check[T[i].left] = 1;
    }
    if(right == '-' ){
      T[i].right = -1;
    }
    else{
      T[i].right = right - '0';
      check[T[i].right] = 1;
    }
  }
  for(int i = 0;i<NumOfNodes;i++){
    if(!check[i]){
      Root = i;
      break;
    }
  }
  return Root;
}
int check(Tree R1,Tree R2){
  if(R1 == Null && R2 == Null){
    return 1;
  }
  if(R1 == Null && R2 !=Null){
    return 0;
  }
  if(R1 != Null && R2 == Null){
    return 0;
  }
  if(T1[R1].value != T2[R2].value){
    return 0;
  }
  if((T1[R1].left != Null) && (T2[R2].left != Null) && T1[T1[R1].left].value == T2[T2[R2].left].value ){
    return check(T1[R1].left,T2[R2].left) && check(T1[R1].right,T2[R2].right);
  }
  else if(T2[R2].left == Null && T1[R1].left == Null){
    return check(T1[R1].right,T2[R2].right);
  }
  else{
    return check(T1[R1].left,T2[R2].right) && check(T1[R1].right,T2[R2].left);
  }
}
