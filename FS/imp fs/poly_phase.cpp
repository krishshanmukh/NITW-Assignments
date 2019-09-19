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

int open(ifstream &in1,ifstream &in2,ifstream &in3,int i,int his)
{
	if(i==0)
	{
		in1.close();
		if(his==1)
		in1.open("data1.txt");
		else if(his==2)
		in1.open("data2.txt");
		else if(his==3)
		in1.open("data3.txt");
		else
		in1.open("data4.txt");
	}
	else if(i==1)
	{
		in2.close();
		if(his==1)
		in2.open("data1.txt");
		else if(his==2)
		in2.open("data2.txt");
		else if(his==3)
		in2.open("data3.txt");
		else
		in2.open("data4.txt");
	}
	else
	{
		in3.close();
		if(his==1)
		in3.open("data1.txt");
		else if(his==2)
		in3.open("data2.txt");
		else if(his==3)
		in3.open("data3.txt");
		else
		in3.open("data4.txt");
	}
}

int main()
{   
	ofstream out,out1("data1.txt"),out2("data2.txt"),out3("data3.txt"),out4("data4.txt");
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
	ifstream in1("data.txt"),in2,in3;
	s=0;
	in1>>e;
	while(!in1.eof())
	{
	    arr[s++]=e;
		if(s==size)
		{
			sort(arr,s);
			if(count<=7)
			store(out1,arr,s);
			else if (count<=13)
			store(out2,arr,s);
			else
			store(out3,arr,s);
			s=0;
			count++;
		}
		in1>>e;	
	}
	if(s!=0)
	{
		store(out3,arr,s);
	}
	in1.close();
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	in1.open("data1.txt");arr1[0]=1;
	in2.open("data2.txt");arr1[1]=2;
	in3.open("data3.txt");arr1[2]=3;
	out.open("data4.txt");his=4;
	in1>>arr[0];
	in2>>arr[1];
	in3>>arr[2];
	s=size;
	s=0;
    while(s==0)
	{
		count=1;
	    if(ctr==4)
	    {
	    	out.close();
	        arr1[i]=his;
	        open(in1,in2,in3,i,his);
	        if(i==0)
	        in1>>arr[0];
	        else if(i==1)
	        in2>>arr[1];
	        else 
	        in3>>arr[2];
	        out.open("data4.txt");his=4;
	    }
	    else if (ctr==3)
	    {
	        out.close();
	        arr1[i]=his;
	        open(in1,in2,in3,i,his);
	        if(i==0)
	        in1>>arr[0];
	        else if(i==1)
	        in2>>arr[1];
	        else 
	        in3>>arr[2];
	    	out.open("data3.txt");his=3;
	    }
	    else if (ctr==2)
	    {
	        out.close();
	        arr1[i]=his;
	        open(in1,in2,in3,i,his);
	        if(i==0)
	        in1>>arr[0];
	        else if(i==1)
	        in2>>arr[1];
	        else 
	        in3>>arr[2];
	    	out.open("data2.txt");his=2;
	    }
	    else if(ctr==1)
	    {
	    	out.close();
	        arr1[i]=his;
	        open(in1,in2,in3,i,his);
	        if(i==0)
	        in1>>arr[0];
	        else if(i==1)
	        in2>>arr[1];
	        else 
	        in3>>arr[2];
	    	out.open("data1.txt");his=1;
	    }
	    else;
		while(!in1.eof()&&!in3.eof()&&!in2.eof())
		{
			while (!is_empty(arr,size))
	    	{                          
		    	i=find_min(arr,size);
			    out<<arr[i]<<" ";
			    if(i==0)
		    	in1>>arr[0];
		    	else if(i==1)
		    	in2>>arr[1];
		    	else
		    	in3>>arr[2];
		    }
		    out<<"-1"<<endl;
		    in1>>arr[0];
			in2>>arr[1];
			in3>>arr[2];
		}
		if(in1.eof())
		{
		    ctr=arr1[0];
		    i=0;
		}
		else if(in2.eof())
		{
			ctr=arr1[1];
			i=1;
		}
		else
		{
			ctr=arr1[2];
		    i=2;
		}
		if(in1.eof()&&in2.eof()&&in3.eof())
		s=1;
	}
	return 0;
}
