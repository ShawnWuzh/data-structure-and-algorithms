// written by Zongheng Wu

#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
  int coeffient;
  int power;
  struct _node *next;
}Node;

typedef struct _list{
  Node *head;
  Node *last;
}List;
void create_linked_list(List *list,int coeffient,int power);
void print_linked_list(List *plist);
int main(){
  List list1;
  List list2;
  list1.head = NULL;
  list1.last = NULL;
  list2.head = NULL;
  list2.last = NULL;
  int poly1_terms = 0; // the number of terms in poly1_terms
  int poly2_terms = 0; // the number of terms in poly2_terms
  int coeffient = 0;
  int power = 0;
  // get the first polynomial from the input
  scanf("%d",&poly1_terms);
  for(int i= 0;i<poly1_terms;i++){
    scanf("%d",&coeffient);
    scanf("%d",&power);
    create_linked_list(&list1,coeffient,power);
  }
  // get the second polynomial from the input
  scanf("%d",&poly2_terms);
  for(int j = 0;j<poly2_terms;j++){
    scanf("%d",&coeffient);
    scanf("%d",&power);
    create_linked_list(&list2,coeffient,power);
  }
  print_linked_list(&list1);
  print_linked_list(&list2);
// compute the product of the two polnomials
  List list3; // This list is for saving the product
  List list4; // This list is for saving the sum
  list3.head = NULL;
  list3.last = NULL;
  list4.head = NULL;
  list4.last = NULL;
  Node* p1 = list1.head;
  // gererate the new linked list for the product of
  Node* p2 = list2.head;
  while(p2){
    coeffient = p1->coeffient * p2->coeffient;
    power = p1->power + p2->power;
    create_linked_list(&list3,coeffient,power);
    p2 = p2->next;
  }
  // insert the rest node into the existing list
  p1 = list1.head->next;
  p2 = list2.head;
  while(p1){
    while(p2){
      
    }
  }


//compute the sum of the two polynomials
  Node* p3 = list1.head;
  Node* p4 = list2.head;
  while(p3 || p4){
    if(p3 && p4){
      if(p3->power > p4->power){
        create_linked_list(&list4,p3->coeffient,p3->power);
        p3 = p3->next;
      }
      else if(p3->power < p4 ->power){
        create_linked_list(&list4,p4->coeffient,p4->power);
        p4 = p4->next;
      }
      else{
        create_linked_list(&list4,p4->coeffient + p3->coeffient,p4->power);
        p3 = p3->next;
        p4 = p4->next;
      }
    }
    else if(!p3){
      create_linked_list(&list4,p4->coeffient,p4->power);
      p4 = p4->next;
    }
    else{
      create_linked_list(&list4,p3->coeffient,p3->power);
      p3 = p3->next;
    }
  }
  print_linked_list(&list3);
  print_linked_list(&list4);
  return 0;
}
void create_linked_list(List *plist,int coeffient,int power){
  Node *p = (Node*)malloc(sizeof(Node));
  p->coeffient = coeffient;
  p->power = power;
  p->next = NULL;
  if(!plist->head){
    plist->head = p;
    plist->last = p;
  }
  else{
    plist->last->next = p;
    plist->last = p;
  }
}
void print_linked_list(List *plist){
  Node *p = plist->head;
  while(p){
    printf("%d %d ",p->coeffient,p->power);
    p = p->next;
  }
  printf("\n");
}
void sort_linked_list(){






}
