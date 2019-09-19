#include<iostream>
#include<fstream>
using namespace std;

int find_min(int A[],int size)
{
	int min=A[0],index=0;
	for(int i=1;i<size;i++)
	{
		if((A[i]<min&&A[i]!=-1)||min==-1)
		{
			min=A[i];
			index=i;
		}
	}
	return index;
}

void sort(int A[],int size)
{
	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
	if(A[j]>A[i])
	swap(A[j],A[i]);
}

int main()
{
	char file[][6]={"1.txt","2.txt","3.txt","4.txt"};
	int arr[4],size,count=0,i,ctr=0,fileno[3];
	ofstream fout[3],out;
	for(i=0;i<3;i++)
	fout[i].open(file[i]);
	ifstream in("data.txt"),fin[3];
	for(i=0;i<3;i++)
	in>>arr[i];
	while(!in.eof())
	{
		sort(arr,3);
		for(i=0;i<3;i++)
		fout[count]<<arr[i]<<" ";
		fout[count]<<"-1"<<endl;
		ctr++;
		if(ctr==7)
		count=1;
		else if(ctr==13)
		count=2;
		for(i=0;i<3;i++)
		in>>arr[i];
	}
	in.close();
	for(i=0;i<3;i++)
	fout[i].close();
	for(i=0;i<3;i++)
	{
		fin[i].open(file[i]);
		fin[i]>>arr[i];
		fileno[i]=i;
	}
	int choice=1,index,end=5,his=3;out.open(file[3]);
	while(choice)
	{
		while(end==5)
		{
			while(arr[0]!=-1||arr[1]!=-1||arr[2]!=-1)
			{
				index=find_min(arr,3);
				out<<arr[index]<<" ";
				fin[index]>>arr[index];
			}
			out<<"-1"<<endl;
			for(i=0;i<3;i++)
			fin[i]>>arr[i];
			for(i=0;i<3;i++)
			if(arr[i]==-1)
			{
				end=i;
				break;
			}
		}
		for(i=0;i<3;i++)
		if(fin[i].eof())
		choice++;
		if(choice==4)
		break;
		fin[end].close();
		out.close();
		out.open(file[fileno[end]]);
		fin[end].open(file[his]);
		swap(fileno[end],his);
		fin[end]>>arr[end];
		choice=1;
		end=5;
	}
	for(i=0;i<3;i++)
		fin[i].close();
		out.close();
	return 0;
}
