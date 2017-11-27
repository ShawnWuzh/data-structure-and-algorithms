
#include<iostream>
using namespace std;
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    char elem;
};
TreeNode*findTree(char*in,char*pre,int length)
{
    if(length==0)
    return NULL;
    TreeNode* node=new TreeNode;
    node->elem=*pre;
    int i=0;
    for(;i<length;i++)
    {
        if(in[i]==*pre)
        break;
    }
    node->left=findTree(in,pre+1,i);
    node->right=findTree(in+i+1,pre+i+1,length-i-1);
    return node;
}
int length(TreeNode *node)
{
    if(node==NULL)
    return 0;
    int l=length(node->left);
    int r=length(node->right);
    return l>r?l+1:r+1;
}
int main()
{
    char in[10000],pre[10000];
    int N;
    cin>>N;
    char c;
    for(int i=0;i<N;i++)
    {
        cin>>c;
        pre[i]=c;
    }
    for(int i=0;i<N;i++)
    {
        cin>>c;
        in[i]=c;
    }
    TreeNode* Node=new TreeNode;
    Node=findTree(in,pre,N);
    cout<<length(Node)<<endl;
}
