#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // TODO
    
    int i;
    
    for(i=0;i<this->vertexList.size();i++)
    {
        
        if(vertexName.compare(this->vertexList[i].name)==0)
        {
            throw DuplicateVertexNameException();
        }
    }
    
    GraphVertex a; a.name= vertexName;a.edgeCount=0;
    this->vertexList.push_back(a);
    
    
    
}
int Graph::vertexIndex(const std::string& vertexName)
{
    int i;
    for(i=0;i<this->vertexList.size();i++)
    {
        
        if(vertexName.compare(this->vertexList[i].name)==0)
        {
            return i;
        }
    }
    
    return INVALID_INDEX;
}


bool Graph::contains_vertex(const std::string& vertexName)
{
    int i;
    
    for(i=0;i<this->vertexList.size();i++)
    {
        if(vertexName == this->vertexList[i].name)
        {
            return true;
        }
        
    }
    
    return false;
    
}


bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    // TODO
    
    int i,mark1=0,mark2=0;
    
    
    // if both of the vertices are not in the graph throw error
    mark1= contains_vertex(fromVertexName); mark2= contains_vertex(toVertexName);
    
    if(mark1 !=1 || mark2 != 1)
    {
        throw VertexNotFoundException();
        return false;
    }
    
    int from,to;
    from = vertexIndex(fromVertexName); to = vertexIndex(toVertexName); // finding indeces of vertices
    
    
    //if edge count is equal max throw error
    if(vertexList[from].edgeCount == MAX_EDGE_PER_VERTEX || vertexList[to].edgeCount == MAX_EDGE_PER_VERTEX )
    {
        throw TooManyEdgeOnVertexExecption();
        return false;
    }

    
    //if the edge is already exists in graph return false
    for(i=0;i<this->edgeList.size();i++)
    {
        if(edgeList[i].vertexId0==from && edgeList[i].vertexId1==to )
        {
            return false;
        }
        
    }
    
    if(from==to)
    {
        return false;
    }
    
    
    //create the edge
    
    GraphEdge e; e.weight= weight; e.vertexId0=from; e.vertexId1=to; e.masked=0;
   
    this->edgeList.push_back(e);
    vertexList[from].edgeIds[vertexList[from].edgeCount]=edgeList.size()-1;
    
    vertexList[to].edgeIds[vertexList[to].edgeCount]=edgeList.size()-1;
    vertexList[from].edgeCount +=1;vertexList[to].edgeCount +=1;
    
   
    
    return true;
    
    
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    // TODO

    int i,mark1=-1,mark2=-1;
    
    for(i=0;i<this->vertexList.size();i++)
    {
        if(from == this->vertexList[i].name)
        {
            mark1=1;
        }
        
    }
    for(i=0;i<this->vertexList.size();i++)
    {
        if(to == this->vertexList[i].name)
        {
            mark2=1;
        }
        
    }
    
    if(mark1==-1 || mark2==-1)
    {
        throw VertexNotFoundException();
    }
    
    

    std::priority_queue<DistanceVertexIdPair> pq;

    
    std::vector<int> distance;
    std::vector<int> previous;
    
    for(int i=0;i<vertexList.size();i++)
    {
        distance.push_back(LARGE_NUMBER);
        previous.push_back(-1) ;
    }
    
    int s;
    for(i=0;i<this->vertexList.size();i++)
    {
        
        if(from.compare(this->vertexList[i].name)==0)
        {
            s=i;
        }
    }
    
    
    distance[s]=0;
    
    for(int j=0;j<vertexList.size();j++)
    {
        

            DistanceVertexIdPair p = DistanceVertexIdPair(j,distance[j]);
            pq.push(p);
       
    }
    
    
    while(!pq.empty())
    {
        int v_ind=pq.top().vId;
        int v_weg= pq.top().currentWeight;
        pq.pop();
        

        for(int k=0;k<vertexList[v_ind].edgeCount;k++)
        {
            int edge_id=vertexList[v_ind].edgeIds[k];
            int w_id= edgeList[edge_id].vertexId0 == v_ind ?  edgeList[edge_id].vertexId1 : edgeList[edge_id].vertexId0;
            
            if(edgeList[edge_id].masked)
            {
                continue;
            }
            
            int new_dist= distance[v_ind] + edgeList[edge_id].weight;
            if(new_dist< distance[w_id])
            {
                distance[w_id]=new_dist;
                previous[w_id]= v_ind;
                DistanceVertexIdPair w = DistanceVertexIdPair(w_id,new_dist) ;
                
                pq.push(w);
          
            }
        }

    }
    int e; //indexof TO
    for(i=0;i<this->vertexList.size();i++)
    {
        
        if(to.compare(this->vertexList[i].name)==0)
        {
            e=i;
        }
    }
    
    
    if(previous[e]==-1)
    {
        return false;
    }
 
    orderedVertexIdList.push_back(e);
    
    while(previous[e]!=s)
    {
        
        orderedVertexIdList.push_back(previous[e]);
        e=previous[e];
    }
    
    orderedVertexIdList.push_back(s);
    std::vector<int> temp;
    
    int vect_size=orderedVertexIdList.size();
    for(int x=0;x<vect_size;x++)
    {
        int git= orderedVertexIdList.back();
        orderedVertexIdList.pop_back();
        temp.push_back(git);
    }
    for(int x=0;x<vect_size;x++)
    {
        orderedVertexIdList.push_back(temp[x]);
        
    }
    
    return true;
    
 
}

void Graph::weg_helper(std::vector<int>& order_short)
{
    int high_weg=-1,edge_id=-1,n1,n2;
    for(int i=0;i<order_short.size()-1;i++)
    {
        n1=order_short[i];n2=order_short[i+1];
        for(int k=0;k<edgeList.size();k++)
        {
            if((edgeList[k].vertexId0==n1 && edgeList[k].vertexId1==n2) || (edgeList[k].vertexId0==n2 && edgeList[k].vertexId1==n1))
            {
                if(edgeList[k].weight>high_weg)
                {
                    high_weg= edgeList[k].weight;
                    edge_id=k;
                    
                }              
            }
        }
    }
    if(edge_id!=-1)
    {
        edgeList[edge_id].masked=true;
    }
    
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
    
    
    UnMaskAllEdges();
    std::vector<int> order_short;
    ShortestPath(order_short,from,to);
    
    orderedVertexIdList.push_back(order_short);
    
  
    
    

    int j=0,i=1;
   while(i<numberOfShortestPaths)
    {
        std::vector<int> order_short_new;
        weg_helper(orderedVertexIdList[j]);
        int var_mi=ShortestPath(order_short_new,from,to);
        if(!var_mi)
        {
            break;
        }
        orderedVertexIdList.push_back(order_short_new);
        j++;i++;
        
    }
    
    int res=orderedVertexIdList.size();
    UnMaskAllEdges();
    
    return res;
    
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO

    
    int i,j;
    
    
    
    for(i=0;i<vertexNames.size();i++)
    {

        int s0_ind,s1_ind;
        s0_ind = vertexIndex(vertexNames[i].s0); s1_ind = vertexIndex(vertexNames[i].s1); 
    

        for(j=0;j<this->edgeList.size();j++)
        {
            if((edgeList[j].vertexId0==s0_ind && edgeList[j].vertexId1==s1_ind) || (edgeList[j].vertexId0==s1_ind && edgeList[j].vertexId1==s0_ind) )
            {
                edgeList[j].masked=true;
            }
        
        }
        
    }
    
    for(i=0;i<vertexNames.size();i++)
    {
        
        if(contains_vertex(vertexNames[i].s0) && contains_vertex(vertexNames[i].s1))
        {
            ;
        }
        else
        {
            throw VertexNotFoundException();
        }
    }
    
    
    
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    
    
    int i,j;
    
    
    
    for(i=0;i<vertexNames.size();i++)
    {
        
        
        
        int s0_ind,s1_ind;
        s0_ind = vertexIndex(vertexNames[i].s0); s1_ind = vertexIndex(vertexNames[i].s1); 
    

        for(j=0;j<this->edgeList.size();j++)
        {
            if((edgeList[j].vertexId0==s0_ind && edgeList[j].vertexId1==s1_ind) || (edgeList[j].vertexId0==s1_ind && edgeList[j].vertexId1==s0_ind))
            {
                edgeList[j].masked=false;
            }
        
        }
    }
    
    for(i=0;i<vertexNames.size();i++)
    {
        
        if(contains_vertex(vertexNames[i].s0) && contains_vertex(vertexNames[i].s1))
        {
            ;
        }
        else
        {
            throw VertexNotFoundException();
        }
    }
    
}

void Graph::UnMaskAllEdges()
{
    // TODO
    int i;
    for(i=0;i<this->edgeList.size();i++)
        {
            edgeList[i].masked=false;
  
        }
        
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO
    if(!contains_vertex(name))
    {
        throw VertexNotFoundException();
    }
    
    
    int ind_name;
    ind_name=vertexIndex(name);
    
    for(int i=0;i<vertexList[ind_name].edgeCount;i++)
    {
        int edge_ind= vertexList[ind_name].edgeIds[i];
        edgeList[edge_ind].masked=true;
    }
    
    
    
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO
    if(!contains_vertex(name))
    {
        throw VertexNotFoundException();
    }
    
    
    int ind_name;
    ind_name=vertexIndex(name);
    
    for(int i=0;i<vertexList[ind_name].edgeCount;i++)
    {
        int edge_ind= vertexList[ind_name].edgeIds[i];
        edgeList[edge_ind].masked=false;
    }
}


void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    // TODO
    int ind0,ind1;
    ind0=vertexIndex(vName0);ind1=vertexIndex(vName1);
    
    if(!contains_vertex(vName0)||!contains_vertex(vName1))
    {
        throw VertexNotFoundException();
    }
    
    for(int i=0;i<this->edgeList.size();i++)
    {
        if((edgeList[i].vertexId0==ind0 && edgeList[i].vertexId1==ind1)||(edgeList[i].vertexId0==ind1 && edgeList[i].vertexId1==ind0))
        {
            edgeList[i].weight=newWeight;break;
        }
        
    }
    
    
    
    
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    // TODO
    

    for(int i=0;i<this->edgeList.size();i++)
    {
        if((edgeList[i].vertexId0==vId0 && edgeList[i].vertexId1==vId1) || (edgeList[i].vertexId0==vId1 && edgeList[i].vertexId1==vId0))
        {
            edgeList[i].weight=newWeight;break;
        }
        
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    // TODO
    
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    // TODO
    
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO
    
    if(vertexId>= TotalVertexCount())
    {
        return "";
    }
    
    return vertexList[vertexId].name;
    
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO
    int vol=vertexList.size();
    int total_weight=0;
    
    int high_weg=-1,edge_id=-1,n1,n2;
   
    
    
    for(int i=0;i<orderedVertexIdList.size()-1;i++)
    {
        n1=orderedVertexIdList[i]; n2=orderedVertexIdList[i+1];
        
        if(n1 >= vol || n2 >=vol)
        {
            throw VertexNotFoundException();
            
        }
        for(int k=0;k<edgeList.size();k++)
        {
            
            
            if((edgeList[k].vertexId0==n1 && edgeList[k].vertexId1==n2) || (edgeList[k].vertexId0==n2 && edgeList[k].vertexId1==n1))
            {
                total_weight += edgeList[k].weight;           
            }
        }
    }
    
    
    
    return total_weight;
}