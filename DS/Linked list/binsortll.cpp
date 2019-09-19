#include<iostream>
#include<cstdlib>
using namespace std;
struct node
{
	int data2;
	char data1;
	node *next;
};
node* sort(node* L,node *C)
{
	C=L;
	int s=0;node *T;
	while(L!=NULL)
	{
	L=L->next;s++;}
	for(int i=0;i<s-1;i++)
	{
		L=C;
		for(int j=i+1;j<s;j++)
		{
			if(L->data1>L->next->data1)
			{
				char t=L->data1;
				L->data1=L->next->data1;
				L->next->data1=t;
				int k=L->data2;
				L->data2=L->next->data2;
				L->next->data2=k;
			}
			L=L->next;
		}		
	}
	T=C;
	L=C;
		while(L!=NULL)
	{
		s=1;
		if(L->next!=NULL)
		while(L->data1==L->next->data1)
		{
		s++;if(L->next!=NULL)L=L->next;}
			for(int i=0;i<s-1;i++)
			{
				L=C;
			for(int j=i+1;j<s;j++)
			{
			if(L->data2>L->next->data2)
			{
				int t=L->data2;
				L->data2=L->next->data2;
				L->next->data2=t;
			}
			L=L->next;
		    }
		    }
		L=T;
		for(int i=0;i<s;i++)
		L=L->next;
		T=L;
	}
	return C;
}
		

void print(node *L)
{
	if(L!=NULL)
	{
		cout<<L->data1<<" "<<L->data2<<"\t";
		print(L->next);
	}
}
int main()
{
	node *L,*A,*S;
	int c;
	char ch;
	cout<<"Enter first elt of ll(char followed by int) : ";
	L=new(node);
	A=L;
	cin>>ch;
	cin>>c;
	L->data2=c;
	L->data1=ch;
	L->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>ch;
	while(ch!='0')
	{
		cin>>c;
		node* I;
		I=new(node);
		I->data2=c;
		I->data1=ch;
		I->next=NULL;
		L->next=I;
		L=L->next;
		cout<<" Enter Elt: ";cin>>ch;
	}
	S=sort(A,S);
	print(S);
	return 0;
}
