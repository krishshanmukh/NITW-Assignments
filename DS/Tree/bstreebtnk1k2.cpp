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
void display(bstnode *T,int a,int b)
{
	if(T!=NULL)
	{
		if(T->lchild!=NULL)
	    display(T->lchild,a,b);
	    if(T->data>a&&T->data<b)
	    cout<<T->data<<" ";
	    if(T->rchild!=NULL)
	    display(T->rchild,a,b);
    }
}
int main()
{
	int d,k1,k2;
	bstnode *T;
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
    cout<<"Enter limits: ";
    cin>>k1>>k2;
    cout<<"Elts between "<<k1<<" and "<<k2<<" are: ";
    display(T,k1,k2);
    return 0;
}
