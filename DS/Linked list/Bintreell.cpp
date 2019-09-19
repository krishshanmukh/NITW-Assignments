#include<iostream>
using namespace std;
struct node
{
	int i;
	cahr ch;
	node *next;
};
void print(node *L)
{
	if(L!=NULL)
	{
		cout<<L->i<<"\t";
		print(L->next);
	}
}

int main()
{
	node *L,*A,*I;
	int c;char ch;
	cout<<"Enter first elt of ll 1 :(char followe by int) ";
	L=new(node);
	M=new(node);
	A=L;
	cin>>ch;
	cin>>c;
	L->i=c;
	L->ch=ch;
	L->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>c;
	while(c!=0||ch=='0')
	{
		I=new(node);
		I->i=c;
		I->ch=ch;
		I->next=NULL;
		L->next=I;
		L=L->next;
		cin>>ch;
		cin>>c;
	}
	L=A;
	
	print(I);
	return 0;
}
