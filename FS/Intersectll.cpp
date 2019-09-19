#include<iostream>
using namespace std;
struct node
{
	int data;
	node *next;
};
void print(node *L)
{
	if(L!=NULL)
	{
		cout<<L->data<<"\t";
		print(L->next);
	}
}
node* intersect(node *L,node *M,node *C)
{
	node *A,*B,*D;int c=0;
	A=M;
	while(L!=NULL)
	{
		M=A;
		while(M!=NULL)
		{
			if(M->data==L->data)
		    {
		    	c++;
			    B=new(node);
			    if(c==1)
			    {C=B;D=C;}
			    else
			    {
			    C->next=B;C=C->next;}
			    B->data=L->data;
			    B->next=NULL;break;
		    }M=M->next;
		}L=L->next;
	}
	return D;
}
int main()
{
	node *L,*M,*A,*B,*I;
	int c;
	cout<<"Enter first elt of ll 1 : ";
	L=new(node);
	M=new(node);
	A=L;B=M;
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
	cout<<"Enter first elt of ll 2 : ";
	cin>>c;
	M->data=c;
	M->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>c;
	while(c!=0)
	{
		I=new(node);
		I->data=c;
		I->next=NULL;
		M->next=I;
		M=M->next;
		cin>>c;
	}
	I=intersect(A,B,I);
	print(I);
	return 0;
}
