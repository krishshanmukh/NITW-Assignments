#include<iostream>
using namespace std;
int c=0;
struct pnode
{
	int co;
	int exp;
	pnode *next;
};
void del(pnode* &C) 
{
	pnode *T;
	T=C->next;
	C->next=T->next;
	T->next=NULL;
	delete(T);
}
pnode* sort(pnode* L)
{
	pnode *C;
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
			if(L->exp<L->next->exp)
			{
				int t=L->exp;
				L->exp=L->next->exp;
				L->next->exp=t;
				t=L->co;
				L->co=L->next->co;
				L->next->co=t;
			}
			L=L->next;
		}
	}
	return C;
}
void addend(pnode *A,int x,int y)
{

        while(A->next!=NULL)
	    A=A->next;
	    A->next=new(pnode);
	    A=A->next;
	A->co=x;
	A->exp=y;
	A->next=NULL;
}
void display(pnode *A)
{
	if(A!=NULL)
	{
		cout<<A->co<<"X("<<A->exp<<")"<<"  ";
		display(A->next);
	}
}
pnode* app(pnode *A,pnode *B)
{
	pnode *T=new(pnode);
	T->co=A->co;
	T->exp=A->exp;
	T->next=NULL;
	A=A->next;
	while(A!=NULL)
    {
    	addend(T,A->co,A->exp);
    	A=A->next;
    }
    while(B!=NULL)
    {
    	addend(T,B->co,B->exp);
    	B=B->next;
    }
    return T;
}
pnode* app1(pnode *A,pnode *B)
{
	pnode *T=new(pnode);
	T->co=A->co;
	T->exp=A->exp;
	T->next=NULL;
	A=A->next;
	while(A!=NULL)
    {
    	addend(T,A->co,A->exp);
    	A=A->next;
    }
    while(B!=NULL)
    {
    	int b = (-1)*(B->co);
    	addend(T,b,B->exp);
    	B=B->next;
    }
    return T;
}
pnode* add(pnode *C)
{
	pnode *T;
	T=C;
	while(C->next!=NULL&&C!=NULL)
	{
		if(C->exp==C->next->exp)
		{
			C->co = C->co + C->next->co;
			del(C);
		}
		else
		C=C->next;
	}
	return T;
}
pnode* multiply(pnode *A,pnode *B,pnode *C)
{
	pnode *T2,*T1;
	T2=B;
	C=NULL;
	int c=1;
	while(A!=NULL)
	{
		B=T2;
		while(B!=NULL)
		{
			if(c!=1)
		    addend(C,(A->co*B->co),(A->exp+B->exp));
		    else
		    {
		    	C=new(pnode);
		    	T1=C;
		    	c++;
		    	C->next=NULL;
		    	C->co=A->co*B->co;
		    	C->exp=A->exp+B->exp;
		    }
			B=B->next;	
		}
		A=A->next;
	}
	return T1;
}
int main()
{
	pnode *A,*B,*C,*C1,*C2;
	cout<<"polynomial 1\nEnter coeff and power : ";
	int co,exp;
	cin>>co>>exp;
	A=new(pnode);
	A->co=co;
	A->exp=exp;
	A->next=NULL;
	cout<<"Enter remaining coeffs and powers: (coeff of 0 to exit) ";
	cin>>co;
	while(co!=0)
	{
		cin>>exp;
		addend(A,co,exp);
		cout<<"Coeff and exp : ";
		cin>>co;
	}
	B=new(pnode);
	cout<<"polynomial 2\nEnter coeff and power : ";
	cin>>co>>exp;
	B->co=co;
	B->exp=exp;
	B->next=NULL;
	cout<<"Enter remaining coeffs and powers: (coeff of 0 to exit) ";
	cin>>co;
	while(co!=0)
	{
		cin>>exp;
		addend(B,co,exp);
		cout<<"Coeff and exp : ";
		cin>>co;
	}
	C=app(A,B);
	C=sort(C);
	C=add(C);
	display(C);
    C1=app1(A,B);
    C1=sort(C1);
	C1=add(C1);
	cout<<endl;
	display(C1);
    C2=multiply(A,B,C2);
	C2=sort(C2);
	C2=add(C2);
	cout<<endl;
	display(C2);
	return 0;
}
