#include<iostream>
using namespace std;

const int d=2;

struct btnode
{
	int count;
	int key[2*d+1];
	btnode *child[2*d+2];
	int x;
	btnode *parent;
	btnode();
};
btnode *A=NULL;

btnode :: btnode()
{
	count=0;
	for(int i=0;i<2*d+2;i++)
	child[i]=NULL;
	parent=NULL;
}

void sort(btnode* &T)
{
	int x=T->key[T->count-1],i;
	btnode *M=T->child[T->count];
	for(i=0;i<T->count-1;i++)
	{
		if(T->key[i]>T->key[T->count-1])
		{
			for(int j=T->count-1;j>i;j--)
			{
			    T->key[j]=T->key[j-1];
			    T->child[j+1]=T->child[j];
			}
			T->key[i]=x;
			T->child[i+1]=M;
			break;
		}
	}
}

btnode* split(btnode *M)
{
	btnode *T;
	T=new(btnode);
	for(int i=(M->count/2)+1;i<M->count;i++)
	{
	    T->key[T->count]=M->key[i];
	    T->child[T->count++]=M->child[i];
    }
    T->child[T->count]=M->child[M->count];
	return T;
}

btnode* parent(int key)
{
	btnode *T;
	T=new(btnode);
	T->key[T->count++]=key;
	return T;
}

btnode* nodesplitting (btnode* &T,int x)
{
	if(T->parent!=NULL)
	{
		sort(T);
		cout<<"Split node of: "<<T->key[0]<<endl;
		cout<<"Add to node of: "<<T->parent->key[0]<<endl;
		btnode *M=split(T);
		//cout<<T->parent->key[0]<<endl;
		T->parent->key[T->parent->count++]=T->key[T->count/2];
		T->parent->child[T->parent->count]=M;
		M->x=T->x;
		//cout<<M->key[0];
		T->count/=2;
		sort(T->parent);
		M->parent=T->parent;
		if(T->parent->count>2*d)
		{
			if(T->parent->parent==NULL)
			{
                btnode* K=nodesplitting(T->parent,T->x+1);
	    	    for(int i=0;i<=K->count;i++)
		        {
		        	K->child[i]->parent=K;
		        }
		    }
		    else
		    {
		        nodesplitting(T->parent,T->x+1);
		    }
	    }
	}
	else
	{
	    sort(T);
		btnode *M=split(T);
		btnode *K=parent(T->key[T->count/2]);
		T->count/=2;
		K->child[0]=T;
		T->parent=K;
		K->child[1]=M;
		M->x=x;
		M->parent=K;
		K->x=x+1;
		A=K;
		return M;
	}
}

void createbtree(btnode* &T,int key,int x)
{
	int i,c=0;
	for(i=0;i<T->count;i++)
	{
		if(key<T->key[i])
		{
			if(T->child[i]!=NULL)
			{
				cout<<"Going to last child"<<T->key[T->count-1]<<endl;
				T->child[i]->parent=T;
			    createbtree(T->child[i],key,x);
			    c=1;
			}
			break;
		}
	}
	if(i==T->count&&T->child[i]!=NULL)
	{
		cout<<"Going to last child"<<T->key[T->count-1]<<endl;
		T->child[i]->parent=T;
	    createbtree(T->child[i],key,x);
	}   
	else if(T->count<2*d&&T->child[0]==NULL)
	{
		T->x=x;
		T->key[T->count++]=key;
		if(T->count!=1)
		sort(T);
	}
    else if(T->count==2*d&&c==0)
    {
    	T->key[T->count++]=key;
    	nodesplitting(T,x);
    }
}

void display(btnode *T,int x)
{
    if(T!=NULL)
	{
		int i;
		for(i=0;i<T->count;i++)
		{
			display(T->child[i],x);
			if(T->x==x)
			cout<<T->key[i]<<" ";
		}
		display(T->child[i],x);
	}	
}

void display1(btnode *T)
{
    if(T!=NULL)
	{
		int i;
		for(i=0;i<T->count;i++)
		{
			display1(T->child[i]);
			cout<<T->key[i]<<" ";
		}
		display1(T->child[i]);
	}	
}

int main()
{
	int  c;
	btnode *T=new(btnode);
	cout<<"Enter nos: ";
	cin>>c;
	while(c!=-1)
	{
		createbtree(T,c,0);
		if(A!=NULL)
		T=A;
		cin>>c;
	}
	display1(T);
	cout<<"\nTree of order: "<<d<<endl;
	for(int i=T->x;i>=0;i--)
	{
	    display(T,i);
	    cout<<endl;
	}
	return 0;
}
