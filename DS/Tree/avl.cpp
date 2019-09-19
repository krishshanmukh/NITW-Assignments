#include<iostream>
using namespace std;

struct btree
{
	btree *lchild;
	int data;
	btree *rchild;
};

int a,b;

int height(btree *T)
{
    if(T==NULL)
	return -1;
	else
	{
		a=height(T->lchild);
		b=height(T->rchild);
		if(a>b)
		return a+1;
		else
		return b+1;
	}	
}

int compare(btree *T,btree *M)
{
	return (height(T)-height(M));
}

void rotateright(btree* &T,btree *M)
{
	T->lchild=M->rchild;
	M->rchild=T;
	T=M;
}

void rotateleft(btree* &T,btree *M)
{
	T->rchild=M->lchild;
	M->lchild=T;
	T=M;
}

void doublerotateright(btree* &T)
{
	rotateleft(T->lchild,T->lchild->rchild);
	rotateright(T,T->lchild);
}

void doublerotateleft(btree* &T)
{
	rotateright(T->rchild,T->rchild->lchild);
	rotateleft(T,T->rchild);
}

void create(btree* &T,int k)
{
	btree *M;
	if(T==NULL)
	{
		T=new(btree);
		T->lchild=NULL;
		T->rchild=NULL;
		T->data=k;
	}
	else
	{
	    if(k<T->data)
	    {
		    create(T->lchild,k);
		    int h=compare(T->lchild,T->rchild);
    		if(h==2)
	    	{
		    	M=T->lchild;
		        if(k<T->lchild->data)
    		    rotateright(T,M);
	    	    else
		        doublerotateright(T);
		    }
    	}
	    else
	    {
	        create(T->rchild,k);
    		int h=compare(T->rchild,T->lchild);
	    	if(h==2)
		    {
    			M=T->rchild;
	    	    if(k>T->rchild->data)
		        rotateleft(T,M);
		        else
		        doublerotateleft(T);
    		}	
        }
    }
}

void display(btree *T)
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
	int d;
	btree *T;
	T=NULL;
	cout<<"Enter elements (-1 to stop) :\n";
	cin>>d;
	while(d!=-1)
    {
    	create(T,d); 
    	cin>>d;
    }
    display(T);
    return 0;
}
