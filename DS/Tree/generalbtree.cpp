#include<iostream>
using namespace std;
struct btree
{
	btree *lchild;
	char data;
	btree *rchild;
};
void input(btree *T,char k)
{
	btree *M;
	cout<<"Enter left child of "<<k<<": ";
	char ch;
	cin>>ch;
	M=T;
	if(ch!='*')
	{
	    	T->lchild=new(btree);
	    	M=M->lchild;
	    	M->data=ch;
	    	M->rchild=NULL;
	    	M->lchild=NULL;
		    input(M,ch);
	}
	cout<<"Enter right child of "<<k<<": ";
	cin>>ch;
	M=T;
	if(ch!='*')
	{
	    	M->rchild=new(btree);
	    	M=M->rchild;
	    	M->data=ch;
	    	M->lchild=NULL;
	    	M->rchild=NULL;
		    input(M,ch);	
	}
}
void display(btree *T)
{
	if(T!=NULL)
	{
	    display(T->lchild);
	    cout<<T->data<<" ";
	    display(T->rchild);
    }
}
void compare(btree *T,btree *M,int &c)
{
	if(T!=NULL&&M!=NULL)
    {
		     if(T->lchild!=NULL&&M->lchild!=NULL)
		    {
			    compare(T->lchild,M->lchild,c);
		    }
		    else if(T->lchild==NULL&&M->lchild!=NULL)
		    c=0;
		    else if(T->lchild!=NULL&&M->lchild==NULL)
		    c=0;
		    else ;
		    if(T->rchild!=NULL&&M->rchild!=NULL)
		    {
			    compare(T->rchild,M->rchild,c);
		    }
		    else if(T->rchild==NULL&&M->rchild!=NULL)
		    c=0;
		    else if(T->rchild!=NULL&&M->rchild==NULL)
		    c=0;
		    else;
	}	
}
void compare1(btree *T,btree *M,int &c)
{
	if(T!=NULL&&M!=NULL)
    {
		     if(T->lchild!=NULL&&M->rchild!=NULL)
		    {
			    compare(T->lchild,M->rchild,c);
		    }
		    else if(T->lchild==NULL&&M->rchild!=NULL)
		    c=0;
		    else if(T->lchild!=NULL&&M->rchild==NULL)
		    c=0;
		    else ;
		    if(T->rchild!=NULL&&M->lchild!=NULL)
		    {
			    compare(T->rchild,M->lchild,c);
		    }
		    else if(T->rchild==NULL&&M->lchild!=NULL)
		    c=0;
		    else if(T->rchild!=NULL&&M->lchild==NULL)
		    c=0;
		    else;
	    }
			
}
int main()
{
	btree *B,*A;
	cout<<"Enter root node: ";
    char ch;
    int c=1;
    cin>>ch;
    A=new(btree);
    A->data=ch;
    A->rchild=NULL;
    A->lchild=NULL;
    input(A,ch);
    display(A);
    cout<<"\nEnter root node: ";
    cin>>ch;
    B=new(btree);
    B->data=ch;
    B->rchild=NULL;
    B->lchild=NULL;
    input(B,ch);
    display(B);
    cout<<endl;
    compare(A,B,c);
    if(c==0)
    cout<<"Dis-similar trees!";
    else 
    cout<<"Similar trees! ";
    c=1;
    	compare1(A->lchild,B->rchild,c);
    	if(c!=0)
    	compare1(A->rchild,B->lchild,c);
    	if(c=0)
    	cout<<"\nNot Mirror Similar!";
    	else
    	cout<<"\nMirror similar trees!";
    return 0;
}
