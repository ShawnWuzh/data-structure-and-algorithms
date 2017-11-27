//written by Zongheng Wu for DS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
void PreorderTraversal( BinTree BT ){
  if(BT){
    printf("%d ",BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
  }
}
void InorderTraversal( BinTree BT ){
  if(BT){
    InorderTraversal(BT->Left);
    printf("%d ",BT->Data);
    InorderTraversal(BT->Right);
  }
}
Position NewNode(ElementType X){
  Position pnode = (Position)malloc(sizeof(struct TNode));
  pnode->Data = X;
  pnode->Left = NULL;
  pnode->Right = NULL;
  return pnode;
}

BinTree Insert( BinTree BST, ElementType X ){
  if(!BST){
    BST = NewNode(X);
  }
  else{
    if(X <= BST->Data){
      BST->Left = Insert(BST->Left,X);
    }
    else{
      BST->Right = Insert(BST->Right,X);
    }
  }
  return BST;
}

Position Find( BinTree BST, ElementType X ){
  Position cur_node = BST;
  int is_found = 0;
  while(cur_node){
    if(X > cur_node->Data){
      cur_node = cur_node->Right;
    }
    else if(X < cur_node->Data){
      cur_node = cur_node->Left;
    }
    else{
      is_found = 1;
      break;
    }
  }
  if(!is_found){
    cur_node = NULL;
  }
  return cur_node;
}

BinTree Delete( BinTree BST, ElementType X ){
  if(!BST){
    printf("Not found\n");
  }
  else if(X > BST->Data){
    BST->Right = Delete(BST->Right,X);
  }
  else if(X < BST->Data){
    BST->Left = Delete(BST->Left,X);
  }
  else{
    if(BST->Left == NULL && BST->Right == NULL){        // the node is a leaf
      free(BST);
      BST = NULL;
    }
    else if(BST->Left == NULL && BST->Right != NULL){   // the node has a right subtree
      Position NewRoot = BST->Right;
      free(BST);
      BST = NewRoot;
    }
    else if(BST->Right == NULL && BST->Left != NULL){   // the node has a left subtree
      Position NewRoot = BST->Left;
      free(BST);
      BST = NewRoot;
    }
    else{     // the node has a left subtree and a right subtree
      Position temp = FindMin(BST->Right);
      BST->Data = temp->Data;
      BST->Right = Delete(BST->Right,BST->Data);
    }
  }
  return BST;
}

Position FindMin( BinTree BST ){
  Position cur_node = BST;
  if(cur_node){
    while(cur_node->Left){
      cur_node = cur_node->Left;
    }
  }
  return cur_node;
}

Position FindMax( BinTree BST ){
  Position cur_node = BST;
  if(cur_node){
    while(cur_node->Right){
      cur_node = cur_node->Right;
    }
  }
  return cur_node;
}
