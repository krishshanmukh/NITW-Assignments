#include<iostream>
using namespace std;
struct node
{
	int data;
	node *next;
};
void del(node* L,int x)
{
	node *T;
	while(L->next->data!=x)
	L=L->next;
	T=L->next;
	L->next=L->next->next;
	delete(T);
}
node* append(node *L1,node *L2, node *L)
{
	L=L1;
	while(L1->next!=NULL)
	L1=L1->next;
	L1->next=L2;
	return L;
}
node* unio(node *L,node *M,node *T)
{
	T=L;
	while(M!=NULL)
	{
		L=T;
		del(L,M->data);
		M=M->next;
	}
	return T;
}
void print(node *L)
{
	if(L!=NULL)
	{
		cout<<L->data<<"\t";
		print(L->next);
	}
}
node* sort(node* L,node *C)
{
	C=L;
	int s=0;
	while(L!=NULL)
	{
	L=L->next;s++;}
	for(int i=0;i<s-1;i++)
	{
		L=C;
		for(int j=i+1;j<s;j++)
		{
			if(L->data>L->next->data)
			{
				int t=L->data;
				L->data=L->next->data;
				L->next->data=t;
			}
			L=L->next;
		}
	}
	return C;
}
node* intersect(node *L,node *M,node *C)
{
	node *A,*B,*D;int c=0;
	A=M;
	while(L!=NULL)
	{
		M=A;
		while(M!=NULL)
		{
			if(M->data==L->data)
		    {
		    	c++;
			    B=new(node);
			    if(c==1)
			    {C=B;D=C;}
			    else
			    {
			    C->next=B;C=C->next;}
			    B->data=L->data;
			    B->next=NULL;break;
		    }M=M->next;
		}L=L->next;
	}
	return D;
}
int main()
{
	node *L,*M,*A,*B,*I,*U,*I1,*S;
	int c;
	cout<<"Enter first elt of ll 1 : ";
	L=new(node);
	M=new(node);
	A=L;B=M;
	cin>>c;
	L->data=c;
	L->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>c;
	while(c!=0)
	{
		I=new(node);
		I->data=c;
		I->next=NULL;
		L->next=I;
		L=L->next;
		cin>>c;
	}
	cout<<"Enter first elt of ll 2 : ";
	cin>>c;
	M->data=c;
	M->next=NULL;
	cout<<"Enter remaining elts :(0 to stop) ";
	cin>>c;
	while(c!=0)
	{
		I=new(node);
		I->data=c;
		I->next=NULL;
		M->next=I;
		M=M->next;
		cin>>c;
	}
	L=A;
	M=B;
	I=intersect(A,B,I);
	I1=I;
	cout<<"Intersect:  ";
	print(I);
	A=L;B=M;
	cout<<endl;
	L=append(A,B,L);
	U=unio(L,I1,U);
	cout<<"Union:  ";
	L=U;
	print(U);
	S=sort(L,S);
	cout<<endl<<"Sort:  ";
	print(S);
	return 0;
}
