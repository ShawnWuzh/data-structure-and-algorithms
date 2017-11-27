#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int coe;
  int expo;
  struct _node* next;
}Node;
typedef struct _node* poly;

poly Read(int terms);
void attach(int coe,int expo,poly* pRear);
poly Add(poly p1,poly p2);
poly Multi(poly p1,poly p2);
void Print(poly p);

int main(){
  poly p1,p2,p3,p4;
  int terms1,terms2;
  scanf("%d",&terms1);
  p1 = Read(terms1);   //读入多项式1
  scanf("%d",&terms2);    //读入多项式2
  p2 = Read(terms2);
  p3 = Add(p1,p2);
  p4 = Multi(p1,p2);
  Print(p4);
  Print(p3);
  return 0;
}

poly Read(int terms){
  int coe,expo;
  poly p = (poly)malloc(sizeof(Node)); //新建一个头结点
  p->next = NULL;
  poly rear = p;  //用一个尾结点表示当前链表中的最后一项
  for(int i = 0;i < terms;i++){
    scanf("%d %d",&coe,&expo);
    attach(coe,expo,&rear);
  }
  poly t = p;
  p = p->next;
  free(t);
  return p;
}

void attach(int coe,int expo,poly* pRear){
  poly temp = (poly)malloc(sizeof(Node));
  temp->coe = coe;
  temp->expo = expo;
  temp->next = NULL;
  (*pRear)->next = temp;
  (*pRear) = temp;
}

poly Add(poly p1,poly p2){
  poly temp1 = p1;
  poly temp2 = p2;
  poly p3 = (poly)malloc(sizeof(Node)); //新建一个头结点
  p3->next = NULL;
  poly rear = p3;       //用一个尾指针指向当前的最后一个
  poly temp;
  if(!temp1 && !temp2){
    temp = p3;
    p3 = p3->next;
    free(temp);
    return p3;
  }
  while(temp1 && temp2){
    if(temp1->expo > temp2->expo){
      attach(temp1->coe,temp1->expo,&rear);
      temp1 = temp1->next;
    }
    else if(temp1->expo < temp2->expo){
      attach(temp2->coe,temp2->expo,&rear);
      temp2 = temp2->next;
    }
    else{
      if(temp1->coe + temp2->coe){
        attach(temp1->coe+temp2->coe,temp1->expo,&rear);
        temp1 = temp1->next;
        temp2 = temp2->next;
      }
      else{
        temp1 = temp1->next;
        temp2 = temp2->next;
      }
    }
  }
  if(!temp1){
    rear->next = temp2;
    rear = temp2;
  }
  else if(!temp2){
    rear->next = temp1;
    rear = temp1;
  }
  temp = p3;
  p3 = p3->next;
  free(temp);
  return p3;
}

poly Multi(poly p1,poly p2){
  poly p4,temp1,temp2,temp4,rear;
  if(!p1 || !p2){
    p4 = NULL;
    return p4;
  }
  else{
    temp1 = p1;
    temp2 = p2;
    p4 = (poly)malloc(sizeof(Node)); // the head of the product
    p4->next = NULL;
    rear = p4;
    // genrrate a new linked list
    while(temp2){
      attach(temp1->coe*temp2->coe,temp1->expo+temp2->expo,&rear);
      temp2 = temp2->next;
    }

    temp1 = temp1->next;
    while(temp1){
      temp2 = p2;
      while(temp2){
        poly temp3 = p4;
        // scann the generated list to search the location to insert the
        // new node
        while(temp3->next && temp2->expo + temp1->expo < temp3->next->expo){
          temp3 = temp3->next;
        }
        // find the location,inseert the new node
        int coe = temp2->coe * temp1->coe;
        // the new node equals the next
        if(temp3->next && temp2->expo + temp1->expo == temp3->next->expo){
          if(temp3->next->coe + coe){
            temp3->next->coe += coe;
          }
          else{
            temp4 = temp3->next;
            temp3->next = temp4->next;
            free(temp4);
          }
        }
        else{
          poly new = (poly)malloc(sizeof(Node));
          new->coe = coe;
          new->expo = temp2->expo + temp1->expo;
          new->next = NULL;
        // the new node is greater than the next
          if(temp3->next){
            temp4 = temp3->next;
            temp3->next = new;
            new->next = temp4;
          }
          else{
            temp3->next = new;
            new->next = NULL;
          }
      }
        temp2 = temp2->next;
    }
    temp1 = temp1->next;
  }
  temp4 = p4;
  p4 = p4->next;
  free(temp4);
  return p4;
}
}

void Print(poly p){
  int flag = 0;
  if(!p){
    printf("0 0");
  }
  else{
    while(p){
      if(flag==0){
        printf("%d %d",p->coe,p->expo);
        flag = 1;
      }
      else{
        printf(" %d %d",p->coe,p->expo);
      }
      p = p->next;
    }
  }
  printf("\n");
}
