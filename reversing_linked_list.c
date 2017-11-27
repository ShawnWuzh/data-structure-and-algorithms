#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int address;
  int data;
  int next_addr;
  struct _node* next;
}Node;
typedef Node* ptrNode;

void Add_new_node(int address,int data,int next_addr,ptrNode *pptrNode);
ptrNode reverse_linked_list(int size_sub,int size,ptrNode *plist);
ptrNode Read(int size);
ptrNode arrange_linked_list(int first_addr,ptrNode *pptrNode,int* size);
void Print(ptrNode list);

int main(){
  int first_addr = 0;
  int size = 0;
  int size_sub = 0;
  scanf("%d %d %d",&first_addr,&size,&size_sub);
  ptrNode list = Read(size);
  ptrNode new_list = arrange_linked_list(first_addr,&list,&size);
  ptrNode reverse_list = reverse_linked_list(size_sub,size,&new_list);
  Print(reverse_list);
  return 0;
}

ptrNode Read(size){
  int address = 0;
  int data = 0;
  int next_addr = 0;
  ptrNode list = (ptrNode)malloc(sizeof(Node));
  list->next = NULL;
  ptrNode rear = list;
  for(int i=0;i<size;i++){
    scanf("%d %d %d",&address,&data,&next_addr);
    Add_new_node(address,data,next_addr,&rear);
  }
  return list;
}

void Add_new_node(int address,int data,int next_addr,ptrNode* pRear){
  ptrNode p = (ptrNode)malloc(sizeof(Node));
  p->address = address;
  p->data = data;
  p->next_addr = next_addr;
  p->next = NULL;
  (*pRear)->next = p;
  (*pRear) = p;
}

ptrNode arrange_linked_list(int first_addr,ptrNode *pptrNode,int* size){
  int next_addr = first_addr;
  int true_size = 0;
  ptrNode new_list = (ptrNode)malloc(sizeof(Node));
  new_list->next = NULL;
  ptrNode rear = new_list;
  ptrNode temp1;
  while(next_addr != -1){
    ptrNode temp = *pptrNode;
    while(temp->next){
      if(temp->next->address == next_addr){
        true_size += 1;
        Add_new_node(temp->next->address,temp->next->data,temp->next->next_addr,&rear);
        next_addr = temp->next->next_addr;
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
        break;
      }
      temp = temp->next;
    }
  }
  *size = true_size;
  return new_list;

}

ptrNode reverse_linked_list(int size_sub,int size,ptrNode *plist){
  ptrNode reverse_list = (ptrNode)malloc(sizeof(Node));
  reverse_list->next = NULL;
  ptrNode rear = reverse_list;
  int cnt = 0;
  int cnt_sb = 0;
  int fir_ele_of_sub = 0; // use this flag to indicate that this is the first element of the sublist
  ptrNode temp,temp1;
  while(size >= size_sub){   // 只要链表的size大于子链表的size，循环继续。
    temp = *plist;
    int left_size = size_sub;
    fir_ele_of_sub = 0;
    while(left_size > 0){
      cnt++;
      if(cnt == left_size){
        if(cnt_sb >= 1 && fir_ele_of_sub == 0){
          rear->next_addr = temp->next->address;
          fir_ele_of_sub = 1;
        }
        cnt = 0;
        left_size--;
        Add_new_node(temp->next->address,temp->next->data,temp->address,&rear);
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
        size--;
        temp = *plist;
      }
      else{
        temp = temp->next;
      }
    }
    cnt_sb += 1;
  }
  int tag = 0;
  while(size){
    if(tag == 0){
      rear->next_addr = temp->next->address;
      tag = 1;
    }
    Add_new_node(temp->next->address,temp->next->data,temp->next->next_addr,&rear);
    temp1 = temp->next;
    temp->next = temp1->next;
    free(temp1);
    size--;
  }
  rear->next_addr = -1;
  return reverse_list;
}

void Print(ptrNode list){
  while(list->next->next){
    printf("%05d %d %05d\n",list->next->address,list->next->data,list->next->next_addr);
    list = list->next;
  }
  printf("%05d %d %d\n",list->next->address,list->next->data,list->next->next_addr);
}
