#include<iostream>
using namespace std;

struct tstnode
{
	int data[2];
	tstnode *child[3];
}*M;
void insert(tstnode* T,int x)
{
	if(T!=NULL)
	{
		if(x<T->data[0])
		{
			if(T->child[0]!=NULL)
			insert(T->child[0],x);
			else
			{
				if(T->data[1]!=-1)
				{
			    T->child[0]=new(tstnode);
			    T=T->child[0];
			    T->data[0]=x;
			    T->child[0]=NULL;
			    T->child[1]=NULL;
			    T->child[2]=NULL;
			    T->data[1]=-1;
			    }
			    else
			    {
			    	if(T->data[0]>x)
			    	{
			    		T->data[1]=T->data[0];
			    		T->data[0]=x;
			    	}
			    	else
			    	T->data[1]=x;
			    }
		    }
		}
	
		else if (x<T->data[1]&&x>T->data[0])
		{
			if(T->child[1]!=NULL)
			insert(T->child[1],x);
			else
			{
				if(T->data[1]!=-1)
				{
			    T->child[1]=new(tstnode);
			    T=T->child[1];
			    T->data[0]=x;
			    T->child[0]=NULL;
			    T->child[1]=NULL;
			    T->child[2]=NULL;
			    T->data[1]=-1;
			    }
			    else
			    {
			    	if(T->data[0]>x)
			    	{
			    		T->data[1]=T->data[0];
			    		T->data[0]=x;
			    	}
			    	else
			    	T->data[1]=x;
			    }
		    }
		}
		else
		{
			if(T->child[2]!=NULL)
			insert(T->child[2],x);
			else
			{
				if(T->data[1]!=-1)
				{
			    T->child[2]=new(tstnode);
			    T=T->child[2];
			    T->data[0]=x;
			    T->child[0]=NULL;
			    T->child[1]=NULL;
			    T->child[2]=NULL;
			    T->data[1]=-1;
			    }
			    else
			    {
			    	if(T->data[0]>x)
			    	{
			    		T->data[1]=T->data[0];
			    		T->data[0]=x;
			    	}
			    	else
			    	T->data[1]=x;
			    }
		    }
		}
	}
}

void display(tstnode *T)
{
	if(T!=NULL)
	{
		if(T->child[0]!=NULL)
	    display(T->child[0]);
	    cout<<T->data[0]<<" ";
	    if(T->child[1]!=NULL)
	    display(T->child[1]);
	    if(T->data[1]!=-1)
	    cout<<T->data[1]<<" ";
	    if(T->child[2]!=NULL)
	    display(T->child[2]);
    }
}
int max(tstnode *T)
{
	if(T->child[2]==NULL)
	{
		if(T->data[1]!=-1)
		return T->data[1];
		else
		return T->data[0];
	}
	else
	return (max(T->child[2]));
}
int min(tstnode *T)
{
	if(T->child[0]==NULL)
		return T->data[0];
	else
	return (max(T->child[2]));
}

int main()
{
	int d;
	tstnode *T;
    cout<<"Enter root nodes : ";
	cin>>d;
	T=new(tstnode);
	M=T;
	T->data[0]=d;
	T->child[0]=NULL;
	T->child[1]=NULL;
	T->child[2]=NULL;
	cin>>d;
	if(T->data[0]<d)
	T->data[1]=d;
	else
	{
		T->data[1]=T->data[0];
		T->data[0]=d;
	}
	cout<<"Enter elements (-1 to stop) :\n";
	cin>>d;
	while(d!=-1)
    {
    	insert(T,d);
    	cin>>d;
    }
    display(T);
    cout<<"\nMax value is: "<<max(T);
    return 0;
}
