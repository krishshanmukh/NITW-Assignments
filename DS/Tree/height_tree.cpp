#include<iostream>
using namespace std;
struct bstnode
{
	bstnode *lchild;
	int data;
	bstnode *rchild;
};
void insert(bstnode* T,int x)
{
	if(T!=NULL)
	{
		if(x<T->data)
		{
			if(T->lchild!=NULL)
			insert(T->lchild,x);
			else
			{
			    T->lchild=new(bstnode);
			    T=T->lchild;
			    T->data=x;
			    T->lchild=NULL;
			    T->rchild=NULL;
		    }
		}
		else
		{
			if(T->rchild!=NULL)
			insert(T->rchild,x);
			else
			{
			    T->rchild=new(bstnode);
			    T=T->rchild;
			    T->data=x;
			    T->rchild=NULL;
			    T->lchild=NULL;
			}
		}
	}
}
int k=0;
int display(bstnode *T,int l)
{
	if(k<l)
	k=l;
	int c=l;
	if(T!=NULL)
	{
		if(T->lchild!=NULL)
		{
	    display(T->lchild,c+1);
	    }
	    if(T->rchild!=NULL)
	    {
	    display(T->rchild,c+1);
	    }
    }
    return k;
}

int main()
{
	int d;
	bstnode *T,*M,*I;
	T=NULL;
	int c=0;
    cout<<"Enter root node : ";
	cin>>d;
	T=new(bstnode);
	T->data=d;
	T->lchild=NULL;
	T->rchild=NULL;
	cout<<"Enter elements (-1 to stop) :\n";
	cin>>d;
	while(d!=-1)
    {
    	insert(T,d);
    	cin>>d;
    }
    cout<<display(T,0);
}
