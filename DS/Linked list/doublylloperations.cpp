#include<iostream>
using namespace std;
struct dnode
{
	dnode *left;
	int data;
	dnode *right;
};
void addbegin(dnode* &A, int x)
{
	A->left=new(dnode);
	A->left->right=A;
	A=A->left;
	A->data=x;
	A->left=NULL;
}
void addend(dnode *A, int x)
{
	while(A->right!=NULL)
	A=A->right;
	A->right=new(dnode);
	A->right->left=A;
	A=A->right;
	A->data=x;
	A->right=NULL;
}
void addbefore(dnode *A,int x,int y)
{
	while(A->data!=y)
	A=A->right;
	dnode *T=new(dnode);
	T->data=x;
	T->right=A;
	T->left=T->right->left;
	if(T->left!=NULL)
	T->left->right=T;
	T->right->left=T;
}
void addafter(dnode *A,int y,int x)
{
	while(A->data!=y)
	A=A->right;
	dnode *T=new(dnode);
	T->data=x;
	T->left=A;
	T->right=T->left->right;
	T->left->right=T;
	if(T->right!=NULL)
	T->right->left=T;
}
void del(dnode *A,int x)
{
	while(A->data!=x)
	A=A->right;
	dnode *T=A;
	T->left->right=T->right;
	if(T->right!=NULL)
	T->right->left=T->left;
	T->right=NULL;
	T->left=NULL;
}
void display(dnode *A)
{
	if(A!=NULL)
    {
    	cout<<A->data<<" ";
    	display(A->right);
    }
}
int main()
{
	dnode *A;
	int x,ch;
	cout<<"Enter first elt: ";
	A=new(dnode);
	cin>>x;
	A->data=x;
	A->right=NULL;
	A->left=NULL;
	cout<<"1.addend\n2.addbegin\n3.addbefore\n4.addafter\n5.delete\n6.display\n7.exit";
	cout<<"\nEnter choice: ";
	cin>>ch;
	while(ch!=7)
	{
		if(ch==1)
		{
			cout<<"Enter no: ";
			cin>>x;
			addend(A,x);
		}
		else if(ch==2)
		{
			cout<<"Enter no: ";
			cin>>x;
			addbegin(A,x);
		}
		else if(ch==3)
		{
			cout<<"Enter no to add: ";
			cin>>x;
			cout<<"Before elt: ";
			int y;
			cin>>y;
			addbefore(A,x,y);
		}
		else if(ch==4)
		{
			cout<<"Enter no to add: ";
			cin>>x;
			cout<<"After elt: ";
			int y;
			cin>>y;
			addafter(A,y,x);
		}
		else if(ch==5)
		{
			cout<<"Enter elt: ";
			cin>>x;
			del(A,x);
		}
		else if(ch==6)
		{
			display(A);
			cout<<endl;
		}
		else
		cout<<"Wrong choice!\n";
		cout<<"enter choice: ";
		cin>>ch;
	}
	return 0;
}
