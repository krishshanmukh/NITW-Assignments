#include<iostream>
using namespace std;
int c=0;
int d=0;
struct mlnode
{
	int tag;
	union
	{
		int d;
		mlnode *slist;
	}*data;
	mlnode *next;
};

void addelt(mlnode* &M)
{
	cout<<"Enter no:";
    int i;cout<<"!";
	cin>>i;cout<<i;
	if(i!=0)
	{cout<<"@";
		if(M==NULL)
		{
		M=new(mlnode);
		M->next=NULL;}
		if(i!=-1&&i!=-2)
		{
			M->tag=1;
			M->data->d=i;
			addelt(M->next);
		}
		else if(i==-1)
		{
			M->tag=2;
			M->data->slist=NULL;
			addelt(M->data->slist);
			addelt(M->next);
		}
	}
}
void display(mlnode *M)
{
	if(M!=NULL)
	{
		if(M->tag==1)
		{
			cout<<M->data.d<<",";
			display(M->next);
		}
		else
		{
			cout<<"(";
			display(M->data.slist);
			display(M->next);
		}
	}
	else
	cout<<"\b),";
}


int main()
{
	mlnode *M,*N;
	M=new(mlnode);
	M->next=new(mlnode);
	M->next->next=NULL;
	N=M;
	cout<<"Enter elts of set: (0 to stop) (-1 to start slist -2 to stop slist) " ;
 	    addelt(M);
	cout<<"(";
	display(M);
	return 0;
}
