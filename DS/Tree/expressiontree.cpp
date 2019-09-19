#include<iostream>
using namespace std;

struct exptree
{
	exptree *lchild;
	int tag;
	union
	{
		int operand;
		char operate;
	}data;
	exptree *rchild;
};

class stack
{
	int top;
	exptree *elts[30];
	int size;
	int tag[30];
    public :
		void push(exptree *T);
		exptree* pop();
		void display();
		stack()
		{
			top=-1;
		}
};

exptree* stack :: pop()
{
	if(top>=0)
	return elts[top--];
	else
	cout<<"Stack is empty";
}

void stack :: push(exptree *T)
{
	if(top<30)
	elts[++top]=T;
}

void stack :: display()
{
	for(int i=0;i<=top;i++)
	{
		if(elts[i]->tag==1)
		cout<<elts[i]->data.operand<<" ";
		else
		cout<<elts[i]->data.operate<<" ";
	}
}

void display(exptree *T)
{
	if(T!=NULL)
	{
		display(T->lchild);
		if(T->tag==1)
		cout<<T->data.operand;
		else
		cout<<T->data.operate;
		display(T->rchild);
	}
}

int calculate(char op,int a,int b)
{
	if(op=='*')
	return a*b;
	else if(op=='/')
	return a/b;
	else if(op=='-')
	return a-b;
	else
	return a+b;
}

int evalexp(exptree *T)
{
	int a,b;
	if(T->tag==2)
	{
		a=evalexp(T->lchild);
		b=evalexp(T->rchild);
		return (calculate(T->data.operate,a,b));
	}
	else
	return T->data.operand;

}

int main()
{
	char ch[50];
	stack s;
	cout<<"Enter the postfix expression: ";
	cin.getline(ch,30,'\n');
	exptree *T,*E;
	int i=0;
	while(ch[i]!='\0')
	{
		T=new(exptree);
		T->lchild=NULL;
		T->rchild=NULL;
		if(ch[i]!='+'&&ch[i]!='/'&&ch[i]!='*'&&ch[i]!='-')
		{
			T->tag=1;
			T->data.operand=0;
			while(ch[i]!=' ')//to store integers greater than 10
			{
				T->data.operand=T->data.operand*10+(ch[i]-'0');
				i++;
			}
			s.push(T);
		}
		else
		{
			exptree *A,*B;//when you encounter an operator, pop last 2 elts and assign them as its left & right
			A=s.pop();
			B=s.pop();
			T->rchild=A;
			T->lchild=B;
			T->tag=2;
			T->data.operate=ch[i];
			s.push(T);
			i++;
		}
		while(ch[i]==' ')//to remove white spaces
		i++;
	}
	T=s.pop();
	display(T);
	cout<<"\nResult is : "<<evalexp(T);
	return 0;
}
