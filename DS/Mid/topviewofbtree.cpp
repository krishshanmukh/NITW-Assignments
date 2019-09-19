#include<iostream>
using namespace std;

struct bstnode
{
	bstnode *lchild;
	char data;
	bstnode *rchild;
	int x;
};

int c;

void insert(bstnode* &T,char ch,int x,int &max,int &min)
{
	if(T==NULL)
	{
		if(max<x)
		max=x;
		if(x<min)
		min=x;
		T=new(bstnode);
		T->data=ch;
		T->lchild=NULL;
		T->rchild=NULL;
		T->x=x;
	}
	cout<<"Enter left child of  "<<T->data<<" :";
	cin>>ch;
	if(ch!='0')
	insert(T->lchild,ch,x-1,max,min);
	cout<<"Enter right child of "<<T->data<<" :";
	cin>>ch;
	if(ch!='0')
	insert(T->rchild,ch,x+1,max,min);
}

void display (bstnode *T,int x)
{
	if(T!=NULL)
	{
	    if(T->x==x)
	    {
	        cout<<T->data<<" ";
	        c=1;
	    }
	    if(c!=1)
	    {
		    display(T->lchild,x);
	    }
	    if(c!=1)
	    {
	    	display(T->rchild,x);
	    }
	}
}

int main()
{
	char d;
	bstnode *T;
	T=NULL;
	T=new(bstnode);
	cout<<"Enter root node: ";
	cin>>T->data;
	T->x=0;
	T->lchild=NULL;
	T->rchild=NULL;
	int max,min;
	max=0;min=0;
	insert(T,T->data,0,max,min);
	cout<<T->data<<" ";
    for(int i=-1,j=1;i>=min||j<=max;i--,j++)
    {
    	c=0;
    	if(i>=min)
    	{
	        display(T->lchild,i);
    	    if(c==0)
        	display(T->rchild,i);
        	c=0;
        }
    	if(j<=max)
    	{
	        display(T->rchild,j);
    	    if(c==0)
        	display(T->rchild,j);
    	}
    }
    return 0;
}
