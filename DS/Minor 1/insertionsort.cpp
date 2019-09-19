#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;
};

int ctr=0;
int a;

void addbefore(node *A,int x,int y)
{
	node *T;
	while(A->next->data!=y&&A->next!=NULL)
	A=A->next;
	T=new(node);
	T->data=x;
	T->next=A->next;
	A->next=T;
}

void del(node *A,int x)
{
	while(A->next->data!=x)
	A->next=A->next->next;
	A->next=A->next->next;
	delete(A->next);
}

void sort(node* &L,int x,node *M)
{
	if(a<=ctr)
	{
		a++;
		if(x<L->data)
		{
			if(ctr==0)
			{
				L->next->data=L->data;
				L->data=x;
			}
			else
			{
				del(M,x);
		        addbefore(M,x,L->data);
		    }
		}
		else
		{
			a++;cout<<"@";
			if(L->next!=NULL)
			sort(L->next,x,M);
		}
	}
}

void print(node *L)
{
	if(L!=NULL)
	{
		cout<<L->data<<"\t";
		print(L->next);
	}
}

int main()
{
	node *L,*M,*I;
	int c;
	cout<<"Enter first elt of ll 1 : ";
	L=new(node);
	M=L;
	cin>>c;
	L->data=c;
	L->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>c;
	while(c!=0)
	{
		I=new(node);
		I->data=c;
		I->next=NULL;
		L->next=I;
		L=L->next;
		cin>>c;
	}
	L=M;
	I=M;
	L=L->next;
	while(L!=NULL)
	{
		a=0;
		sort(I,L->data,M);
		ctr++;
		I=M;
		L=L->next;
	}
	print(M);
	return 0;
}
