#include<iostream>
#include<cstring>
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
	btree *T,*M,*N,*O;
	T=new(btree);
	M=T;
	T->lchild=NULL;
	T->rchild=NULL;
	int k=strlen(B);
	int b=strlen(A);
	k=k-1;
	T->data=B[k--];
	s.push(T);
	int i,ctr;

		while(k>=0)
		{
			i=b-1;
			T=s.pop();
			ctr=0;
		    while(A[i]!=T->data)
		    {
			    if(A[i]==B[k])
			    {
			    	ctr=1;
			    	s.push(T);
					T->rchild=new(btree);
					T=T->rchild;
					T->lchild=NULL;
					T->rchild=NULL;
					T->data=A[i];
					s.push(T);
					break;
				}
				i--;
			}
			if(ctr==0)
			{
				l1: i=b-1;
				s.push(T);
				N=s.pop();
				T=s.pop();
				if(T==NULL)
				{
					ctr=1;
					N->lchild=new(btree);
					N=N->lchild;
					N->data=B[k];
					N->rchild=NULL;
					N->lchild=NULL;
					s.push(N);
				}
				else
				{
				while(A[i]!=N->data)
				i--;
				while(A[i]!=T->data)
				{
				    if(A[i]==B[k])
    			    {
	    		    	ctr=1;
		    			N->lchild=new(btree);
			    		N=N->lchild;
				    	N->lchild=NULL;
					    N->rchild=NULL;
    					N->data=A[i];
    					s.push(T);
	    				s.push(N);
		    			break;
			    	}	
			    	i--;
				}
				if(ctr==0)
				goto l1;
			    }
			}
			
			k--;
		}
	
	return M;
}

void display(btree *T)
{
	if(T!=NULL)
	{
		cout<<T->data;
	    if(T->lchild!=NULL)
	    display(T->lchild);
	    if(T->rchild!=NULL)
	    display(T->rchild);
    }
}

int main()
{
	char A[20],B[20];
	btree *T;
	cout<<"Enter inorder expression: ";
	cin>>A;
	cout<<"Enter post-order expression: ";
	cin>>B;
	T=btreecreate(A,B);
	cout<<"Pre-order: ";
	display(T);
	return 0;
}
