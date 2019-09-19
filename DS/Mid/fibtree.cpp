#include<iostream>
using namespace std;

struct ftree
{
	ftree *lchild;
	int data;
	ftree *rchild;
};

void getfib(int key,int &a,int &b)
{
	a=1;b=0;
	while((a+b)!=key&&a<=key)
	{
		int temp=a;
		a=a+b;
		b=temp;
	}
}

void create (ftree* &T,int key)
{
	if(T==NULL)
	{
		T=new(ftree);
		T->lchild=NULL;
		T->rchild=NULL;
		T->data=key;
	}
	int a,b;
	if(key!=1)
	{
	    getfib(key,a,b);
		create(T->lchild,a);
		create(T->rchild,b);
	}
}

void display(ftree *T)
{
	if(T!=NULL)
	{
		cout<<T->data<<" ";
		display(T->lchild);
		display(T->rchild);
	}
}

int main()
{
	int a;
	ftree *T=NULL;
	cout<<"Enter order of fib series: ";
	cin>>a;
	create(T,a);
	display(T);
	return 0;
}
