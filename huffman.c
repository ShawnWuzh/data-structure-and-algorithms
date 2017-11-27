// written by Zongheng WU for DS
#include <stdio.h>
#include <stdlib.h>
#define MAXNUMBER 64
#define MAXFREQUENCY 1001
#include <string.h>

typedef struct _charfre{
  char c;
  int frequency;
}CharFre;

typedef struct _TreeNode{
  struct _TreeNode* left;
  struct _TreeNode* right;
  int value;
}TreeNode;
typedef TreeNode* Tree;
typedef TreeNode* pTreeNode;

// use linked list to store the tree
typedef struct _LinkNode{
  pTreeNode tree;
  struct _LinkNode* next;
}LinkNode;
typedef LinkNode* pLinknode;
typedef struct _List{
  pLinknode head;
  pLinknode tail;
}List;

int ComputeWpl(pTreeNode pnode);
void PreTraversal(pTreeNode pNode,int length,int* pWPL);
pTreeNode BuildHuffman(List* pList);
void insert_to_linked_list(List* pList,int value);
pTreeNode NewTreeNode(int value);
pTreeNode FindMin(List* pList);
void Delete(List* pList,int value);
void UnionTwoTrees(pTreeNode tree1,pTreeNode tree2,List* pList);
int SatisfyWpl(int N,char *str[],CharFre CF[]);
int cmpfunc(const void* p1,const void* p2);
int CheckPrefix(char *str[],int N);
void Free(char* str[],int N);

int main(){
  int N;
  scanf("%d\n",&N);
  char c;
  int fre;
  int first = 1;
  // get the character and frequency
  CharFre CF[MAXNUMBER];
  for(int i= 0;i<N;i++){
    if(first){
      scanf("%c %d",&c,&fre);
      first = 0;
    }
    else{
      scanf(" %c %d",&c,&fre);
    }
    CF[i].c = c;
    CF[i].frequency = fre;
  }
  // store the each tree in a linked list
  List list;
  list.head = NULL;
  list.tail = NULL;
  for(int i= 0;i<N;i++){
    insert_to_linked_list(&list,CF[i].frequency);
  }
  pTreeNode huffman = BuildHuffman(&list);
  int WPL;
  WPL = ComputeWpl(huffman);
  int students = 0;
  scanf("%d",&students);
  char *str[MAXNUMBER];
  for(int i= 0;i<students;i++){
    int cur_wpl = SatisfyWpl(N,str,CF);
    if(cur_wpl != WPL){
      printf("No\n");
    }
    else{
      qsort(str,N,sizeof(char*),cmpfunc);
      if(CheckPrefix(str,N)){
        printf("Yes\n");
      }
      else{
        printf("No\n");
      }
    }
    Free(str,N);
  }
  return 0;
}
int ComputeWpl(pTreeNode huffman){
  int length = -1;
  int WPL = 0;
  PreTraversal(huffman,length,&WPL);
  return WPL;
}

void PreTraversal(pTreeNode pNode,int length,int* pWPL){
  length++;
  int WPL = *pWPL;
  if(pNode->left == NULL && pNode->right == NULL){
    WPL += length * pNode->value;
    *pWPL = WPL;
  }
  else{
    PreTraversal(pNode->left,length,pWPL);
    PreTraversal(pNode->right,length,pWPL);
  }
}

pTreeNode BuildHuffman(List* pList){
  pTreeNode tree1,tree2,huffman;
  while(pList->head){
    tree1 = FindMin(pList);
    Delete(pList,tree1->value);
    tree2 = FindMin(pList);
    Delete(pList,tree2->value);
    if(pList->head){
      UnionTwoTrees(tree1,tree2,pList);
    }
  }
  huffman = (pTreeNode)malloc(sizeof(TreeNode));
  huffman->value = tree1->value + tree2->value;
  huffman->left = tree1;
  huffman->right = tree2;
  return huffman;
}

void insert_to_linked_list(List* pList,int value){
  pLinknode p = (pLinknode)malloc(sizeof(pLinknode));
  p->tree = NewTreeNode(value);
  if(pList->head == NULL){
    pList->head = p;
    pList->tail = p;
  }
  else{
    pList->tail->next = p;
    pList->tail = p;
  }
}

pTreeNode NewTreeNode(int value){
  pTreeNode pTree = (pTreeNode)malloc(sizeof(TreeNode));
  pTree->value = value;
  pTree->left = NULL;
  pTree->right = NULL;
  return pTree;
}

pTreeNode FindMin(List* pList){
  pLinknode p = pList->head;
  int min_value = p->tree->value;
  pLinknode pmin = p;
  while(p->next){
    if(p->next->tree->value < min_value){
      min_value = p->next->tree->value;
      pmin = p->next;
    }
    p = p->next;
  }
  return pmin->tree;
}

void Delete(List* pList,int value){
  pLinknode p = pList->head;
  if(p->tree->value == value){
    pList->head = p->next;
  }
  else{
    while(p->next->tree->value != value){
      p = p->next;
    }
    if(p->next->next == NULL){
      pList->tail = p;
    }
    p->next = p->next->next;
  }
}

void UnionTwoTrees(pTreeNode tree1,pTreeNode tree2,List* pList){
  pTreeNode pTree = (pTreeNode)malloc(sizeof(TreeNode));
  pTree->value = tree1->value + tree2->value;
  pTree->left = tree1;
  pTree->right = tree2;
  pLinknode pLink = (pLinknode)malloc(sizeof(LinkNode));
  pLink->tree = pTree;
  pLink->next = NULL;
  pList->tail->next = pLink;
  pList->tail = pLink;
}

int SatisfyWpl(int N,char *str[],CharFre CF[]){
  int cur_wpl = 0;
  char c;
  for(int i=0;i<N;i++){
    str[i] = (char*)malloc(MAXNUMBER * sizeof(char));
    scanf("\n%c %s",&c,str[i]);
    for(int j=0;j<N;j++){
      if(CF[j].c == c){
        cur_wpl += CF[j].frequency * strlen(str[i]);
        break;
      }
    }
  }
  return cur_wpl;
}

int cmpfunc(const void* p1,const void* p2){
  return strlen(*((char**)p1))-strlen(*((char**)p2));
}

int CheckPrefix(char *str[],int N){
  int check_value = 1;
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++){
      if(strncmp(str[i],str[j],strlen(str[i])) == 0){
        check_value = 0;
        break;
      }
    }
    if(!check_value){
      break;
    }
  }
  return check_value;
}

void Free(char* str[],int N){
  for(int i= 0;i<N;i++){
    free(str[i]);
  }
}
