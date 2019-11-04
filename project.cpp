#include<bits/stdc++.h>
using namespace std;

/* APPLYING ALGORITHM FOR A GRAPH SHOWN AS BELOW 

					 1
				 	/
				  2     3
				  \   /
				    5
				   / \
				  7	  6
				  \   |
				   9  |
				  /	\ |	                                   	         \
		         8	 \|
		              10

*/

/* WHERE INFECTED GRAPH IS GIVEN BELOW

			         1
				 	/
				  2     3
				  \   /
				    5

*/


int sub(vector<int>v,int a[])
{
int m=v.size();
int n=4;
   
    map<int, int> mp1; 
  
    for (int i = 0; i < m; i++) 
        mp1[v[i]]++; 
  
    int f = 0; 
  
    for (int i = 0; i < n; i++) { 
       
  
        if (mp1.find(a[i]) == mp1.end()) { 
            f = 1; 
            break; 
        } 
  
        else { 
            mp1[a[i]]--; 
  
            if (mp1[a[i]] == 0) 
                mp1.erase(mp1.find(a[i])); 
        } 
    } 
  
    return f; 
} 


vector<int> bfs(int s,int T,vector<int> adj[]) 
{ int i;
    bool visited[10]; 
    for( i = 0; i < 10; i++) 
        visited[i] = false; 
  
    list<int> queue; 
  	vector<int>v;
    visited[s] = true; 
    queue.push_back(s);
    v.push_back(s); 
    queue.push_back(0);

    int t=0; 
  
    while(!queue.empty() && t<T) 
    { 


        s = queue.front(); 
        if(s==0)
        	{t++;
        		queue.push_back(0);}
         
        queue.pop_front(); 
        if(s!=0)
        {
        for (i =0; i < adj[s].size(); ++i) 
        { 
            if (!visited[adj[s][i]]) 
            { 
                visited[adj[s][i]] = true; 
                queue.push_back(adj[s][i]); 
                v.push_back(adj[s][i]);
            } 
        }
        } 

    } 

   return v;
} 


     
void addEdge(vector<int> adj[], int u, int v) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u); 
} 
   /*CREATE A GRAPH MANUALLY*/

void make(vector<int> adj[]) 
{ 
     
    addEdge(adj, 1, 2); 
    addEdge(adj, 5, 2); 
    
    addEdge(adj, 5, 3); 
    addEdge(adj, 5, 6); 
    addEdge(adj, 5, 7); 
    addEdge(adj, 9, 7);
    addEdge(adj, 6, 10);
    addEdge(adj, 10, 9);
    addEdge(adj, 8, 9);

} 

void mak(vector<int> ad[]) 
{ 
     
    addEdge(ad, 5, 3);
    addEdge(ad, 5, 2);
    
    addEdge(ad, 2, 1);

} 

/* CHECKING FOR ONE HOP */

int is_hop(int i,int j,vector<int> adj[])
{
	int k;
	for(k=0;k<adj[i].size();k++)
	{
		if(adj[i][k]==j)
		{
			return 1;
		}
	}
	return 0;
}

/* CALCULATING THE PROBALITY FOR PARTICULARS NODES */

float pro(int i,int j,vector<int> adj[],float p)
{
	if(i==j)
		return 1-p;
	else if(is_hop(i,j,adj))
	{
		int d;
		d=adj[i].size();
		return (p/d);
	}
	else
		return 0;
}

/* FUNCTION TO FILL THE TABLE USING PREVIOUS DATA */

float cal(float phi[][6],int k, vector<int> adj[],int j,float p)
{
	int i;
	float ch;
	ch=0;
	for(i=1;i<6 && i!=4;i++)
	{
		ch=ch+(pro(k,i,adj,p)*phi[j+1][i]);
	}
	return ch;
}


int main()
{
	vector<int> adj[20];
	make(adj);
	vector<int>ad[20];
	mak(ad);
	float p=0.8;
	int T=2;
	int infected[5]={1,2,3,5};
	float phi[T+1][6]={0};
	int i;

	for(i=1;i<6;i++)
	{
		phi[T][i]=1;
	}
	map<float,int>m;
	vector<float>final;
	vector<int>final_nodes;
	int j;
	for(j=T-1;j>=0;j--)
	{
		for(i=1;i<6 && i!=4;i++)
		{
			phi[j][i]=cal(phi,i,adj,j,p);
			if(j==0)
			{
				m[phi[j][i]]=i;
				final.push_back(phi[j][i]);
			}
		}

	}

	sort(final.begin(),final.end());
	for(i=3;i>=0;i--)
	{
		final_nodes.push_back(m[final[i]]);
	}
 
	for(i=0;i<=3;i++)
	{
		vector<int> vf;
		vf=bfs(final_nodes[i],T,adj);
		if(!sub(vf,infected)==1)
		{
			cout<<final_nodes[i] <<"th ::: node is the source node";
			break;
		}
	}
	
}