#include<iostream>
using namespace std;
struct node
{
	int data;
	node *next;
};
void addbegin(node* &A,int i)
{
	node *T;
	T=new(node);
	T->data=i;
	T->next=A;
	A=T;
}
int del(node* &A)
{
	node *T;
	T=A;
	A=A->next;
	int t=T->data;
	delete(T);
	return t;
}
void extract(node* &A,node* &B)
{
	while(A!=NULL)
	{
		B->data=del(A);
		B=B->next;
	}
}
int getelt(node* &A)
{
	int t=A->data;
	A=A->next;
	return t;
}
void addend(node* A,int x)
{
	while(A->next!=NULL)
	A=A->next;
    A->next=new(node);
    A=A->next;
	A->data=x;
	A->next=NULL;
}
void display(node *A)
{
	if(A!=NULL)
	{
		cout<<A->data<<" ";
		display(A->next);
	}
}
int main()
{
	node *R[10],*A,*B;
	int i,j,a,ctr=1,c=1,d=1;
	cout<<"Enter first elt of list: ";
	cin>>a;
	A=new(node);
	B=A;
	A->data=a;
	A->next=NULL;
	cout<<"Enter remng elts (-1 to stop): ";
	cin>>a;
	while(a!=-1)
	{
		addend(A,a);
		cin>>a;
	} 
	for(int k=0;k<10;k++)
	R[k]=NULL;
	A=B;
	while(c==1)
	{
		c=0;
	    while(A!=NULL)
	    {
		    i=getelt(A);
		    j=i/ctr;
		    j=j%10;
		    if(R[j]==NULL)
		    {
		    	R[j]=new(node);
		    	R[j]->next=NULL;
		    	R[j]->data=i;
		    }
		    else
		    addend(R[j],i);
		    if(i/(10*ctr)!=0)
		    c=1;
	    }
	    A=B;
	    ctr*=10;
	    d++;
	    for(int k=0;k<10;k++)
	    {
	    	if(R[k]!=NULL)
	    	{
	    	    extract(R[k],A);
			}
	    }
	    A=B;
	}
	cout<<"Sorted order: "<<endl;
	display(A);
	return 0;
}
