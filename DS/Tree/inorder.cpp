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


void input(btree* &T,char k)
{
	if(T==NULL)
	{
			T=new(btree);
	    	T->data=k;
	    	T->lchild=NULL;
	    	T->rchild=NULL;
	}
	cout<<"Enter left child of "<<k<<": ";
	char ch;
	cin>>ch;
	if(ch!='*')
	{
		    input(T->lchild,ch);
	}
	cout<<"Enter right child of "<<T->data<<": ";
	cin>>ch;
	if(ch!='*')
	{
		    input(T->rchild,ch);	
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
    btree *M=T;
	do
	{//l1:
		while(T!=NULL)
		{
			s.push(T);
			T=T->lchild;
		}
		T=s.pop();
		if(T!=NULL)
		{
			cout<<T->data<<" ";
			T=T->rchild;
			//goto l1;
		}
		else 
		T=T->rchild;
	}while(!s.isempty()||T!=NULL);
}

void preorder(btree *T)
{
	stack s;
	btree *M=T;
	do
	{
		//l1:
		while(T!=NULL)
		{
			s.push(T);
			cout<<T->data<<" ";
			T=T->lchild;
		}
		T=s.pop();
		if(T!=NULL)
	    {
		
			T=T->rchild;
			//goto l1;
		}
		else
		T=T->rchild;
	}while(!s.isempty()||T!=NULL);
}

void postorder(btree *T)
{
	stack s,s1;
    btree *M=T;
    s.push(T);
	do
	{
		T=s.pop();
		s1.push(T);
		if(T->lchild!=NULL)
		s.push(T->lchild);
		if(T->rchild!=NULL)
		s.push(T->rchild);
	}while(!s.isempty());
	while(!s1.isempty())
	cout<<s1.pop()->data<<" ";
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
    B=A;
    input(A,ch);
    cout<<"Inorder : ";
    inorder(A);
    cout<<"\nPre-order : ";
    preorder(B);
    cout<<"\nPost-order : ";
    postorder(A);
    return 0;
}
