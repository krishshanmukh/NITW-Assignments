#include<iostream>
#include<cstring>
using namespace std;

struct ttree
{
	char data[2];
	ttree *child[3];
};

int size;

void input(ttree *T,char c[],int i)
{
	if(i<size)
	{
		T->data[0]=c[i];
		T->data[1]=c[i+1];
		T->child[0]=NULL;
		T->child[1]=NULL;
		T->child[2]=NULL;
		if((3*i+2)<size)
		{
			T->child[0]=new(ttree);
			
			input(T->child[0],c,(3*i+2));
		}			
		
		if((3*i+4<size))
		{
			T->child[1]=new(ttree);
			
			input(T->child[1],c,(3*i+4));
		}	
		
		if((3*i+6<size))
		{
			T->child[2]=new(ttree);
			
			input(T->child[2],c,(3*i+6));
		}	
		
	}
}
void display(ttree *T)
{
	if(T!=NULL)
	{
		
	    cout<<T->data[0]<<" ";
	    cout<<T->data[1]<<" ";
		if(T->child[0]!=NULL)
	    display(T->child[0]);
	    if(T->child[1]!=NULL)
	    display(T->child[1]);
	    if(T->data[1]!=-1)
	    if(T->child[2]!=NULL)
	    display(T->child[2]);
    }
}

int main()
{
	char c[30];
	ttree *T;
	cin>>c;
	size=strlen(c);
	T=new(ttree);
	input(T,c,0);
	display(T);
	return 0;
}
