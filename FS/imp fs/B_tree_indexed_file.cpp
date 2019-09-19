#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

const int d=1;

class student
{
	public:
		int rollno;
		char name[11];
		char cgpa[5];
};
class buffer
{
	public:
	char buff[30];
    void pack(char a[]);
    void store(ofstream &out);
    void pack1 (char a[]);
};
void buffer :: pack1 (char a[])
{
	strcpy(buff,a);
	strcat(buff,"$");
}
void buffer :: pack (char a[])
{
	strcat(buff,a);
	strcat(buff,"$");
}
void buffer :: store (ofstream &out)
{
	int l;
    l = strlen(buff);
    for(int i=0;i<l;i++)
    out<<buff[i];
    out<<endl;
}

struct btnode
{
	int count;
	int key[2*d+1];
	int index[2*d+1];
	int ptr[2*d+2];
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
	{
	    child[i]=NULL;
	    ptr[i]=-1;
	}
	parent=NULL;
}

void sort(btnode* &T)
{
	int x=T->key[T->count-1],y=T->index[T->count-1],i;
	btnode *M=T->child[T->count];
	for(i=0;i<T->count-1;i++)
	{
		if(T->key[i]>T->key[T->count-1])
		{
			for(int j=T->count-1;j>i;j--)
			{
			    T->key[j]=T->key[j-1];
			    T->index[j]=T->index[j+1];
			    T->child[j+1]=T->child[j];
			}
			T->key[i]=x;
			T->index[i]=y;
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
	    T->index[T->count]=M->index[i];
	    T->child[T->count++]=M->child[i];
    }
    T->child[T->count]=M->child[M->count];
	return T;
}

btnode* parent(int key,int index)
{
	btnode *T;
	T=new(btnode);
	T->key[T->count]=key;
	T->index[T->count++]=index;
	return T;
}

btnode* nodesplitting (btnode* &T,int x)
{
	if(T->parent!=NULL)
	{
		sort(T);
		btnode *M=split(T);
		T->parent->key[T->parent->count]=T->key[T->count/2];
		T->parent->index[T->parent->count++]=T->index[T->count/2];
		T->parent->child[T->parent->count]=M;
		M->x=T->x;
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
		btnode *K=parent(T->key[T->count/2],T->index[T->count/2]);
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

void createbtree(btnode* &T,int key,int index,int x)
{
	int i,c=0;
	for(i=0;i<T->count;i++)
	{
		if(key<T->key[i])
		{
			if(T->child[i]!=NULL)
			{
				T->child[i]->parent=T;
			    createbtree(T->child[i],key,index,x);
			    c=1;
			}
			break;
		}
	}
	if(i==T->count&&T->child[i]!=NULL)
	{
		T->child[i]->parent=T;
	    createbtree(T->child[i],key,index,x);
	}
	else if(T->count<2*d&&T->child[0]==NULL)
	{
		T->x=x;
		T->key[T->count]=key;
		T->index[T->count++]=index;
		if(T->count!=1)
		sort(T);
	}
    else if(T->count==2*d&&c==0)
    {
    	T->key[T->count]=key;
    	T->index[T->count++]=index;
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

void assignptr(btnode* &T,int p)
{
	if(T!=NULL)
	{
		int i;
		for(i=0;i<=T->count;i++)
		{
			if(T->child[i]!=NULL)
			T->ptr[i]=2*p+i+1;
		}
		for(i=0;i<=T->count;i++)
		{
			assignptr(T->child[i],T->ptr[i]);
		}
	}
}

void store(btnode *T,ofstream &out,int h)
{
    if(T!=NULL)
	{
		int i;
		if(h==0)
		for(i=0;i<T->count;i++)
		{
			for(i=0;i<T->count;i++)
			out<<T->ptr[i]<<" "<<T->key[i]<<" ";
			out<<T->ptr[i]<<"   ";
		}
		for(i=0;i<T->count;i++)
		{
			store(T->child[i],out,h-1);
		}
		store(T->child[i],out,h-1);
	}
}

int main()
{
	int c=0;
	ofstream out;
	char a[10];
	student s;
	buffer b;
	out.open("B_tree_datafile.txt");
	btnode *T=new(btnode);
	cout<<"Enter roll no:";
	cin>>s.rollno;
	do
	{
		itoa(c,a,10);
		b.pack1(a);
		createbtree(T,s.rollno,c,0);
		itoa(s.rollno,a,10);
		b.pack(a);
	    cout<<"Enter name:";
	    cin>>s.name;b.pack(s.name);
	    cout<<"Enter cgpa:";
	    cin>>s.cgpa;	b.pack(s.cgpa);
	    b.store(out);
		c++;
		if(A!=NULL)
		T=A;
		cout<<"Enter roll no:";
	    cin>>s.rollno;
	}while(s.rollno!=0);
	out.close();
	out.open("btreeindexfile.txt");
	assignptr(T,0);
	for(int i=T->x;i>=0;i--)
	{
	    display(T,i);
	    cout<<endl;
	}
	for(int i=0;i<=T->x;i++)
	{
	    store(T,out,i);
	    out<<endl;
	}
	out.close();
	return 0;
}
