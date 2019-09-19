#include<iostream>
using namespace std;
union u1
{
	char ch;
	int i;
};
struct node1
{
	int i;
	node1 *next;
};
struct node2
{
	char ch;
	node2 *next;
};
struct node
{
	u1 u;
	int tag;
	node *next;
};
void print(node1 *L)
{
	if(L!=NULL)
	{
		cout<<L->i<<"\t";
		print(L->next);
	}
}
void print(node2 *L)
{
	if(L!=NULL)
	{
		cout<<L->ch<<"\t";
		print(L->next);
	}
}
int main()
{
	node *L,*M;node1 *I,*A;node2 *C,*B;
	cout<<"\n1.int\n2.char\n";
	int c,i;char ch;
	cin>>c;int ctr1=0,ctr2=0;
	L=new(node);C=new(node2);I=new(node1);A=I;B=C;M=L;
	cout<<"Enter first elt of ll : ";
	if(c==1)
	{
		cin>>i;
		L->u.i=i;
		L->tag=c;
	}
	else
	{
		cin>>ch;
	L->u.ch=ch;L->tag=c;}
	L->next=NULL;
	cout<<"Enter remaining elts of ll :";
	cout<<"\n1.int\n2.char\nother.exit : ";
	cin>>c;
	while(c==1||c==2)
	{
		node *T=new(node);cout<<"Enter Elt : ";
		if(c==1)
		{
			cin>>i;
			T->u.i=i;
			L->next=T;
			T->next=NULL;
			T->tag=c;
			L=L->next;
		}
		else
		{
			cin>>ch;
			T->u.ch=ch;
			L->next=T;
			T->next=NULL;
			T->tag=c;
			L=L->next;
		}
		cout<<"Enter choice: ";
		cin>>c;
	}
	while(M!=NULL)
	{
		if(M->tag==1)
		{
			if(ctr1==0)
			{
				I->i=M->u.i;
				I->next=NULL;
			}
			else
			{
			    node1* T;
			    T=new(node1);
			    T->i=M->u.i;
			    T->next=NULL;
			    I->next=T;
			    I=I->next;
			}
			ctr1++;
		}
		else
		{
			if(ctr2==0)
			{
				C->ch=M->u.ch;
				C->next=NULL;
			}
			else
			{
			    node2* T;
			    T=new(node2);
			    T->ch=M->u.ch;
			    T->next=NULL;
			    C->next=T;
			    C=C->next;
			}ctr2++;
		}
		M=M->next;
	}
	cout<<"INT : "
	print(A);
	cout<<endl<<"CHAR : ";
	print(B);
	return 0;
}
