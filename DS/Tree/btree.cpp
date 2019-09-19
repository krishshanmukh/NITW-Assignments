#include<iostream>
using namespace std;

int d;

struct lnode
{
	int data;
	lnode *next;
	lnode();
};

lnode::lnode()
{
	next=NULL;
}

struct cnode;

struct btree
{
	int count;
	btree *parent;
	lnode *key;
	cnode *child;
	btree();
};

btree::btree()
{
	parent=NULL;
	key=NULL;
	child=NULL;
	count=0;
}

struct cnode
{
	btree *child;
	cnode *next;
	cnode();
};

cnode::cnode()
{
	next=NULL;
}

void addbefore(lnode *A,int x,int y)
{
	lnode *T;
	while(A->next->data!=y&&A->next!=NULL)
	A=A->next;
	T=new(lnode);
	T->data=x;
	T->next=A->next;
	A->next=T;
}
void addend(lnode *A,int x)
{
	while(A->next!=NULL)
	A=A->next;
	A->next=new(lnode);
	A->next->data=x;
	A->next->next=NULL;
}
void addbegin(lnode* &A,int x)
{
	lnode *T=new(lnode);
	T->data=x;
	T->next=A;
	A=T;
}

void sort(btree* &L,int count,int c)
{
	btree *M=L;
	for(int i=0;i<M->count;i++)
	{
		
		if(M->key->data>c)
		{
			if(i==0)
			addbegin(L->key,c);
			else if(i<count)
			addbefore(L->key,c,L->key->data);
			else;
			break;
		}
		if(M->key->next!=NULL)
		M->key=M->key->next;
	}
	if(c>M->key->data)
	{
		addend(L->key,c);
	}
}

btree* split(btree *T)
{
	btree *M=new(btree);
	for(int i=0;i<T->count/2;i++)
	T->key=T->key->next;
	T->count=T->count/2;
	M=new(btree);
	M->count=T->count;
	M->key=T->key->next;
	T->key->next=NULL;
	return M;
}

btree* parent(int key)
{
	btree *T;
	T=new(btree);
	addbegin(T->key,key);
	T->count++;
	return T;
}

void createbtree(btree* &T,int key)
{
	btree *M=T;
	int i;
	if(T->count!=0)
	{
	    for(i=0;i<T->count;i++)
	    {
		    if(key<T->key->data)
    		{
	    		if(T->child!=NULL)
	    		{
		    	    createbtree(T->child->child,key);
		    	}
		    	break;
		    }
		    if(T->key->next!=NULL)
			T->key=T->key->next;
			if(T->child!=NULL)
			T->child=T->child->next;
		}
		if(i==T->count&&T->child!=NULL)
		{
	    	createbtree(T->child->child,key);
		}
		else if(T->count<2*d&&T->child==NULL)
		{
			sort(M,M->count,key);
			T=M;
			T->count++;
		}
		else
		{
			btree *L=split(T);
			btree *K=parent(T->count/2);
			K->child=new(cnode);
			K->child->child=T;
			T->parent=K;
			K->child->next=new(cnode);
			K->child->next->child=L;
			L->parent=K;
			T=K;
		}
	}
	else
	{
		addbegin(T->key,key);
		T->count++;
	}
}

void display(btree *T)
{
    if(T!=NULL)
	{
		for(int i=0;i<T->count;i++)
		{
			if(T->child!=NULL)
			display(T->child->child);
			cout<<T->key->data<<" ";
			if(T->child!=NULL)
			T->child=T->child->next;
			if(T->key!=NULL)
			T->key=T->key->next;
		}
		if(T->child!=NULL)
		display(T->child->child);
	}	
}

int main()
{
	int  c;
	cout<<"Enter value of d: ";
    cin>>d;
	btree *T=new(btree);
	cout<<"Enter nos: ";
	cin>>c;
	while(c!=-1)
	{
		createbtree(T,c);
		cin>>c;
	}
	display(T);
	return 0;
}
