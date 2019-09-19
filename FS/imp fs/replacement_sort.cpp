#include<iostream>
#include<fstream>
using namespace std;

int findelt(int arr[],int size,int elt)
{
	int min=0;
	for(int i=0;i<size;i++)
	{
		if(elt<arr[i])
		{
			if(min==0)
			min=arr[i];
			else if(arr[i]<min)
			min=arr[i];
		}
	}
	if(min!=0)
	{
		for(int i=0;i<size;i++)
		{
			if(arr[i]==min)
			{
				for(int j=i;j<size-1;j++)
				arr[j]=arr[j+1];
			}
		}
	}
	return  min;
}

int getmin(int arr[],int size)
{
	int min=arr[0];
	for(int i=0;i<size;i++)
	{
		if(min>arr[i])
			min=arr[i];
	}
	if(min!=0)
	{
		for(int i=0;i<size;i++)
		{
			if(arr[i]==min)
			{
				for(int j=i;j<size-1;j++)
				arr[j]=arr[j+1];
			}
		}
	}
	return min;
}

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
	int arr[size],count=1,min,ctr=1;
	ifstream in1("data.txt"),in2;
	s=0;
	in1>>e;
	while(!in1.eof())
	{
	    arr[s++]=e;
		while(s==size&&!in1.eof())
		{
			min=getmin(arr,size);
			if(count%2==1)
			out3<<" "<<min;
			else
			out4<<" "<<min;
			in1>>e;
			while(!in1.eof())
			{
				arr[size-1]=e;
				min=findelt(arr,size,min); //to check if least value is greater than last elt in the file!
				if(min!=0)
				{
				     if(count%2==1)
			         out3<<" "<<min;
		          	 else
         			 out4<<" "<<min;
					 in1>>e;	
				}
				else
				{
					if(count%2==1)
					out3<<" "<<"-1"<<endl;
					else
					out4<<" "<<"-1"<<endl;
					count++;
					break;
				}
			}
		}
		in1>>e;
	}
		if(count++%2==1)
		{
			sort(arr,s);
			for(int i=0;i<s-1;i++)
			out3<<" "<<arr[i];
			out3<<" "<<"-1"<<endl;
		}
		else
		{
			sort(arr,s);
			for(int i=0;i<s-1;i++)
			out4<<" "<<arr[i];
			out4<<" "<<"-1"<<endl;
		}
	out3.close();
	out4.close();
	in1.close();
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
			    	    if(s!=no)
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
		    		    if(s!=no)
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
						if(s!=no)    
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
    				    if(s!=no)
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
