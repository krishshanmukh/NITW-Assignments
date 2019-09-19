#include<iostream>

using namespace std;

struct node
{
	int tag;
	union
	{
		int no;
		node *ptr;
	}data;
	node *next;
};

void input(node* &T,int elt)
{
	cin>>elt;
	if(T==NULL&&elt!=-2)
	{
		T=new(node);
		T->next=NULL;
		if(elt!=-1)
		{
			T->tag=1;
			T->data.no=elt;
		}
		else
		{
			T->tag=2;
			T->data.ptr=NULL;
			input(T->data.ptr,elt);
		}
		input(T->next,elt);
	}
}

void display(node *T)
{
	if(T!=NULL)
	{
		if(T->tag==1)
		cout<<T->data.no<<" ";
		else
		{
			cout<<"( ";
			display(T->data.ptr);
			cout<<") ";
		}
		display(T->next);
	}
}

int main()
{
	int elt;
	node *T=NULL;
	input(T,elt);
	display(T);
	return 0;
}
