#include <stdio.h>

typedef struct _stack{
  int data[1000];
  int top;   // use top to point to the top of the stack
  int size;  // use size to indicate the maximum capacity of the stack
  int cur_size; // use cut_size to indicate the current amount of elements in the stack
}Stack;
typedef Stack* pStack;

int push(int element,pStack p);
void pop(pStack p);
void check(int sequence[],int size_of_series,pStack p);

int main(){
  Stack check_stack;
  pStack p = &check_stack;
  int sequence[1000]={0};    // sequence to store the pop sequence
  int size_of_stack = 0; // means the maximum size of the stack
  int size_of_series = 0;// means the how many numbers to push into the stack
  int num_of_pops = 0;// means the number of the lines of pop sequences
  scanf("%d %d %d",&size_of_stack,&size_of_series,&num_of_pops);
  p->size = size_of_stack;// the maximum of the stack
  p->top = -1;// top first point to -1 position,means no elements
  p->cur_size = 0;
  for(int j= 0;j<num_of_pops;j++){   // get the input line by line
    for(int i= 0;i<size_of_series;i++){
      scanf("%d",&sequence[i]);      // get the input from the pop sequence
    }
    check(sequence,size_of_series,p);
  }
  return 0;
}

void check(int sequence[],int size_of_series,pStack p){
  int check_value = 1; // use check_value to indicate whether this sequence is possible(1)
                     // or not(0)
  int first = 0;           // use first to always point to the "first" element of sequence
  int left_size = size_of_series;// use left_size indicate the number of left
                       //elements of the series need to be pushed into the stack
  int element = 1;     // use element to represent the number which is being pushed into the stack
  int current_size;
  int top_stack;
  int push_state;
  while(left_size){    // as long as the left_size does not equal to 0;continue to push element
    check_value = 1;
    current_size = p->cur_size;
    if(current_size == 0){       // as long as the stack is empty,push one element
      push(element,p);
      left_size--;
      element += 1;
    }
    if(p->cur_size){
      top_stack = p->data[p->top];
      if(sequence[first] == top_stack){ //once the top element of the stack equals to the "first" element
                                          //of the pop sequence,means the stack has to pop up
        pop(p);
        first++;
      }
      else{
        push_state = push(element,p);
        if(!push_state){
          check_value = 0;
          break;
        }
        else{
          left_size--;
          element += 1;
        }
      }
  }
}
  while(p->cur_size){          // is stack is not empty,see if can pop there elements
    top_stack = p->data[p->top];
    if(sequence[first] == top_stack){
      pop(p);
      first++;
    }
    else{
      break;
    }
  }
  p->top = -1;      // clear the stack
  p->cur_size = 0;
   // once there is no element needs to be pop,loop continue
  if(first != size_of_series){
    check_value = 0;
  }
  if(check_value == 0){
    printf("NO\n");
  }
  else{
    printf("YES\n");
}
}

int push(int element,pStack p){
  int push_state = 0;  // use push_state to indicate push action succeed or fail;
  if(p->cur_size < p->size){
    p->data[++(p->top)] = element;// top first increment by 1, and assign the element to the
                                      // top position of the data array
    p->cur_size++;
    push_state = 1; // successfully push one element
  }
  else{             //means the stack is already full,cannot push any elements at all
    push_state = 0; // fail to push one element
  }
  return push_state;
}
void pop(pStack p){
  p->top--;
  p->cur_size--;
}
