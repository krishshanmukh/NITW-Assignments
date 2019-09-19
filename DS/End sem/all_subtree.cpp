#include<iostream>
using namespace std;

struct bstree
{
	int data;
	bstree *lchild;
	bstree *rchild;
};

void create(bstree* &T,int elt)
{
	if(T==NULL)
	{
		T=new(bstree);
		T->data=elt;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	else
	{
		if(elt<T->data)
		create(T->lchild,elt);
		else
		create(T->rchild,elt);
	}
}

void display(bstree *T,int x)
{
	if(T!=NULL&&x>=0)
	{
		if(x==0)
		cout<<T->data<<" ";
		else
		{
			display(T->lchild,x-1);
			display(T->rchild,x-1);
		}
	}
}

int maximum;

void calheight(bstree *T,int x)
{
	if(T!=NULL)
	{
		if(x>maximum)
		maximum=x;
		calheight(T->lchild,x+1);
		calheight(T->rchild,x+1);
	}
}

void subtree(bstree *T)
{
	if(T!=NULL)
	{
		cout<<T->data<<" ---- \n";
		maximum=0;
		calheight(T,0);
		for(int i=0;i<=maximum;i++)
		{
			display(T,i);
			cout<<endl;
		}
		cout<<endl;
		subtree(T->lchild);
		subtree(T->rchild);
	}
}

int main()
{
	bstree *T=NULL;
	int elt;
	cout<<"Enter elt: (-1 to stop) ";
	cin>>elt;
	while(elt!=-1)
	{
		create(T,elt);
		cin>>elt;
	}
	subtree(T);
	return 0;
}
