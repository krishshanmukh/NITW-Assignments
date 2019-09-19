#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;
};

struct heap
{
	node *T;
};

void heap_create(heap H[],int x)
{
	if(x>0)
	{
		if(H[x].T->data<H[(x-1)/2].T->data)
		{
			heap temp=H[x];
			H[x]=H[(x-1)/2];
			H[(x-1)/2]=temp;
			heap_create(H,(x-1)/2);
		}
	}
}

void input(heap H[],int &count)
{
	cout<<"Enter elts: "<<endl;
	int elt;
	cin>>elt;
	while(elt!=-1)
	{
		H[count].T=new(node);
		H[count].T->next=NULL;
		H[count++].T->data=elt;
		heap_create(H,count-1);
		cin>>elt;
	}
}

void heapify(heap H[],int x,int size)
{
	if((2*x+2)<=size)
	{
		int p=(H[2*x+1].T->data>H[2*x+2].T->data?2*x+2:2*x+1);
		if(H[p].T->data<H[x].T->data)
		{
			heap temp=H[x];
			H[x]=H[p];
			H[p]=temp;
			heapify(H,p,size);
		}
	}
	else if((2*x+1)<=size)
	{
		int p=2*x+1;if(H[p].T->data<H[x].T->data)
		{
			heap temp=H[x];
			H[x]=H[p];
			H[p]=temp;
			heapify(H,p,size);
		}
	}
}

node* heap_sort(heap H[],int &size)
{
	node *L=H[0].T;
	H[0]=H[size--];
	heapify(H,0,size);
	return L;
}

node *L;

void linked_list(heap H[],int size)
{
	static node *M=heap_sort(H,size);
	L=M;	
	while(size>=0)
	{
		L->next=heap_sort(H,size);
		L=L->next;
	}
	L=M;
}

void display(node *M)
{
	if(M!=NULL)
	{
		cout<<M->data<<" ";
		display(M->next);
	}
}

int main()
{
	heap H[100];
	int size=0;
	input(H,size);
	linked_list(H,size-1);
	display(L);
	return 0;
}
