#include<iostream>
#include<cstring>
using namespace std;

struct btnode
{
	btnode *lchild;
	int wt;
	char ch;
	btnode *rchild;
};

struct member
{
	btnode *T;
};

int find_min(member M[],int size)
{
	int min=0,index;
	for(int i=0;i<size;i++)
	{
		if(M[i].T!=NULL&&(min==0||min>M[i].T->wt))
		{
			index=i;
			min=M[i].T->wt;
		}
	}
	cout<<index<<" ";
	return index;
}

btnode* create_btnode(btnode *A,btnode *B)
{
	btnode *T=new(btnode);
	T->lchild=A;
	T->rchild=B;
	T->wt=A->wt+B->wt;
	T->ch='@';
	return T;
}

void display(btnode *T,char ch[],int i,char c)
{
	if(T!=NULL)
	{
		if(i!=-1)
		ch[i]=c;
		if(T->lchild!=NULL)
		{
			display(T->lchild,ch,i+1,'0');
			display(T->rchild,ch,i+1,'1');
		}
		else
		{
			ch[i+1]='\0';
			cout<<endl<<T->ch<<" - "<<ch;
		}
	}
}


int main()
{
	member M[10];
	btnode *T,*A,*B;
	cout<<"Enter number: ";
	int no,i=0,index;
	char ch;
	cin>>no;
	while(no!=-1)
	{
		cout<<"Enter character: ";
		cin>>ch;
		M[i].T=new(btnode);
		M[i].T->lchild=NULL;
		M[i].T->rchild=NULL;
		M[i].T->wt=no;
		M[i++].T->ch=ch;
		cout<<"Enter number: ";
		cin>>no;
	}
	no=1;
	while(no++!=i)
	{
		index=find_min(M,i);
		A=M[index].T;
		M[index].T=NULL;
		index=find_min(M,i);
		B=M[index].T;
		T=create_btnode(A,B);
		M[index].T=T;
	}
	char code[10];
	display(T,code,-1,0);
	return 0;
}
