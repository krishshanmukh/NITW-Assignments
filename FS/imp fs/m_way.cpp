#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

void sort (int arr[],int s)
{
	for(int i=0;i<s;i++)
	    for(int j=0;j<s-i-1;j++)
	    if(arr[j]>arr[j+1])
	    {
	    	int t=arr[j];
	    	arr[j]=arr[j+1];
	    	arr[j+1]=t;
		}
}

void store(ofstream &out,int arr[],int s)
{
	for(int i=0;i<s;i++)
	out<<" "<<arr[i];
	out<<" "<<"-1"<<endl;
}

int find_min(int arr[],int size)
{
	int min=0;
	int j;
	for(int i=0;i<size;i++)
	{
		if((arr[i]<=min||min==0)&&arr[i]!=-1)
		{
		    min=arr[i];
		    j=i;
		}
	}
	return j;
}

int is_empty(int arr[],int size)
{
	int i;
	for(i=0;i<size;i++)
	if(arr[i]!=-1)
	break;
	if(i==size)
	return 1;
	else return 0;
}

int main()
{   
	int e,s,no=0,m;
    cout<<"Enter value of m: ";
    cin>>m;
	const int size=m;
	int arr[size],count=0,ctr=1;
	ofstream fout[size];
	ifstream fin[size],in("data.txt");
	s=0;
	char file[2*size][10];
	for(int i=1;i<=2*size;i++)
	{
		itoa(i,file[i-1],10);
		strcat(file[i-1],".txt");
	}
	in>>e;
	for(int i=0;i<m;i++)
	fout[i].open(file[2*i]);
	while(!in.eof())
	{
	    arr[s++]=e;
		if(s==size)
		{
			sort(arr,s);
			store(fout[count],arr,s);
			s=0;
			count++;
			if(count==m)
			count=0;
		}
		no++;
		in>>e;	
	}
	in.close();
	if(s!=0)
	{
		sort(arr,s);
		store(fout[count],arr,s);
	}
	for(int i=0;i<m;i++)
	fout[i].close();	
    while(s<no)
	{
		if(ctr++%2==1)
		for(int i=0;i<m;i++)
		{
			fout[i].open(file[2*i+1]);
			fin[i].open(file[2*i]);
			fin[i]>>arr[i];
		}
		else
		for(int i=0;i<m;i++)
		{
		    fout[i].open(file[2*i]);
			fin[i].open(file[2*i+1]);
			fin[i]>>arr[i];
		}
		s=0;
		count=0;
		e=1;
		while(e)
		{
			e=0;
			while (!is_empty(arr,size))
	    	{   
			    int j;                       
		    	j=find_min(arr,size);
			    fout[count]<<arr[j]<<" ";
			    fin[j]>>arr[j];
			    if(count==0)
			    s++;
		    }
		    fout[count++]<<"-1"<<endl;
		    for(int i=0;i<m;i++)
	    	{
	    		if(!fin[i].eof())
	    		{
				    fin[i]>>arr[i];
				    e=1;
				}
			}
			if(count==m)
			count=0;
		}
		for(int i=0;i<m;i++)
		{
			fout[i].close();
			fin[i].close();
		}
	}
	return 0;
}
