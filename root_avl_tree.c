// written by Zongheng WU for DS
#include <stdio.h>
#include <stdlib.h>


typedef struct _node{
  int data;
  struct _node* left;
  struct _node* right;
}TreeNode;
typedef TreeNode* pTreeNode;

pTreeNode NewNode(int data);
int max(int a,int b);
int Height(pTreeNode root);
pTreeNode left_rotate(pTreeNode root);
pTreeNode right_rotate(pTreeNode root);
pTreeNode AVL_insert(pTreeNode root,int data);

int main(){
  int N,data;    // the N is the number of keys to be inserted
  scanf("%d",&N);
  scanf("%d",&data);
  pTreeNode root = NewNode(data);
  for(int i=1;i<N;i++){
    scanf("%d",&data);
    root = AVL_insert(root,data);
  }
  printf("%d",root->data);
  return 0;
}

pTreeNode NewNode(int data){
  pTreeNode pnode = (pTreeNode)malloc(sizeof(TreeNode));
  pnode->data = data;
  pnode->left = NULL;
  pnode->right = NULL;
  return pnode;
}

int max(int a,int b){
  return (a>b)?a:b;
}

// compute the height of a subtree
int Height(pTreeNode root){
  if(!root){
    return -1;
  }
  else{
    return max(Height(root->left),Height(root->right)) + 1;
  }
}

pTreeNode right_rotate(pTreeNode root){
  pTreeNode new_root = root->left;
  root->left = new_root->right;
  new_root->right = root;
  return new_root;
}

pTreeNode left_rotate(pTreeNode root){
  pTreeNode new_root = root->right;
  root->right = new_root->left;
  new_root->left = root;
  return new_root;
}

pTreeNode AVL_insert(pTreeNode root,int data){
  // for a regular insert for a binary search tree
  if(!root){
    root = NewNode(data);
  }
  else{
    if(data > root->data){
      root->right = AVL_insert(root->right,data);
    }
    else{
      root->left = AVL_insert(root->left,data);
    }
  }
  // check the AVL property
  int ba_factor = Height(root->left) - Height(root->right);
  if(ba_factor > 1){
    int left_child_bf = Height(root->left->left) - Height(root->left->right);
    if(left_child_bf > 0){
      root = right_rotate(root);
    }
    else if(left_child_bf < 0){
      root->left = left_rotate(root->left);
      root = right_rotate(root);
    }
  }
  else if(ba_factor < -1){
    int right_child_bf = Height(root->right->left) - Height(root->right->right);
    if(right_child_bf < 0){
      root = left_rotate(root);
    }
    else if(right_child_bf > 0){
      root->right = right_rotate(root->right);
      root = left_rotate(root);
    }
  }
  return root;
}
