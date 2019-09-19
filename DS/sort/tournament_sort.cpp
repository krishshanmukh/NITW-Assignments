#include<iostream>
using namespace std;

int i=0;

struct bintree
{
	int data;
	bintree *lchild;
	bintree *rchild;
	int h;
};

int create(bintree* &T,int A[],int k,int h)
{
	if(T==NULL)
	{
		T=new(bintree);
		T->lchild=NULL;
		T->data=-1;
		T->rchild=NULL;
		T->h=h;
	}
	if(h==0)
	{
		if(i<k)
		T->data=A[i++];
		else;
	}
	else
	{
		create(T->lchild,A,k,h-1);
		create(T->rchild,A,k,h-1);
	}
}

int compare(bintree *T,bintree *M)
{
	if(T!=NULL&M!=NULL)
	{
		if(T->data>=M->data)
		return 1;
		else
		return 0;
	}
	else
	return 1;
}

int sort(bintree *T)
{
	if(T->lchild->lchild!=NULL)
	sort(T->lchild);
	if(T->rchild->rchild!=NULL)
	sort(T->rchild);
    if(compare(T->lchild,T->rchild))
    T->data=T->lchild->data;
	else
	T->data=T->rchild->data;
	return T->data;
}

void del(bintree *T,int x)
{
	if(T!=NULL)
	{
		if(T->data==x)
		T->data=-1;
		del(T->lchild,x);
		del(T->rchild,x);
	}
}
int calheight(int x)
{
	int i=-1;
	while(x!=0)
	{
		x/=2;
		i++;
	}
	return i;
}

void display(bintree *T)
{
	if(T!=NULL)
	{
		if(T->lchild==NULL&&T->rchild==NULL)
		cout<<T->data<<" ";
		else
		{
		    display(T->lchild);
		    display(T->rchild);
		}
	}
}

int main()
{
	int A[20],elt,h,h1;
	bintree *T=NULL;
	cout<<"Enter elts: ";
	int k=0;
	cin>>elt;
	while(elt!=-1)
	{
		A[k++]=elt;
		cin>>elt;
	}
	h=calheight(k);
	h1=calheight(k-1);
	if(h==h1)
	h++;
	create(T,A,k,h);
	display(T);
	cout<<endl;
	for(int j=0;j<k;j++)
	{
	   elt=sort(T);
	   cout<<elt<<" ";
	   del(T,elt);
    }
    return 0;
}
