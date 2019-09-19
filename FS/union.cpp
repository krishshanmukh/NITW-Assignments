#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream o;
	ifstream i1,i2;
	int a[100],i=0,b;
	i1.open("d1.txt");
	i2.open("d2.txt");
	o.open("union.txt");
	do
	{
		i1>>b;
		a[i]=b;
		i++;
	}while(!i1.eof());
	do
	{
		i2>>b;
		a[i]=b;
		i++;
	}while(!i2.eof());
	for(int j=0;j<i-1;j++)
	{
		for(int k=j+1;k<i;k++)
		{
			if(a[j]==a[k])
			{
				for(int l=k;l<i;l++)
				a[l]=a[l+1];
				i--;
				k--;
			}
		}
	}
	for(int j=0;j<i;j++)
	o<<a[j]<<" ";
	o.close();
	i1.close();
	i2.close();
	return 0;
}
