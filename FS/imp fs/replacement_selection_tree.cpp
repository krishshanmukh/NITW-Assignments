#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int i=0,index;

int compare(int a,int b)
{
		if(a<0&&b<0)
		return -1;
		else if(a<0)
		return 0;
		else if(b<0)
		return 1;
		else if(a==0)
		return 0;
		else if(b==0)
		return 1;
		else if(a>b)
		return 0;
		else
		return 1;
}

int sort(int A[],int a,int size)
{
	if(2*a<size/2)
	sort(A,2*a,size);
	if(2*a+1<size/2)
	sort(A,2*a+1,size);
    int c=compare(A[2*a],A[2*a+1]);
    if(c==1)
    A[a]=A[2*a];
    else if(c==0)
    A[a]=A[2*a+1];
	else
	A[a]=0;
	return A[a];
}

void del(int A[],int size,int elt)
{
	/*if(2*a<size/2)
	{
	    del(A,2*a,size,elt);
	    if(2*a+1<size/2)
	    del(A,2*a+1,size,elt);
	}
	else
	{
		if(A[2*a]==elt)
		{
			A[2*a]=0;
			index=2*a;
		}
		else if(A[2*a+1]==elt)
		{
			A[2*a+1]=0;
			index=2*a+1;
		}
	}*/
	for(int i=size/2;i<size;i++)
	if(A[i]==elt)
	{
		index=i;
		A[i]=0;
		break;
	}
}

void unflag(int A[],int size)
{
	for(int i=size/2;i<size;i++)
	A[i]=abs(A[i]);
}

int isfullflag(int A[],int size)
{
	for(int i=size/2;i<size;i++)
	{
		if(A[i]>0)
		return 0;
	}
	return 1;
}

void flag(int A[],int size,int elt)
{
	for(int i=size/2;i<size;i++)
	if(A[i]==elt)
	{
		A[i]*=-1;
		break;
	}
}

int isempty(int A[],int size)
{
	int c=1;
	for(int i=size/2;i<size;i++)
	if(A[i]!=0)
	{
	    c=0;
	    break;
	}
	return c;
}

int main()
{
	int elt,h,i,e=0,no=0,s=0,a,b;/*no- no of elts , s- no. of elts in sorted file in each iteration,
	 a&b to extract elts to compare, h-height of tree, e-to implement initial loop*/
	ofstream out("data.txt"),out1("data1.txt"),out2("data2.txt");
	cout<<"Enter the elts: ";
	cin>>elt;
	while(elt!=-1)
	{
		out<<elt<<" ";
		cin>>elt;
		no++;
	}
	out.close();
	ifstream in("data.txt"),in1,in2;
	cout<<"Enter the exp of 2: ";
	cin>>h;
	const int size=pow(2,h+1);
	i=size/2;
	int A[size];
    while(!in.eof()&&i<size)
    {
	    in>>A[i++];
    }
    int count=1,ctr=1;//count to switch btn pair of files and ctr to select reqd pair
    while(!isempty(A,size))
    {
    	elt=sort(A,1,size);
    	if(elt!=0&&e<elt)
    	{
    		if(count%2==1)
    		out1<<elt<<" ";
    		else
    		out2<<elt<<" ";
    		del(A,size,elt);
    		e=elt;
    		in>>elt;
    		if(!in.eof())
    		A[index]=elt;
    	}
    	else if(!isfullflag(A,size))
    	{
    		flag(A,size,elt);
    	}
    	else
    	{
    		e=0;
    		if(count%2==1)
    		out1<<"-1"<<endl;
    		else
    		out2<<"-1"<<endl;
    		count++;
    		unflag(A,size);
    	}
    }
   	if(count%2==1)
   	out1<<"-1"<<endl;
   	else
   	out2<<"-1"<<endl;
    out1.close();
    out2.close();
    while(s<no)
	{
		count=1;
	    s=0;
	    if(ctr++%2==1)
	    {
	        in1.open("data1.txt");
	        in2.open("data2.txt");
	        out1.open("data3.txt");
	        out2.open("data4.txt");
	    }
	    else
	    {
	        in1.open("data3.txt");
	    	in2.open("data4.txt");
	    	out1.open("data1.txt");
	    	out2.open("data2.txt");
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
			            out1<<b<<" ";
			            s++;
			        }
	    		    if(b!=-1&&!in2.eof())
		    	    in2>>b;
			        else
			        {
				        while(a!=-1&&!in1.eof())
				        {
				    	    out1<<a<< " ";
    					    s++;
		    			    in1>>a;
			    	    }
			    	    if(s!=no)
				         out1<<"-1"<<endl;
    				     in1>>a;in2>>b;
	    			     count++;
		    	    }
		        }
    		    else if(s!=no)
	    	    {
	    	    	if(b!=-1)
		        	out2<<b<<" ";
			        if(b!=-1&&!in2.eof())
    			    in2>>b;
	    		    else
		    	    {
			    	    while(a!=-1&&!in1.eof())
				        {
				        	out2<<a<< " ";
	    				    in1>>a;
		    		    }
		    		    if(s!=no)
			    	     out2<<"-1"<<endl;
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
			            out1<<a<<" ";
			            s++;
			        }
	    		    if(a!=-1&&!in1.eof())
		    	    in1>>a;
			        else
			        {
    				    while(b!=-1&&!in2.eof())
	    			    {
	    			    	s++;
		    		    	out1<<b<< " ";
					        in2>>b;
    				    }    
    				    if(s!=no)
		    		     out1<<"-1"<<endl;
			    	     in1>>a;in2>>b;
				         count++;
    			    }    
	    	    }
		        else if(s!=no)
		        {
		        	if(a!=-1)
		    	    out2<<a<<" ";
	    		    if(a!=-1&&!in1.eof())
		    	    in1>>a;
			        else
			        {
    				    while(b!=-1&&!in2.eof())
	    			    {
		    		    	out2<<b<< " ";
					        in2>>b;
    				    }    
    				    if(s!=no)
	    			     out2<<"-1"<<endl;
			      	     in1>>a;in2>>b;
				         count++;
    			    }
	    	    }
	        }
	    }
	    out1.close();
	    out2.close();
    	in1.close();
	    in2.close();
	    cout<<s<<" ";
	}
	return 0;
}
