#include<iostream>
using namespace std;
struct btree
{
	btree *lchild;
	char data;
	btree *rchild;
};

class stack
{
	int top;
	btree *elts[30];
	int size;
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
};

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


void input(btree *T,char k)
{
	btree *M;
	cout<<"Enter left child of "<<k<<": ";
	char ch;
	cin>>ch;
	M=T;
	if(ch!='*')
	{
	    	T->lchild=new(btree);
	    	M=M->lchild;
	    	M->data=ch;
	    	M->rchild=NULL;
	    	M->lchild=NULL;
		    input(M,ch);
	}
	cout<<"Enter right child of "<<k<<": ";
	cin>>ch;
	M=T;
	if(ch!='*')
	{
	    	M->rchild=new(btree);
	    	M=M->rchild;
	    	M->data=ch;
	    	M->lchild=NULL;
	    	M->rchild=NULL;
		    input(M,ch);	
	}
}
int stack:: isempty()
{
	if(top==-1)
	return 1;
	else
	return 0;
}
void inorder(btree *T)
{
	stack s;
	int c;
	btree *M=T;
	do
	{
		l1:
		while(T!=NULL)
		{
			s.push(T);
			cout<<T->data<<" ";
			T=T->lchild;
		}
		T=s.pop();
		    if(T!=NULL)
		    {
		    	if(M==T)
		    	{
		    	T=T->rchild;
		    	goto l1;
		    }
		    else
		    T=T->rchild;
		    }
	}while(!s.isempty());
}

int main()
{
	btree *B,*A;
	cout<<"Enter root node: ";
    char ch;
    int c=1;
    cin>>ch;
    A=new(btree);
    A->data=ch;
    A->rchild=NULL;
    A->lchild=NULL;
    input(A,ch);
    inorder(A);
    return 0;
}
