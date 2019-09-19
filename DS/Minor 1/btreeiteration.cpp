#include<iostream>
using namespace std;

struct btree
{
	btree *lchild;
	int data;
	btree *rchild;
};

class stack
{
	int top;
	btree *elts[30];
	int tag[30];
    public :
		void push(btree *T);
		btree* pop();
		void display();
		int isempty();
		stack()
		{
			top=-1;
		}
}s;

btree* stack :: pop()
{
	if(top>=0)
	return elts[top--];
	else
	return NULL;
}

void stack :: push(btree *T)
{
	if(top<30)
	elts[++top]=T;
}

int stack:: isempty()
{
	if(top==-1)
	return 1;
	else
	return 0;
}

int data;

void input(btree *T)
{
	while(!s.isempty())
	{
		T=s.pop();
		cout<<"Enter left child of "<<T->data<<" ";
		cin>>data;
		if(data!=-1)
		{
			T->lchild=new(btree);
			T->lchild->data=data;
			T->lchild->lchild=NULL;
			T->lchild->rchild=NULL;
			s.push(T->lchild);
		}
		cout<<"Enter right child of "<<T->data<<" ";
		cin>>data;
		if(data!=-1)
		{
			T->rchild=new(btree);
			T->rchild->data=data;
			T->rchild->lchild=NULL;
			T->rchild->rchild=NULL;
			s.push(T->rchild);
		}
	}
}

void display(btree *T)
{
	if(T!=NULL)
	{
		
	    if(T->lchild!=NULL)
	    display(T->lchild);
	    cout<<T->data<<" ";
	    if(T->rchild!=NULL)
	    display(T->rchild);
    }
}

int main()
{
	btree *B,*A;
	cout<<"Enter root node: ";
    cin>>data;
    A=new(btree);
    s.push(A);
    A->data=data;
    A->rchild=NULL;
    A->lchild=NULL;
    input(A);
    display(A);
    return 0;
}
