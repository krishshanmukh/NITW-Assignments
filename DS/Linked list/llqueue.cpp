#include<iostream>
#include<cstdlib>
using namespace std;
struct node
{
	int data;
	node *next;
};
struct lnq
{
	node *front;
	node *rear;
};
void addend(node* A,int x)
{
	node *T=new(node);
	T->data=x;
	T->next=NULL;
	A=T;
}
int del(node* &A)
{
	node *T;
	T=A;
	A=A->next;
	int d=T->data;
	T->next=NULL;
	delete(T);
	return d;
}
void enqueue(lnq Q,int x)
{
	if(Q.front==NULL)
	{
	addend(Q.front,x);
	Q.rear=Q.front;
    }
    else
    addend(Q.rear,x);
}
int delqueue(lnq Q)
{
	if(Q.front!=NULL)
	{
	    int d=del(Q.front);
	    return d;
	}
	else
	return NULL;
}
void display(lnq Q)
{
	while(Q.front!=NULL)
	{
	cout<<Q.front->data<<" ";
	Q.front=Q.front->next;
    }
}
int main()
{
	lnq Q;
	node *T;
	cout<<"1.enqueue\n2.delqueue\n3.display\n4.exit\nEnter choice: ";
	int choice;
	cin>>choice;
	Q.front=new(node);
	Q.rear=Q.front;
	do
	{
		switch(choice)
		{
			case 1:
				cout<<"Enter no: ";
				int ch;
				cin>>ch;
				enqueue(Q,ch);
				break;
		    case 2:
		    	if(Q.front!=NULL)
		    	cout<<"Deleted "<<delqueue(Q);
		    	break;
		    case 3:
		    	display(Q);
				break;
			case 4:
			    exit(0);
			    break;
			default:
			    cout<<"Wring choice!";	
		}
		cout<<"\n1.enqueue\n2.delqueue\n3.display\n4.exit\nEnter choice: ";
		cin>>choice;
	}while(choice!=4);
	return 0;
}
