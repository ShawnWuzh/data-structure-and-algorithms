#include <stdio.h>
#include <string.h>
#define MAXNODES 30
typedef struct _stack{
  int data[MAXNODES];
  int top;
}Stack;
typedef Stack *pStack;
void Push(int element,pStack p);
int Pop(pStack p);
void post_order(int left_index,int right_index,int root_index_in_pre);
int pre_order[MAXNODES];
int in_order[MAXNODES];
int first_print = 1;
int main(){
  Stack tree_stack;
  pStack p = &tree_stack;
  p->top = -1;
  int num_of_nodes = 0;
  int element = 0;
  scanf("%d",&num_of_nodes);
  char s[5];
  char *push = "Push";
  int count1 = 0;  // use count1 to indicate the index of pre_order array
  int count2 = 0;  // use count2 to indicate the index of in_order array
  for(int i=0;i<2 * num_of_nodes;i++){
    scanf("%s",s);
    if(strcmp(s,push) == 0){
      scanf("%d",&element);
      pre_order[count1++] = element;
      Push(element,p);
    }
    else{
      in_order[count2++] = Pop(p);
    }
  }
  // use the pre_order and in_order array to print_the_post_order
  post_order(0,num_of_nodes-1,0);
  return 0;
}
void post_order(int left_index,int right_index,int root_index_in_pre){
  int root_index;
  for(int i = left_index;i < right_index + 1;i++){    // find the index of root in in_order
    if(in_order[i] == pre_order[root_index_in_pre]){
      root_index = i;
      break;
    }
  }
  if(left_index != root_index){
    if(left_index == root_index - 1){
      if(first_print){
        printf("%d",in_order[left_index]);
        first_print = 0;
      }
      else{
        printf(" %d",in_order[left_index]);
      }
    }
    else{
      post_order(left_index,root_index-1,root_index_in_pre + 1);
    }
  }
  if(right_index != root_index){
    if(right_index == root_index + 1){
      if(first_print){
        printf("%d",in_order[right_index]);
        first_print = 0;
      }
      else{
        printf(" %d",in_order[right_index]);
      }
    }
    else{
      post_order(root_index + 1,right_index,root_index_in_pre + (root_index - left_index) + 1);
    }
}
  if(first_print){
    printf("%d",in_order[root_index]);
    first_print = 0;
  }
  else{
    printf(" %d",in_order[root_index]);
  }
}

void Push(int element,pStack p){
  p->top += 1;
  p->data[p->top] = element;
}

int Pop(pStack p){
  int value;
  value = p->data[p->top];
  p->top -= 1;
  return value;
}
