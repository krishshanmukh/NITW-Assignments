#include<iostream>
using namespace std;
struct bstnode
{
	bstnode *lchild;
	int data;
	bstnode *rchild;
};
void insert(bstnode* T,int x)
{
	if(T!=NULL)
	{
		if(x<T->data)
		{
			if(T->lchild!=NULL)
			insert(T->lchild,x);
			else
			{
			    T->lchild=new(bstnode);
			    T=T->lchild;
			    T->data=x;
			    T->lchild=NULL;
			    T->rchild=NULL;
		    }
		}
		else
		{
			if(T->rchild!=NULL)
			insert(T->rchild,x);
			else
			{
			    T->rchild=new(bstnode);
			    T=T->rchild;
			    T->data=x;
			    T->rchild=NULL;
			    T->lchild=NULL;
			}
		}
	}
}
int max(bstnode *T)
{
	if(T->rchild==NULL)
	{
		return T->data;
	}
	else
	return (max(T->rchild));
}
int f=0;
bstnode* max(bstnode *T,bstnode* &M)
{
	if(T->rchild!=NULL)
	{
		f++;
		M=T;
	    return (max(T->rchild,M));
	}
	else if(f!=0)
	{
	return T;
    }
	else
	{
		M=T;
		return T;
	}
}
bstnode* search(bstnode *T,bstnode* &M,int k)
{
	if(T!=NULL)
	{
	    if(k<T->data)
	    {
	    M=T;
	    return search(T->lchild,M,k);
	    }
	    else if(k>T->data)
	    {
	    	M=T;
	    	return search(T->rchild,M,k);
	    }
	    else
	    return T;
	}
}
void del(bstnode *T,int k)
{
	bstnode *M,*N,*O,*P;
	int i;
	N=search(T,M,k);//N (pointer to be deleted) has pointer of k and M has parent of N
	if(N->lchild!=NULL)
	{
	    i=max(N->lchild);
	    P=max(N->lchild,O);//to store parent of max in O and max in P 
        if(N->lchild==P)
        O=N;
	if(N->lchild==NULL&&N->rchild==NULL)
	{
		if(M->lchild==N)
		M->lchild=NULL;
		else
		M->rchild=NULL;
		delete(N);
		return;
	}
	else
	{
		N->data=i;
		if(O->lchild==P)
		O->lchild=NULL;
		else
		O->rchild=P->rchild;
		delete(P);
		return;
	}
    }
    else
    {
    	M->rchild=N->rchild;
    	delete(N);
    }
}
void display(bstnode *T)
{
	if(T!=NULL)
	{
		if(T->lchild!=NULL)
	    display(T->lchild);
	    cout<<T->data<<" ";
	    if(T->rchild!=NULL)
	    display(T->rchild);
    }
}
void printt(bstnode *T)
{
	if(T!=NULL)
	{
	    if(T->rchild==NULL&&T->lchild==NULL)
	    cout<<T->data<<" ";
	    printt(T->lchild);
	    printt(T->rchild);
	}
}
void printnt(bstnode *T)
{
	if(T!=NULL)
	{
	    if(T->rchild!=NULL||T->lchild!=NULL)
	    cout<<T->data<<" ";
	    if(T->lchild!=NULL)
        printnt(T->lchild);
        if(T->rchild!=NULL)
        printnt(T->rchild);
	}
}

int min(bstnode *T)
{
	if(T->lchild==NULL)
	{
		return T->data;
	}
	else
	return (min(T->lchild));
}
int main()
{
	int d;
	bstnode *T,*M,*I;
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
    	insert(T,d);
    	cin>>d;
    }
    cout<<"Elts in sorted order: ";
	display(T);
	cout<<"\nTerminal nodes are: ";
	printt(T);
	cout<<"\nNon-Terminal nodes are: ";
	printnt(T);
	cout<<"\nMax elts: "<<max(T);
	cout<<"\nMin elt: "<<min(T);
	cout<<"\nEnter elt to delete: ";
	cin>>d;
	M=search(T,I,d);
	if(M->data==d)
	cout<<"elt found\n"<<endl;
	if(M->data==d)
	del(T,d);
	else
	cout<<"Elt not found!\n";
    display(T);
    return 0;
}
