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
	{
	return NULL;
    }
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

btree* btreecreate(char A[],char B[])
{
	stack s;
	btree *T,*M,*N;
	T=new(btree);
	M=T;
	T->lchild=NULL;
	T->rchild=NULL;
	T->data=B[0];
	s.push(T);
	int i,j=1,ctr;

		while(B[j]!='\0')
		{
			i=0;
			T=s.pop();
			ctr=0;
		    while(A[i]!=T->data)
		    {
			    if(A[i]==B[j])
			    {
			    	ctr=1;
			    	s.push(T);
					T->lchild=new(btree);
					T=T->lchild;
					T->lchild=NULL;
					T->rchild=NULL;
					T->data=A[i];
					s.push(T);
					break;
				}
				i++;
			}
			if(ctr==0)
			{
				l1: i=0;
				s.push(T);
				N=s.pop();
				T=s.pop();
				if(T==NULL)
				while(A[i]!=N->data)
				i++;
				if(T==NULL)
				{
					ctr=1;
					N->rchild=new(btree);
					N=N->rchild;
					N->data=B[j];
					N->rchild=NULL;
					N->lchild=NULL;
					s.push(N);
				}
				else
				{
				while(A[i]!=N->data)
				i++;
				while(A[i]!=T->data)
				{
				    if(A[i]==B[j])
    			    {
	    		    	ctr=1;
		    			N->rchild=new(btree);
			    		N=N->rchild;
				    	N->lchild=NULL;
					    N->rchild=NULL;
    					N->data=A[i];
    					s.push(T);
	    				s.push(N);
		    			break;
			    	}	
			    	i++;
				}
				if(ctr==0)
				goto l1;
			    }
			}
			
			j++;
		}
	
	return M;
}

void display(btree *T)
{
	if(T!=NULL)
	{
	if(T->lchild!=NULL)
	display(T->lchild);
	if(T->rchild!=NULL)
	display(T->rchild);
		cout<<T->data<<" ";
    }
}

int main()
{
	char A[20],B[20];
	btree *T;
	cout<<"Enter inorder expression: ";
	cin>>A;
	cout<<"Enter preorder expression: ";
	cin>>B;
	T=btreecreate(A,B);
	display(T);
	return 0;
}
