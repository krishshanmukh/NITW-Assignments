#include<iostream>
using namespace std;
struct btnode
{
	btnode *lchild,*rchild;
	char data;
};

int compare_pos(char x,char y,char inorder[] )
{
	int i1,i2;
	for(i1=0;inorder[i1]!=x;i1++) ;
	for(i2=0;inorder[i2]!=y;i2++) ;
	if(i1<i2) return 1; else return 2;
}
void insert(btnode *&t,char preorder,char inorder[])
{
	if(t==NULL)
 {
 	t= new btnode;
	t->lchild=NULL;
	t->data=preorder;
	t->rchild=NULL;
 }
 else
 {
 	int pos=compare_pos(preorder,t->data,inorder);
	if(pos==1)
    insert(t->lchild,preorder,inorder);
    else
    insert(t->rchild,preorder,inorder);
 }

}

void print(btnode *t,int k)
{
	if(t!=NULL)
	{
		if(k==1)
		{
			cout<<t->data<<" ";
		}
		else if(k!=0)
		{
			print(t->lchild,k-1);
			print(t->rchild,k-1);
		}
	}
}
int height(btnode *t,int k)
{
	int x1,x2;
	if(t!=NULL)
	{
		x1=height(t->lchild,++k);
		k--;
		x2=height(t->rchild,++k);
		k--;
		if(x1>x2) return x1; else return x2;
	}
	else return k;
}

int main()
{char preorder[50],inorder[50];
cout<<"Enter preorder data of binary tree :";cin.getline(preorder,50);
 cout<<"Enter inorder data of binary tree :";cin.getline(inorder,50);
 btnode *t=NULL;int i=0;
 for( i=0;preorder[i]!=NULL;i++)
 insert(t,preorder[i],inorder);
int h=height(t,0);
	for(i=1;i<=h;i++)
	{
		print(t,i); cout<<endl;
	}

}
