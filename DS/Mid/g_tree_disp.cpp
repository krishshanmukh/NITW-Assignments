#include<iostream>
using namespace std;

struct gtree
{
	gtree *fchild;
	char data;
	gtree *nsibling;
};

void input(gtree* &T,char data)
{
	if(T==NULL)
	{
		T=new(gtree);
		T->data=data;
		T->fchild=NULL;
		T->nsibling=NULL;
	}
	cout<<"Enter first child of "<<T->data<<" :";
	cin>>data;
	if(data!='0')
	input(T->fchild,data);
	cout<<"Enter next sibling of "<<T->data<<" :";
	cin>>data;
	if(data!='0')
	input(T->nsibling,data);
}

void display(gtree *T)
{
	if(T!=NULL)
	{
		cout<<T->data<<" ";
		if(T->fchild!=NULL)
		cout<<"( ";
		display(T->fchild);
		display(T->nsibling);
		if(T->nsibling==NULL)
		cout<<") ";
	}
}

int main()
{
	cout<<"Enter root node: ";
	gtree *T=new(gtree);
	char ch;
	cin>>ch;
	T->data=ch;
	T->fchild=NULL;
	T->nsibling=NULL;
	cout<<"Enter first child of "<<ch<<" :";
	cin>>ch;
	input(T->fchild,ch);
	display(T);
	cout<<"\b ";
	return 0;
}
