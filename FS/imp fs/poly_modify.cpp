#include<iostream>
#include<fstream>
using namespace std;

void sort (int arr[],int s)
{
	for(int i=0;i<s;i++)
	{
	    for(int j=0;j<s-i-1;j++)
	    if(arr[j]>arr[j+1])
	    {
	    	int t=arr[j];
	    	arr[j]=arr[j+1];
	    	arr[j+1]=t;
	    }
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

int open(ifstream in[],int i,int his)
{
	in[i].close();
	if(his==1)
	in[i].open("data1.txt");
	else if(his==2)
	in[i].open("data2.txt");
	else if(his==3)
	in[i].open("data3.txt");
	else
	in[i].open("data4.txt");
}

int main()
{   
	ofstream out[3],out1;
	out[0].open("data1.txt");
	out[1].open("data2.txt");
	out[2].open("data3.txt");
	//cout<<"Enter the numnbers to be sorted: ";
	int e,s,a,b,no=0;
	//cin>>e;
	//do{
//		no++;
//		out<<e<< " ";
//		cin>>e;
//	}while(e!=-1);
//	cout<<no;
	const int size=3;
	int arr[size],arr1[size],count=1,ctr=5,i=0,his=4;
	ifstream in[3];in[0].open("data.txt");
	s=0;
	in[0]>>e;
	while(!in[0].eof())
	{
	    arr[s++]=e;
		if(s==size)
		{
			sort(arr,s);
			if(count<=7)
			store(out[0],arr,s);
			else if (count<=13)
			store(out[1],arr,s);
			else
			store(out[2],arr,s);
			s=0;
			count++;
		}
		in[0]>>e;	
	}
	if(s!=0)
	{
		store(out[2],arr,s);
	}
	in[0].close();
	out[0].close();
	out[1].close();
	out[2].close();
	in[0].open("data1.txt");arr1[0]=1;
	in[1].open("data2.txt");arr1[1]=2;
	in[2].open("data3.txt");arr1[2]=3;
	out1.open("data4.txt");his=4;
	in[0]>>arr[0];
	in[1]>>arr[1];
	in[2]>>arr[2];
	s=0;
    while(s==0)
	{
		count=1;
		if(ctr!=5)
		{
			
	    	out1.close();
	        arr1[i]=his;
	        open(in,i,his);
	        in[i]>>arr[i];
		}
	    if(ctr==4)
	    {
	        out1.open("data4.txt");his=4;
	    }
	    else if (ctr==3)
	    {
	    	out1.open("data3.txt");his=3;
		}
	    else if (ctr==2)
	    {
	    	out1.open("data2.txt");his=2;
	    }
	    else if(ctr==1)
	    {
	    	out1.open("data1.txt");his=1;
	    }
	    else;
		while(!in[0].eof()&&!in[1].eof()&&!in[2].eof())
		{
			while (!is_empty(arr,size))
	    	{                          
		    	i=find_min(arr,size);
			    out1<<arr[i]<<" ";
		    	in[i]>>arr[i];
		    }
		    out1<<"-1"<<endl;
		    in[0]>>arr[0];
			in[1]>>arr[1];
			in[2]>>arr[2];
		}
		for(int j=0;j<4;j++)
		if(in[j].eof())
		{
		    ctr=arr1[j];
		    i=j;break;
		}
		if(in[0].eof()&&in[1].eof()&&in[2].eof())
		s=1;
	}
	return 0;
}
