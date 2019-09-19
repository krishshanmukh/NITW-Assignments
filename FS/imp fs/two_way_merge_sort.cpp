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

int main()
{
	ofstream out("data.txt"),out3("data1.txt"),out4("data2.txt");
	cout<<"Enter the numnbers to be sorted: ";
	int e,s,a,b,no=0;
	cin>>e;
	do{
		no++;
		out<<e<< " ";
		cin>>e;
	}while(e!=-1);
	cout<<no;
	out.close();
	cout<<"Enter the size of the array: ";
	cin>>s;
	const int size=s;
	int arr[size],count=1,ctr=1;
	ifstream in1("data.txt"),in2;
	s=0;
	in1>>e;
	while(!in1.eof())
	{
	    arr[s++]=e;
		if(s==size)
		{
			sort(arr,s);
			if(count++%2==1)
			store(out3,arr,s);
			else
			{
				store(out4,arr,s);
			}
			s=0;
		}
		in1>>e;	
	}
	if(s!=0)
	{
		sort(arr,s);	
		if(count++%2==1)
		store(out3,arr,s);
		else
		{
			store(out4,arr,s);
		}
		s=0;
	}
	in1.close();
	out3.close();
	out4.close();
	s=size;
while(s<no)
	{
		count=1;
	    s=0;
	    if(ctr++%2==1)
	    {
	        in1.open("data1.txt");
	        in2.open("data2.txt");
	        out3.open("data3.txt");
	        out4.open("data4.txt");
	    }
	    else
	    {
	        in1.open("data3.txt");
	    	in2.open("data4.txt");
	    	out3.open("data1.txt");
	    	out4.open("data2.txt");
	    }
    	in1>>a;
	    in2>>b;
    	while(!in1.eof()||!in2.eof())
	    {
		    if(a>b)
    		{
	    		if(count%2==1)
		    	{
		    		if(b!=-1)
		    		{
			            out3<<b<<" ";
			            s++;
			        }
	    		    if(b!=-1&&!in2.eof())
		    	    in2>>b;
			        else
			        {
				        while(a!=-1&&!in1.eof())
				        {
				    	    out3<<a<< " ";
    					    s++;
		    			    in1>>a;
			    	    }
				         out3<<"-1"<<endl;
    				     in1>>a;in2>>b;
	    			     count++;
		    	    }
		        }
    		    else if(s!=no)
	    	    {
	    	    	if(b!=-1)
		        	out4<<b<<" ";
			        if(b!=-1&&!in2.eof())
    			    in2>>b;
	    		    else
		    	    {
			    	    while(a!=-1&&!in1.eof())
				        {
				        	out4<<a<< " ";
	    				    in1>>a;
		    		    }
			    	     out4<<"-1"<<endl;
				         in1>>a;in2>>b;
    				     count++;
	    		    }
		        }
	        }
    	    else
	        {
	        	if(count%2==1)
			    {
			    	if(a!=-1)
			    	{
			            out3<<a<<" ";
			            s++;
			        }
	    		    if(a!=-1&&!in1.eof())
		    	    in1>>a;
			        else
			        {
    				    while(b!=-1&&!in2.eof())
	    			    {
	    			    	s++;
		    		    	out3<<b<< " ";
					        in2>>b;
    				    }    
		    		     out3<<"-1"<<endl;
			    	     in1>>a;in2>>b;
				         count++;
    			    }    
	    	    }
		        else if(s!=no)
		        {
		        	if(a!=-1)
		    	    out4<<a<<" ";
	    		    if(a!=-1&&!in1.eof())
		    	    in1>>a;
			        else
			        {
    				    while(b!=-1&&!in2.eof())
	    			    {
		    		    	out4<<b<< " ";
					        in2>>b;
    				    }    
	    			     out4<<"-1"<<endl;
			      	     in1>>a;in2>>b;
				         count++;
    			    }
	    	    }
	        }
	    }
	    out3.close();
	    out4.close();
    	in1.close();
	    in2.close();
	    cout<<s<<" ";
	}
	return 0;
}
