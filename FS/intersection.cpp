#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream o;
	ifstream i1,i2;
	int a[20],b[20],c[20],d=0,e=0,f=0,p;
	i1.open("d1.txt");
	i2.open("d2.txt");
	o.open("intersect.txt");
	do
	{
		i1>>p;
		a[d]=p;
		d++;
	}while(!i1.eof());
		do
	{
		i2>>p;
		b[e]=p;
		e++;
	}while(!i2.eof());
	for(int j=0;j<d;j++)
	{
		for(int k=0;k<e;k++)
		{
			if(a[j]==b[k])
			{
				c[f]=a[j];
				f++;
			}
		}
	}
	for(int j=0;j<f-1;j++)
	{
		for(int k=j+1;k<f;k++)
		{
			if(c[j]==c[k])
			{
				for(int l=k;l<f;l++)
				c[l]=c[l+1];
				f--;
				k--;
			}
		}
	}
		for(int j=0;j<f;j++)
	o<<c[j]<<" ";
	o.close();
	i1.close();
	i2.close();
	return 0;
}
