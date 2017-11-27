// written by Zongheng Wu for DS
// implement the list leaves by queue
#include <stdio.h>
#define MAXNODES 10
#define Tree int
#define Null -1
typedef struct _queue{
  int data[MAXNODES];
  int front;
  int rear;
}Queue;
typedef Queue *pQ;
void add_to_queue(int element,pQ p);
int out_of_queue(pQ p);
int is_empty(pQ p);

typedef struct _TreeNode{
  Tree left;
  Tree right;
}TreeNode;
TreeNode T[MAXNODES];
Tree build_the_tree(int num_of_nodes);
void find_the_leaf(int num_of_nodes);


int main(){
  Tree R;
  int num_of_nodes = 0;
  char left,right;
  scanf("%d\n",&num_of_nodes);
  R = build_the_tree(num_of_nodes);
  find_the_leaf(R);
  return 0;
}
void add_to_queue(int element,pQ p){
  (p->rear)++;
  p->data[p->rear] = element;
}
int out_of_queue(pQ p){
  (p->front)++;
  return p->data[p->front];
}
int is_empty(pQ p){
  if(p->front == p->rear){
    return 1;
  }
  else{
    return 0;
  }
}
Tree build_the_tree(int num_of_nodes){
  int check[MAXNODES] = {0};
  Tree R = Null;
  char left,right;
  for(int i = 0;i<num_of_nodes;i++){
    scanf("%c %c\n",&left,&right);
    if(left == '-'){
      T[i].left = Null;
    }
    else{
      T[i].left = left - '0';
      check[T[i].left] = -1;
    }
    if(right == '-'){
      T[i].right = Null;
    }
    else{
      T[i].right = right - '0';
      check[T[i].right] = -1;
    }
  }
  for(int j = 0;j<num_of_nodes;j++){
    if(check[j] == 0){
      R = j;
      break;
    }
  }
  return R;
}
void find_the_leaf(Tree R){
  Queue q;
  int first = 1;
  q.front = q.rear = -1;
  add_to_queue(R,&q);
  while(!is_empty(&q)){
    int front_value = out_of_queue(&q);
    if(T[front_value].left == Null && T[front_value].right == Null){
      if(first){
        printf("%d",front_value);
        first = 0;
      }
      else{
        printf(" %d",front_value);
    }
    }
    else if(T[front_value].left != Null && T[front_value].right != Null){
      add_to_queue(T[front_value].left,&q);
      add_to_queue(T[front_value].right,&q);
    }
    else if(T[front_value].left == Null){
      add_to_queue(T[front_value].right,&q);
    }
    else if(T[front_value].right == Null){
      add_to_queue(T[front_value].left,&q);
    }
  }
}
