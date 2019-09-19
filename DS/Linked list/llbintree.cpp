#include<iostream>
using namespace std;
struct inode
{
	char cdata;
	int data;
	inode* next;
};
struct node
{
	int data;
	node *next;
};
struct onode
{
	char cdata;
	node* iptr;
	onode *next;
};
void input(inode* &I)
{
	cout<<"Enter elt: (char followed by int)";
	char c;int i;
	inode *R;
	cin>>c>>i;
	I=new(inode);
	R=I;
	I->cdata=c;
	I->data=i;
	I->next=NULL;
	cout<<"Do you want to enter more?(y for yes)  ";
	char ch;
	cin>>ch;
	while(ch=='y')
	{
		cout<<"Enter elt : ";
	    cin>>c>>i;
	    inode *T;
	    T=new(inode);
	    T->cdata=c;
	    T->data=i;
	    T->next=NULL;
	    R->next=T;
	    R=R->next;
	    cout<<"Enter choice: (y to continue)  ";
	    cin>>ch;
	}
}
void addbefore(node *A,int x,int y)
{
	node *T;
	while(A->next->data!=y&&A->next!=NULL)
	A=A->next;
	T=new(node);
	T->data=x;
	T->next=A->next;
	A->next=T;
}
void addend(node *A,int x)
{
	while(A->next!=NULL)
	A=A->next;
	A->next=new(node);
	A->next->data=x;
	A->next->next=NULL;
}
void addbegin(node* &A,int x)
{
	node *T=new(node);
	T->data=x;
	T->next=A;
	A=T;
}
void display(onode *O)
{
	if(O!=NULL)
	{
		cout<<O->cdata<<" ";
		while(O->iptr!=NULL)
		{
		    cout<<O->iptr->data<<" ";
		    O->iptr=O->iptr->next;
		}
		cout<<"\t";
		display(O->next);
	}
}
void sort(inode *I,onode* &O)
{
	onode* T2;
	O=new(onode);
	T2=O;
	int v;
	T2->cdata=I->cdata;
	T2->iptr=new(node);
	T2->iptr->data=I->data;
	T2->next=NULL;
	T2->iptr->next=NULL;
	I=I->next;
	while(I!=NULL)
	{
		O=T2;v=0;
		while(O!=NULL)
		{
			node* T;
			if(I->cdata==O->cdata)
			{v=1;
				T=O->iptr;int c=0;
				while(O->iptr->next!=NULL)
				{
					c=1;
					if(I->data<=O->iptr->data)
					{
						if(c==1)//as elt is less than first elt of iptr addbegin is used
						addbegin(O->iptr,I->data);
						else
						addbefore(T,I->data,O->iptr->data);
						break;
					}
					else//if elt is greater than frst and remng elts increment c by 1
					{
					O->iptr=O->iptr->next;c++;}
				}
				if(c==0)//only 1 elt in iptr
				{
				if(O->iptr->data>I->data)
			    addbegin(O->iptr,I->data);
			    else
			    addend(T,I->data);
			    }//elt is greatest of all so add at end
				if(T->next==NULL&&c!=0)
				addend(T,I->data);
			}
			
			O=O->next;
		}
		O=T2;
		if(v!=1)//no onode for given character so create new onode
		{
			while(O->next!=NULL)
			O=O->next;
			O->next=new(onode);
			O->next->cdata=I->cdata;
			O->next->iptr=new(node);
			O->next->iptr->data=I->data;
			O->next->iptr->next=NULL;
			O->next->next=NULL;
		}
		I=I->next;
	}
	O=T2;
}
int main()
{
	int a=1;
	inode *I;
	onode *O;
	input(I);
	sort(I,O);
	display(O);
	return 0;
}
