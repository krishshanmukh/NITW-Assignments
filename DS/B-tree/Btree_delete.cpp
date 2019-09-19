#include<iostream>
using namespace std;

const int d=1;
int c=0;

struct btnode
{
	int count;
	int key[2*d+1];
	btnode *child[2*d+2];
	int x;
	btnode *parent;
	btnode();
};
btnode *A=NULL;

btnode :: btnode()
{
	count=0;
	for(int i=0;i<=2*d+2;i++)
	child[i]=NULL;
	parent=NULL;
}

void sort(btnode* &T)
{
	int x=T->key[T->count-1],i;
	btnode *M=T->child[T->count];
	for(i=0;i<T->count-1;i++)
	{
		if(T->key[i]>T->key[T->count-1])
		{
			for(int j=T->count-1;j>i;j--)
			{
			    T->key[j]=T->key[j-1];
			    T->child[j+1]=T->child[j];
			}
			T->key[i]=x;
			T->child[i+1]=M;
			break;
		}
	}
}

btnode* split(btnode *M)
{
	btnode *T;
	T=new(btnode);
	for(int i=(M->count/2)+1;i<M->count;i++)
	{
	    T->key[T->count]=M->key[i];
	    T->child[T->count++]=M->child[i];
    }
    T->child[T->count]=M->child[M->count];
	return T;
}

btnode* parent(int key)
{
	btnode *T;
	T=new(btnode);
	T->key[T->count++]=key;
	return T;
}



int keyredbn(btnode *T)
{
	int i=0;
	if(T->parent==NULL)
	return 0;
	else
	{
		while(T->key[0]>T->parent->key[i]&&i<T->parent->count)
		i++;
		btnode *M=T->parent;
		if(i==0)
		{
			if(M->child[i+1]->count<2*d)
			{
				for(int j=M->child[i+1]->count-1;j>=0;j--)
				{
			    	M->child[i+1]->key[j+1]=M->child[i+1]->key[j];
				    M->child[i+1]->child[j+1]=M->child[i+1]->child[j];
				}
				M->child[i+1]->count++;
				M->child[i+1]->key[0]=M->key[i];
				M->child[i+1]->child[0]=M->child[i]->child[T->count];
				M->key[i]=T->key[--T->count];
				return 1;
			}
				else
				return 0;
		}
		else if(i==M->count-1)
		{	
			if(M->child[i+1]->count<2*d)
			{
				for(int j=M->child[i+1]->count-1;j>=0;j--)
				{
				    M->child[i+1]->key[j+1]=M->child[i+1]->key[j];
				    M->child[i+1]->child[j+1]=M->child[i+1]->child[j];
				}
				M->child[i+1]->count++;
				M->child[i+1]->key[0]=M->key[i];
				M->child[i+1]->child[0]=M->child[i]->child[T->count];
				M->key[i]=T->key[--T->count];
				return 1;
			}
			else if(M->child[i-1]->count<2*d)
			{	
				M->child[i-1]->key[M->child[i-1]->count++]=M->key[i-1];
				M->child[i-1]->child[M->child[i-1]->count]=M->child[i]->child[0];
				M->key[i-1]=T->key[0];
				for(int j=0;j<T->count;j++)
				{
				    T->key[j]=T->key[j+1];
				    T->child[j]=T->child[j+1];
				}
				T->count--;
				return 1;
		    }
			else 
			return 0;
		}
		else
		{
			if(M->child[i-1]->count<2*d)
			{
				M->child[i-1]->key[M->child[i-1]->count++]=M->key[i-1];
				M->child[i-1]->child[M->child[i-1]->count]=M->child[i]->child[0];
				M->key[i-1]=T->key[0];
				for(int j=0;j<T->count;j++)
				{
				    T->key[j]=T->key[j+1];
				    T->child[j]=T->child[j+1];
				}
				T->count--;
				return 1;
			}
			else 
			return 0;
		}
    }
}

btnode* nodesplitting (btnode* &T,int x)
{
	cout<<"Node splitting of: "<<T->key[0]<<endl;
	if(T->parent!=NULL)
	{
		btnode *M=split(T);
		T->parent->key[T->parent->count++]=T->key[T->count/2];
		T->parent->child[T->parent->count]=M;
		T->count/=2;
		sort(T->parent);
		M->parent=T->parent;
		M->x=T->x;
		if(T->parent->count>2*d)
		{
			int y=keyredbn(T->parent);
		    if(y==0)
            nodesplitting(T->parent,T->x+1);
	    }
	}
	else if(T->parent==NULL)
	{
		btnode *M=split(T);
		btnode *K=parent(T->key[T->count/2]);
		T->count/=2;
		K->child[0]=T;
		T->parent=K;
		K->child[1]=M;
		M->x=x;
		M->parent=K;
		K->x=x+1;
		A=K;
	}
}

void createbtree(btnode* &T,int key,int x)
{
	int i,c=0;
	for(i=0;i<T->count;i++)
	{
		if(key<T->key[i])
		{
			if(T->child[i]!=NULL)
			{
				T->child[i]->parent=T;
			    createbtree(T->child[i],key,x);
			    c=1;
			}
			break;
		}
	}
	if(i==T->count&&T->child[i]!=NULL)
	{
		T->child[i]->parent=T;
	    createbtree(T->child[i],key,x);
	}
	else if(T->count<2*d&&T->child[0]==NULL)
	{
		T->x=x;
		T->key[T->count++]=key;
		if(T->count!=1)
		sort(T);
	}
    else if(T->count==2*d&&c==0)
    {
    	T->key[T->count++]=key;
    	sort(T);
    	int w;
    	w=keyredbn(T);
    	if(w==0)
    	nodesplitting(T,x);
    }
}
	
btnode* search(btnode* T,int x,int &j)
{
	int i;
	for(i=0;i<T->count;i++)
	{
		if(T->key[i]==x)
		{
			j=i;
		    return T;
		}
		else if(x<T->key[i])
		{
		     return (search(T->child[i],x,j));
		     break;
		 }
		else;
	}
	if(i==T->count)
	return search(T->child[i],x,j);
}

void nodecombining(btnode* &T,btnode *M)
{
	for(int i=T->count;i<T->count+M->count;i++)
	{
		T->key[T->count++-1]=M->key[i-T->count];
	}
}

int isleaf(btnode *T)
{
	if(T->child[0]==NULL)
	return 1;
	else
	return 0;
}

int keyredbn1(btnode *T,int k)
{
	int i=0;
	if(T->parent==NULL||T==NULL)
	return 0;
	else
	{
		while(T->key[0]>T->parent->key[i]&&i<T->parent->count)
		i++;
		btnode *M=T->parent;
		if(i==0)
		{
			if(M->child[i+1]->count<2*d)
			{
				for(int j=M->child[i+1]->count-1;j>=0;j--)
				{
			    	M->child[i+1]->key[j+1]=M->child[i+1]->key[j];
				    M->child[i+1]->child[j+1]=M->child[i+1]->child[j];
				}
				M->child[i+1]->count++;
				M->child[i+1]->key[0]=M->key[i];
				M->child[i+1]->child[0]=M->child[i]->child[T->count];
				M->key[i]=T->key[--T->count];
				return 1;
			}
				else
				return 0;
		}
		else if(i==M->count-1)
		{	
			if(M->child[i+1]->count<2*d&&(k==2))
			{
				for(int j=M->child[i+1]->count-1;j>=0;j--)
				{
				    M->child[i+1]->key[j+1]=M->child[i+1]->key[j];
				    M->child[i+1]->child[j+1]=M->child[i+1]->child[j];
				}
				M->child[i+1]->count++;
				M->child[i+1]->key[0]=M->key[i];
				M->child[i+1]->child[0]=M->child[i]->child[T->count];
				M->key[i]=T->key[--T->count];
				return 1;
			}
			else if(M->child[i-1]->count<2*d&&(k==1))
			{	
				M->child[i-1]->key[M->child[i-1]->count++]=M->key[i-1];
				M->child[i-1]->child[M->child[i-1]->count]=M->child[i]->child[0];
				M->key[i-1]=T->key[0];
				for(int j=0;j<T->count;j++)
				{
				    T->key[j]=T->key[j+1];
				    T->child[j]=T->child[j+1];
				}
				T->count--;
				return 1;
		    }
			else 
			return 0;
		}
		else
		{
			if(M->child[i-1]->count<2*d)
			{
				M->child[i-1]->key[M->child[i-1]->count++]=M->key[i-1];
				M->child[i-1]->child[M->child[i-1]->count]=M->child[i]->child[0];
				M->key[i-1]=T->key[0];
				for(int j=0;j<T->count;j++)
				{
				    T->key[j]=T->key[j+1];
				    T->child[j]=T->child[j+1];
				}
				T->count--;
				return 1;
			}
			else 
			return 0;
		}
    }
}

int del(btnode *T,int x)
{
	int j;
	btnode *M=search(T,x,j);
    if(!isleaf(M))
   	{
   		if(M->child[j]->count>d&&j<M->count)
   		{
   			M->key[j]=del(M->child[j],M->child[j]->key[M->child[j]->count-1]);
   			c=1;
   		}
   		else if(M->child[j+1]->count>d&&j<M->count)
   		{
   			M->key[j]=del(M->child[j+1],M->child[j+1]->key[0]);
   			c=2;
   		}
   		else
   		{
   			//int a=del(M->child[j],M->child[j]->key[M->child[j]->count]);
   			int a=M->key[j];
   		    nodecombining(M->child[j],M->child[j+1]);
   		    for(int k=j;j<M->count-1;k++)
   		    {
   		    	M->key[j]=M->key[j+1];
   		    	M->child[j+1]=M->child[j+2];
   		    }

   		    return a;
   		}
   	}
   	else
   	{
   		if(c==0&&M->count>d)
   		{
   			int m=M->key[j];
   			for(int k=j;k<M->count-1;k++)
   			M->key[k]=M->key[k+1];
   			M->count--;
   			return m;
   		}
   		else if(c==1&&M->count>d)
   		{
   			return M->key[--M->count];
   		}
   		else if(c==2&&M->count>d)
   		{
   			int a=M->key[0];
   			for(int k=0;k<M->count-1;k++)
   			M->key[k]=M->key[k+1];
   			M->count--;
   			return a;
   		}
   		else
   		{
   			if(M->parent!=NULL)
   			{
   			    btnode *N=M->parent; 
	            int i=0;
	        	while(M->key[0]>N->key[i]&&i<2*d)
	            i++;
    	        int a=M->key[i];
        	    if(i<2*d&&N->child[i+1]->count<d)
            	{
            		for(int k=j;j<M->count-1;k++)
   				    {
   			    		M->key[j]=M->key[j+1];
   		    			M->child[j+1]=M->child[j+2];
	   		    	}
	   		    	M->count--;
	   		    	nodecombining(N->child[i],N->child[i+1]);
 	  			    return a;
				}
				else
   			    {
   			    	int m=M->key[j];
   			    	for(int k=j;j<M->count-1;k++)
   				    {
   			    		M->key[j]=M->key[j+1];
   		    			M->child[j+1]=M->child[j+2];
	   		    	}
	   		    	M->count--;
   				    int x=keyredbn1(N->child[i+1],1);
   				    if(x==0)
   				    x=keyredbn1(N->child[i-1],2);
   				    return m;
   			    }
			}
   		}
   	}
}

void display(btnode *T,int x)
{
    if(T!=NULL)
	{
		int i;
		for(i=0;i<T->count;i++)
		{
			display(T->child[i],x);
			if(T->x==x)
			cout<<T->key[i]<<" ";
		}
		display(T->child[i],x);
	}	
}

int main()
{
	int  e;
	btnode *T=new(btnode);
	cout<<"Enter nos: ";
	cin>>e;
	while(e!=-1)
	{
		createbtree(T,e,0);
		if(A!=NULL)
		T=A;
		cin>>e;
	}
	cout<<"Tree of order: "<<d<<endl<<endl;
	for(int i=T->x;i>=0;i--)
	{
	    display(T,i);
	    cout<<endl;
	}
	cout<<"Enter elt to delete: ";
	cin>>e;
	while(e!=0)
	{
	    c=0;
	    del(T,e);
	    for(int i=T->x;i>=0;i--)
	    {
	        display(T,i);
	        cout<<endl;
	    }
	    cout<<"Enter elt to del: ";
	    cin>>e;
	}
	return 0;
}
