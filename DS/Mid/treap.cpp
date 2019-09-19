#include<iostream>
using namespace std;

struct btree
{
	btree *lchild;
	int data;
	char cdata;
	btree *rchild;
};

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

void create(btree* &T,int k,char ch)
{
	btree *M;
	if(T==NULL)
	{
		T=new(btree);
		T->lchild=NULL;
		T->rchild=NULL;
		T->data=k;
		T->cdata=ch;
	}
	else
	{
	    if(ch<T->cdata)
	    {
		    create(T->lchild,k,ch);
		    if(T->lchild->data<T->data)
		    rotateright(T,T->lchild);
    	}
	    else
	    {
	        create(T->rchild,k,ch);
			if(T->rchild->data<T->data)
		    rotateleft(T,T->rchild);	
        }
    }
}

void display(btree *T)
{
	if(T!=NULL)
	{
		display(T->lchild);
		cout<<T->data<<" "<<T->cdata<<"  ";
		display(T->rchild);
	}
}

int main()
{
	int d;
	char ch;
	btree *T;
	T=NULL;
	cout<<"Enter elements (-1 to stop) :\n";
	cin>>d;
	while(d!=-1)
    {
    	cin>>ch;
    	create(T,d,ch); 
    	cin>>d;
    }
    display(T);
    return 0;
}
