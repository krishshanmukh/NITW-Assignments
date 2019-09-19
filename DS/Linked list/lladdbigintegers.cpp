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
void addend(dnode* &A, int x)
{
	while(A->right!=NULL)
	A=A->right;
	A->right=new(dnode);
	A->right->left=A;
	A=A->right;
	A->data=x;
	A->right=NULL;
}
void display(dnode *A)
{
	if(A!=NULL)
    {
    	cout<<A->data;
    	display(A->right);
    }
}
void add(dnode *A,dnode *B,dnode *&C)
{
	C=new(dnode);
	int a,b;
	a=((A->data)+(B->data))%10;
	b=((A->data)+(B->data))/10;
	C->data=a;
	C->left=NULL;
	C->right=NULL;
	A=A->left;
	B=B->left;
	while(A->left!=NULL&&B->left!=NULL)
	{
		a=((A->data)+(B->data)+b)%10;
	    addbegin(C,a);
	    b=((A->data)+(B->data))/10;
	    A=A->left;
	    B=B->left;
	}
	a=((A->data)+(B->data)+b)%10;
    addbegin(C,a);
	b=((A->data)+(B->data))/10;
	if(A->left==NULL)
	{
		B=B->left;
		while(B->left!=NULL)
		{
			a=((B->data)+b)%10;
	        addbegin(C,a);
	        b=(B->data)/10;
	        B=B->left;
		}
		a=(B->data+b)%10;
		b=(B->data+b)/10;
		addbegin(C,a);
	}
	else if(B->left==NULL)
	{
		A=A->left;
		while(A->left!=NULL)
		{
			a=((A->data)+b)%10;
	        addbegin(C,a);
	        b=(A->data)/10;
	        A=A->left;
		}
		a=(A->data+b)%10;
		b=(A->data+b)/10;
		addbegin(C,a);
	}
	if(b!=0)
	addbegin(C,b);
}
int main()
{
	char a[50],i=0;
	dnode *A,*B,*C,*D,*E,*F;
	cout<<"Enter first no: ";
	cin>>a;
	A=new(dnode);
	B=A;
	A->data=a[i]-'0';
	A->right=NULL;
	A->left=NULL;
	i++;
	while(a[i]!='\0')
	{
		addend(A,a[i]-'0');
		i++;
	}
	cout<<"Enter second no: ";
	cin>>a;
	i=0;
	C=new(dnode);
	D=C;
	C->data=a[i]-'0';
	C->right=NULL;
	C->left=NULL;
	i++;
	while(a[i]!='\0')
	{
		addend(C,a[i]-'0');
		i++;
	}
	add(A,C,E);
	cout<<"Sum is : "<<endl;
	display(E);
	return 0;
}
