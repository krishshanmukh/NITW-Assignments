#include<iostream>
#include<cstdlib>
int c=0;
using namespace std;
struct node
{
	int data;
	node* next;
};
struct lnst
{
	node* top;
};
void addbegin(node* &A,int x)
{
	node *T;
	T=new(node);
	T->data=x;
	if(c!=0)
	T->next=A;
	else
	T->next=NULL;
	A=T;
}
int del(node* &A)
{
	node *T;
	T=A;
	int d=T->data;
	A=A->next;
	T->next=NULL;
	delete(T);
	return d;
}
void push(lnst S,int x)
{
	addbegin(S.top,x);
}
int pop(lnst &S)
{
	if (S.top!=NULL)
	{
	return del(S.top);
	c--;
    }
	else 
	cout<<"Cannot pop!!!";
}
void display(lnst S)
{
	while(S.top!=NULL)
	{
		cout<<S.top->data<<" ";
		S.top=S.top->next;
	}
}
int main()
{
	lnst S;
	cout<<"1.Push\n2.Pop\n3.display\n4.exit\n";
	int ch,x;
	cout<<"Enter choice : ";
	cin>>ch;
	while(ch!=4)
	{
		switch(ch)
		{
			case 1: cout<<"Enter elt: ";
			cin>>x;
			push(S,x);
			c++;
			break;
			case 2: 
			
			x=pop(S);if(c!=0)cout<<"Successfully popped "<<x;
		
			break;
			case 3: node *T;
			T=S.top;
			if(c!=0)
			display(S);
			S.top=T;
			break;
			default:cout<<"Wrong choice!";
		}
		cout<<"\nEnter choice : ";
		cin>>ch;
		}
		return 0;
}
