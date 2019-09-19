#include<iostream>
using namespace std;

int partition(int A[],int low,int h)
{
	int p=A[low],l=low+1;
	while(l<=h)
	{
		while(A[l]<p)
		l++;
		while(A[h]>p)
		h--;
		if(l<h)
		{
			swap(A[l],A[h]);
		}
	}
	swap(A[low],A[h]);
	return h;
}

void quick_sort(int A[],int low,int high)
{
	if(low<high)
	{
		int j=partition(A,low,high);
		quick_sort(A,low,j-1);
		quick_sort(A,j+1,high);
	}
}

int input(int A[])
{
	cout<<"Enter elts: ";
	int elt,size=0;
	cin>>elt;
	while(elt!=-1)
	{
		A[size++]=elt;
		cin>>elt;
	}
	return size;
}

void display(int A[],int size)
{
	for(int i=0;i<size;i++)
	cout<<A[i]<<" ";
}

int main()
{
	int A[20],size;
	size=input(A);
	quick_sort(A,0,size-1);
	display(A,size);
	return 0;
}
