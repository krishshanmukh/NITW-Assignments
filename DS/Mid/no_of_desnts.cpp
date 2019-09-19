#include<iostream>
using namespace std;

struct btree
{
	btree *lchild;
	int data;
	btree *rchild;
	int no;
};

int des(btree *T)
{
    if(T->lchild!=NULL&&T->rchild!=NULL)
	return (des(T->lchild)+des(T->rchild)+2);	
	else if(T->lchild!=NULL&&T->rchild==NULL)
	return (des(T->lchild)+1);
	else if(T->lchild==NULL&&T->rchild!=NULL)
	return (des(T->rchild)+1);
	else
	return 0;
}

void insert(btree* &T,int x)
{
	if(T==NULL)
	{
		T=new(btree);
		T->data=x;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	cout<<"Enter left child of  "<<T->data<<" :";
	cin>>x;
	if(x!=-1)
	insert(T->lchild,x);
	cout<<"Enter right child of "<<T->data<<" :";
	cin>>x;
	if(x!=-1)
	insert(T->rchild,x);
	T->no=des(T);
}

void display(btree *T)
{
	if(T!=NULL)
	{ 
	    cout<<T->data<<" - "<<T->no<<"\t";
	    display(T->lchild);
	    display(T->rchild);
	}
}

int main()
{
	cout<<"Enter root node: ";
	int x;
	cin>>x;
	btree *T=NULL;
	insert(T,x);
	display(T);
	return 0;
}
