#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;
void Print(List L);
List Merge(List L1,List L2);
void add_new_node(List list,int value);


List Merge(List L1,List L2){
  List L = (List)malloc(sizeof(struct Node));//新建一个头结点
  L->Next = NULL;
  PtrToNode head = NULL;   //指向第一个结点
  PtrToNode tail = NULL;
  PtrToNode p1 = L1->Next;    //得到头结点的Next
  PtrToNode p2 = L2->Next;
  while(p1 || p2){
    if(p1 && p2){
      if(p1->Data > p2->Data){
        if(!head){
          head = p2;
          tail = p2;
        }
        else{
          tail->Next = p2;
          tail = p2;
        }
        p2 = p2->Next;
      }
      else if(p1->Data < p2->Data){
        if(!head){
          head = p1;
          tail = p1;
        }
        else{
          tail->Next = p1;
          tail = p1;
        }
        p1 = p1->Next;
      }
      else{
        if(!head){
          head = p1;
          tail = p1;
        }
        else{
          tail->Next = p1;
          tail = p1;
        }
        p1 = p1->Next;   // this is crucial! The order here is very important
        tail -> Next = p2;
        tail = p2;
        p2 = p2->Next;
      }
    }
    else if(!p1){
      if(!head){
        head = p2;
        tail = p2;
      }
      else{
        tail->Next = p2;
        tail = p2;
      }
      p2 = p2->Next;
    }
    else if(!p2){
      if(!head){
        head = p1;
        tail = p1;
      }
      else{
        tail->Next = p1;
        tail = p1;
      }
      p1 = p1->Next;
    }
  }
  L->Next = head;
  L1->Next = NULL;
  L2->Next = NULL;
  return L;
}
void add_new_node(List list,int value){
  PtrToNode p1 = (PtrToNode)malloc(sizeof(struct Node));
  p1->Data = value;
  p1->Next = NULL;
  if(!(list->Next)){
    list->Next = p1;
  }
  else{
    PtrToNode p2 = list->Next;
    while(p2->Next){
      p2 = p2->Next;
    }
    p2->Next = p1;
  }
}

int main(){
  List L1,L2,L;
  L1 = (List)malloc(sizeof(struct Node));//初始化头结点
  L2 = (List)malloc(sizeof(struct Node));
  L1->Next = NULL;
  L2->Next = NULL;
  add_new_node(L1,1);
  add_new_node(L1,3);
  add_new_node(L1,5);
  add_new_node(L2,1);
  add_new_node(L2,3);
  add_new_node(L2,5);
  add_new_node(L2,18);
  // Print(L1);
  // Print(L2);
  L = Merge(L1,L2);
  Print(L);
  Print(L1);
  Print(L2);
  return 0;
}
void Print(List L){
  print
  PtrToNode p = L;
    while(p){
      printf("%d ",p->Data);
      p = p->Next;
    }
  printf("\n");
}
