#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

struct bstnode
{
	bstnode *lchild;
	int data;
	bstnode *rchild;
};

int maxi=0;

void insert(bstnode* &T,int elt,int x)
{
	if(T!=NULL)
	{
		if(elt<T->data)
		insert(T->lchild,elt,x+1);
		else
		insert(T->rchild,elt,x+1);
	}
	else
	{
		if(maxi<x)
		maxi=x;
	    T=new(bstnode);
	    T->data=elt;
	    T->lchild=NULL;
	    T->rchild=NULL;
    }
}
int side=0;
void display(bstnode *T,int x,int level)
{
	if(T!=NULL&&x>=0)
	{
		if(x==0)
		{
			int spctr=pow(2,level);
			if(side==0)
			for(int j=0;j<spctr-1;j++)
			cout<<"  ";
			else
			for(int j=0;j<(2*spctr-1);j++)
			cout<<"  ";
			cout<<setw(3)<<T->data;
			side++;
		}
		else
		{
	    	display(T->lchild,x-1,level-1);
	    	display(T->rchild,x-1,level-1);
	    }
    }
    else if(x>=0&&T==NULL)
    {
    	int sp=pow(2,level);
    	if(side==0)
    	{
	    	for(int i=0;i<2*sp-1;i++)
    		cout<<"  ";
    		side++;
    	}
		else
		for(int i=0;i<2*sp;i++)
    	cout<<"  ";	
    }
}
int main()
{
	int d,k1,k2;
	bstnode *T;
	T=NULL;
	int c=0;
    cout<<"Enter root node : ";
	cin>>d;
	T=new(bstnode);
	T->data=d;
	T->lchild=NULL;
	T->rchild=NULL;
	cout<<"Enter elements (-1 to stop) :\n";
	cin>>d;
	while(d!=-1)
    {
    	insert(T,d,0);
    	cin>>d;
    }
    for(int i=0;i<=maxi;i++)
    {
    	side=0;
    	display(T,i,maxi);
    	cout<<endl;
	}
    return 0;
}
