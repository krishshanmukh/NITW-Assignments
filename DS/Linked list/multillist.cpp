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
	}data;
	mlnode *next;
};
mlnode *t[5];
void addelt(mlnode *M)
{
	int i;
	cin>>i;
	if(i!=0)
	{
		if((i!=-1)&&(i!=-2))//as long as you don't go to a sub level
		{
			if(M->next!=NULL)//If M->next is NULL you should create new mlnode otherwise it is already created
			{
				M->tag=1;
				M->data.d=i;
				M->next=NULL;
			}
			else
			{
				M->next=new(mlnode);
				M=M->next;
				M->tag=1;
				M->data.d=i;
				M->next=NULL;
			}
			addelt(M);
		}
		else if(i==-1)//when you encounter an ( symbol
		{
			if(M->next!=NULL)
			{
				M->tag=2;
				M->data.slist=new(mlnode);
				M->next=NULL;
				t[d]=M;d=0;//storing parent address of iptr
				M=M->data.slist;
			}
			else
			{
				M->next=new(mlnode);
				M=M->next;
				M->tag=2;
				M->data.slist=new(mlnode);
				M->next=NULL;
				t[d]=M;d++;
				M=M->data.slist;
			}
			addelt(M);
		}
		else if(i==-2)//retrieving parent address after encountering ) symbol
		{
			addelt(t[--d]);
		}
		else
		;
	}
}
void display(mlnode *M,mlnode *N)
{
	if(N!=NULL)
	{
		if(M!=NULL)
		{
	    if(M->tag==1)
	    {
		    cout<<M->data.d<<",";
		    if(M==N)//as long as M and N are at same level
		    {
		    M=M->next;
		    N=N->next;
		    }
		    else
		    M=M->next;
		    display(M,N);
	    }
	    else if(M->tag==2)
	    {
	    	cout<<"(";
	    	mlnode *T;
	    	T=M;//sroring data of previous level to use it when calling recursively
	    	M=M->data.slist;
	    	display(M,N);//displaying slist
	    	cout<<"\b),";
	    	if(T==N)
	    	{
	    	N=N->next;
	    	T=T->next;
	        }
	        else
	        T=T->next;
	    	display(T,N);
	    }
	    else ;
	}
    }
}



int main()
{
	mlnode *M,*N;
	M=new(mlnode);
	N=M;
	cout<<"Enter elts of set: (0 to stop) (-1 to start slist -2 to stop slist) " ;
	addelt(M);
	c=0;
	cout<<"(";
	display(M,N);
	cout<<"\b)";//to remove excess ,
	return 0;
}
