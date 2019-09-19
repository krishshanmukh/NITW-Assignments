#include<iostream>
using namespace std;

const int d = 3;

struct dheap
{
	int data;
	dheap *child[d+1];
	dheap *parent;
	int no;
	dheap()
	{
		for(int i=0;i<d;i++)
		child[i]=NULL;
	}
};

void heapify(dheap *T)
{
	if(T->parent!=NULL)
	{
		if(T->data<T->parent->data)
		{
			int t=T->parent->data;
			T->parent->data=T->data;
			T->data=t;
			heapify(T->parent);
		}
	}
}

void heap_create(dheap* &T,dheap *P,int i,int A[],int size)
{
	int no;
	if(P!=NULL)
	no=P->no;
	else
	no=0;
	int temp=(d*no)+i+1;
	if(T==NULL&&temp<size)
	{
		T=new(dheap);
		T->parent=P;
		T->no=temp;
		T->data=A[temp];
		heapify(T);
		for(int j=0;j<d;j++)
		heap_create(T->child[j],T,j,A,size);
	}
}

void display(dheap *T,int level)
{
	if(T!=NULL&&level>=0)
	{
		if(level==0)
		cout<<T->data<<" ";
		else
		for(int j=0;j<d;j++)
		display(T->child[j],level-1);
    }
}

int calculate(int i)
{
	int j=0;
	while(i!=0)
	{
		j++;
		i/=d;
	}
	return j;
}

int main()
{
	int A[30],elt,i=0;
	cout<<"Enter elts: (-1 to stop) ";
	cin>>elt;
	while(elt!=-1)
	{
		A[i++]=elt;
		cin>>elt;
	}
	dheap *T=NULL;
	heap_create(T,NULL,-1,A,i);
	int height=calculate(i);
	for(int j=0;j<height;j++)
	{
		display(T,j);
		cout<<endl;
	}
	return 0;
}
