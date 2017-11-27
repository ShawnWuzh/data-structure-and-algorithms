// written by Zongheng Wu for DS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int data;
  struct _node *left,*right;
  int tag;
}TreeNode;
typedef TreeNode* pTreeNode;

pTreeNode NewTree(int N);
pTreeNode NewNode(int data);
pTreeNode insert(pTreeNode pNode,int data);
void check(pTreeNode cur_root,int N);
int find(pTreeNode cur_root,int data);
void set_tag(pTreeNode cur_node);
void Free(pTreeNode cur_node);

int main(){
  int N,L;
  scanf("%d",&N);
  while(N){
    pTreeNode Tree = NULL;
    scanf("%d",&L);
    Tree = NewTree(N);     // build a new tree
    for(int i=0;i<L;i++){
      set_tag(Tree);       // set the tag of the tree
      check(Tree,N);       // check if the series is the same as the original tree
    }
    Free(Tree);            // free the original tree for next potential tree
    scanf("%d",&N);
  }
}

pTreeNode NewTree(int N){
  int R;
  scanf("%d",&R);
  pTreeNode Root = NewNode(R);
  for(int i = 1;i<N;i++){      // insert the value read from the input one by one
    scanf("%d",&R);
    Root = insert(Root,R);
  }
  return Root;
}

pTreeNode NewNode(int data){    // new a node for a specified value
  pTreeNode pNode = (pTreeNode)malloc(sizeof(TreeNode));
  pNode->data = data;
  pNode->left = NULL;
  pNode->right = NULL;
  pNode->tag = 1;
  return pNode;
}

pTreeNode insert(pTreeNode pnode,int data){      // insert the newnode to the tree
  if(!pnode){                                    // this function is very important!!
    pnode = NewNode(data);
  }
  else{
    if(data > pnode->data){
      pnode->right = insert(pnode->right,data);
    }
    else if(data < pnode->data){
      pnode->left = insert(pnode->left,data);
    }
  }
  return pnode;
}


void check(pTreeNode cur_root,int N){   // to check the series satisfy the tree
  int data;
  int same_flag = 1;
  for(int j = 0;j<N;j++){
    scanf("%d",&data);
    if(same_flag){
      if(!find(cur_root,data)){    // to find the current value
        same_flag = 0;
      }
    }
  }
  if(!same_flag){
    printf("No\n");
  }
  else{
    printf("Yes\n");
  }
}

int find(pTreeNode cur_root,int data){
  if(cur_root->tag == 0){
    if(cur_root->data > data){
      return find(cur_root->left,data);
    }
    else{
      return find(cur_root->right,data);
    }
  }
  else{
    if(cur_root->data == data){
      cur_root->tag = 0;
      return 1;
    }
    else{
      return 0;
    }
  }
}

void set_tag(pTreeNode cur_node){
  if(cur_node){
    cur_node->tag = 1;
    set_tag(cur_node->left);
    set_tag(cur_node->right);
  }
}

void Free(pTreeNode cur_node){
  if(cur_node->left){
    Free(cur_node->left);
  }
  if(cur_node->right){
    Free(cur_node->right);
  }
  free(cur_node);
}
