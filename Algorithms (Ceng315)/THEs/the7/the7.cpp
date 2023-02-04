#include "the7.h"

/*
struct Road {
  std::pair<int, int> buildings;
  int time;
  Road(std::pair<int, int> bs, int t) : buildings(bs), time(t) {}
};

*/
using namespace std;
// Implement your solution after this line
const int INF = INT_MAX;

  /* printing the graph
    for(int i = 0;i<n;i++)
    {
        for(auto x: adj[i])
            {
                
                cout << i << ", " << x.first <<  ", " << x.second  <<" || ";
                
            }
            cout<<"\n";
    }
    */
    

void Dijkstras(int n, std::vector<Road> &roads, int s, int* dist,int* parent)
{
    
    int visited[n];
    vector<pair<int,int>> adj[n];
    
    for(int i=0;i< n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(roads[j].buildings.first == i )
            {
                adj[i].push_back({roads[j].buildings.second,roads[j].time});
            }
            
            else if(roads[j].buildings.second == i)
            {
                adj[i].push_back({roads[j].buildings.first,roads[j].time});
            }
        }
    }
    
  
    //adj is array holds the nodes and their neighbors and their cost
    
    for(int i=0;i<n;i++)
    {
       dist[i] = INF;  //initaliziaton of distance
       visited[i]=false;    //init of visited array
       
    }
    dist[s] = 0; //distance of source node is 0
    parent[s]=s;
    while(true) 
    {
        int u = -1;
        
        //finding smallest distance for unvisited node
        for(int i=0;i<n;i++)
        {
            if(!visited[i] && (u ==-1 || dist[i] < dist[u]))
            {
                u=i;
            }
        }
        
        //if no node found breeak
        if(u==-1)
            break;
            
        visited[u] = true ; // mark node is visited

        
        //updating the distances of all unvisited neighs
        
        for(auto x: adj[u])
        {
            
            int node = x.first;
            int weight = x.second;
            
            if(dist[node] > dist[u] + weight)
            {
                dist[node] = dist[u] + weight;
                parent[node] = u;
            }
            
        }
    } 
    
   
    
}


void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    // You can change these variables. These are here for demo only.
    std::vector<int> path;
    //int graph[n][n];


    int dist_s[n];  int parent_s[n];                                //starting node is s
    int dist_x[n];  int parent_x[n];                              // starting node is x
    int dist_y[n];  int parent_y[n];                                 // starting node is y
    
    
    Dijkstras(n,roads,s,dist_s,parent_s);
    Dijkstras(n,roads,x,dist_x,parent_x);
    Dijkstras(n,roads,y,dist_y,parent_y);
    
   
    
    int s_x_y_d = dist_s[x]+dist_x[y]+dist_y[d];
    int s_y_x_d = dist_s[y]+dist_y[x]+dist_x[d];
    int s_x_d = dist_s[x]+dist_x[d];
    int s_y_d = dist_s[y]+dist_y[d];
    int s_d = dist_s[d];
    
    
    
    // both can be used 
   
    if(s_x_y_d <= l || s_y_x_d <= l )
    {
        int both = s_x_y_d <= s_y_x_d ? s_x_y_d : s_y_x_d;
        
        if(printPath)
        {
            if(both==s_x_y_d)  // s-->x-->y-->d
            {
                
                stack<int>temp; vector<int>path_both;
                //cout<<"both==s_x_y_d";
                //s-->x look for parent_s
                
                
                temp.push(x);   // push the destination
                int curr=x; // curr
                while(parent_s[curr] != s )
                {
                    temp.push(parent_s[curr]);    // push the parrent 
                    curr = parent_s[curr];        // update current
                }
                
                temp.push(s);       //push start node but just for this condition
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());         //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                
                // x-->y look for parent_x
                
                temp.push(y);  //push the destination
                curr=y; // curr
                while(parent_x[curr] != x )       // while the parent is not the start node
                {
                    temp.push(parent_x[curr]);    // push the parrent 
                    curr = parent_x[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                
                // y --> d look for parent_y
                
                temp.push(d);    //push the destination
                curr=d;     // curr
                while(parent_y[curr] != y )       // while the parent is not the start node
                {
                    temp.push(parent_y[curr]);    // push the parrent 
                    curr = parent_y[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                //NOw path  has the  correct path
                cout <<"YES BOTH " <<both<<"MINUTES" << "\n";
                PrintRange(path_both.begin(), path_both.end());
                
                
                
                
            }
            // **********************s-->y-->x-->d***************************************
            //s-->y-->x-->d
            else            //s-->y-->x-->d
            {
                stack<int>temp; vector<int>path_both;
                //cout<<"both==s_y_x_d\n";
                //s-->y look for parent_s
                
                temp.push(y);   // push the destination
                int curr=y; // curr
                while(parent_s[curr] != s )
                {
                    temp.push(parent_s[curr]);    // push the parrent 
                    curr = parent_s[curr];        // update current
                }
                
                temp.push(s);       //push start node but just for this condition
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());         //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                
                
                // y-->x look for parent_x
                
                temp.push(x);  //push the destination
                curr=x; // curr
                while(parent_y[curr] != y )       // while the parent is not the start node
                {
                    temp.push(parent_y[curr]);    // push the parrent 
                    curr = parent_y[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                
                
                
                // x --> d look for parent_y
                
                temp.push(d);    //push the destination
                curr=d;     // curr
                while(parent_x[curr] != x )       // while the parent is not the start node
                {
                    temp.push(parent_x[curr]);    // push the parrent 
                    curr = parent_x[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                //Now path  has the  correct path
                /*
                for(int i=0;i<path_both.size();i++)
                {
                    cout<< path_both[i]<<" "<<"\n";
                }*/
                cout <<"YES BOTH " <<both<<"MINUTES" << "\n";
                PrintRange(path_both.begin(), path_both.end());
                
                
            }
            
            
        }
        else
        {
            if(s_x_y_d<=s_y_x_d)
            {
                cout <<"YES BOTH " <<s_x_y_d<<"MINUTES" << "\n";
            }
            else
            {
                cout <<"YES BOTH " <<s_y_x_d <<"MINUTES" << "\n";
            }
        }
    }
    
    else if(s_x_d <= l || s_y_d <= l)
    {
        int min = s_x_d <= s_y_d ? s_x_d : s_y_d;
        
        if(printPath)
        {
            if(min==s_x_d) // s->x-->d
            {
                stack<int>temp; vector<int>path_both;
                
                //s-->x look for parent_s
                
                
                temp.push(x);   // push the destination
                int curr=x; // curr
                while(parent_s[curr] != s )
                {
                    temp.push(parent_s[curr]);    // push the parrent 
                    curr = parent_s[curr];        // update current
                }
                
                temp.push(s);       //push start node but just for this condition
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());         //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
      
                // x --> d look for parent_x
                
                temp.push(d);    //push the destination
                curr=d;     // curr
                while(parent_x[curr] != x )       // while the parent is not the start node
                {
                    temp.push(parent_x[curr]);    // push the parrent 
                    curr = parent_x[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                //NOw path  has the  correct path
                cout <<"YES PRINTER " <<min<<"MINUTES" << "\n";
                PrintRange(path_both.begin(), path_both.end());
            }
            else //s-->y-->d
            {
                stack<int>temp; vector<int>path_both;
                
                //s-->y look for parent_s
                
                
                temp.push(y);   // push the destination
                int curr=y; // curr
                while(parent_s[curr] != s )
                {
                    temp.push(parent_s[curr]);    // push the parrent 
                    curr = parent_s[curr];        // update current
                }
                
                temp.push(s);       //push start node but just for this condition
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());         //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
      
                // y --> d look for parent_x
                
                temp.push(d);    //push the destination
                curr=d;     // curr
                while(parent_y[curr] != y )       // while the parent is not the start node
                {
                    temp.push(parent_y[curr]);    // push the parrent 
                    curr = parent_y[curr];        // update current
                }
                
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());      //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
                //NOw path  has the  correct path
                cout <<"YES DORM " <<min<<"MINUTES" << "\n";
                PrintRange(path_both.begin(), path_both.end());
            }
        }
        else
        {
            if(min==s_x_d)
            {
                cout <<"YES PRINTER " << min <<"MINUTES" << "\n";
            }
            else
            {
                cout <<"YES DORM " << min <<"MINUTES" << "\n";
            }
        }
        
    }
    
    else
    {
        if(s_d <= l)
        {
            if(printPath)
            {
                stack<int>temp; vector<int>path_both;
                
                //s-->d look for parent_s
                
                
                temp.push(d);   // push the destination
                int curr=d; // curr
                while(parent_s[curr] != s )
                {
                    temp.push(parent_s[curr]);    // push the parrent 
                    curr = parent_s[curr];        // update current
                }
                
                temp.push(s);       //push start node but just for this condition
                
                while(!temp.empty())
                {
                    path_both.push_back(temp.top());         //empty stack push the parent nodes the path to the vector
                    temp.pop();
                }
                
              
                //NOw path  has the  correct path
                cout <<"YES DIRECTLY " <<s_d<<"MINUTES" << "\n";
                PrintRange(path_both.begin(), path_both.end());
            }
            else
            {
                cout <<"YES DIRECTLY " <<s_d<<"MINUTES" << "\n";
            }
        }
        
        else
        {
            cout << "IMPOSSIBLE"<<"\n";
        }
    }

    
    


    
    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());
    
}