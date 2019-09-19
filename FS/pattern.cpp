#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream o;
	ifstream i;
	i.open("data.txt");
	o.open("pattern.txt");
	char ch,a[26],m[26],c[26][20];
	int b[26],e,d=0,j,k,l,n;
    i>>ch;
	while(!i.eof())
	{
		a[d]=ch;
	    i>>ch;
		cout<<a[d];
     	d++;
	}
n=d;
	for(j=0;j<d;j++)
	{
		m[j]=a[j];
		cout<<m[j];
	}
	for(j=0;j<d-1;j++)
	{	
		for(k=j+1;k<d;k++)
		{
			if(a[j]==a[k])
			{
				for(l=k;l<d-1;l++)
				{
				a[l]=a[l+1];
			    }
				d--;
				k--;
			}
		}
	}
	for(j=0;j<d;j++)
	{
		b[j]=0;
		for(k=0;k<n;k++)
		{
			if(a[j]==m[k])
			b[j]++;
		}
		cout<<b[j]<<" ";
	}
	cout<<endl;
	e=b[0];
	for(j=1;j<d;j++)
	{
		if(b[j]>e)
		e=b[j];
	}
	for(j=0;j<d;j++)
	{
		for(k=1;k<=e;k++)
		{
			if(b[j]==k)
			{
				for(l=0;l<e-k;l++)
				c[j][l]=' ';
				for(l=e-k;l<e;l++)
				c[j][l]='*';
			}
		}
	}
	for(j=0;j<e;j++)
	{
		for(k=0;k<d;k++)
		cout<<c[k][j]<<" ";
		cout<<endl;
	}
	for(j=0;j<d;j++)
	cout<<a[j]<<" ";
	o.close();
	i.close();
	return 0;
}
