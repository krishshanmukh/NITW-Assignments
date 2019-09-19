#include<iostream>
using namespace std;

struct dlnode
{
	dlnode *left;
	char data;
	dlnode *right;
};

int rec_palin(dlnode *D1,dlnode *D2)
{
	if(D1!=D2&&D1->right!=D2->left)
	{
		if(D1->data==D2->data)
		return rec_palin(D1->right,D2->left);
		else
		return 0;
	}
	else if(D1->data==D2->data)
	return 1;
	else
	return 0;
}

int main()
{
	dlnode *D1,*D2;
	D1=new(dlnode);
	D2=D1;
	cout<<"Enter first elt: ";
	char c;
	cin>>c;
	D2->data=c;
	D2->left=NULL;
	D2->right=NULL;
	cout<<"Enter remng elts (0 to stop) : ";
	cin>>c;
	while(c!='0')
	{
		D2->right=new(dlnode);
		D2->right->left=D2;
		D2=D2->right;
		D2->right;
		D2->right=NULL;
		D2->data=c;
		cin>>c;
	}
	c=rec_palin(D1,D2);
	if(c)
	cout<<"It is a palindrome" ;
	else
	cout<<"Not a palindrome";
	return 0;
}
