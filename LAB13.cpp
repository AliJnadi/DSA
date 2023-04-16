/******************************************************************************
                              Kruskal algorithm implementation in c++
                                  a.jnadi@innopolis.university
                                          DSA2023_LAB12
*******************************************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <set>

using namespace std;

template<typename V,typename E>
class Graph
{
    public:
    
    class Vertex;
    class Edge;
    
    class Vertex
    {
        public:
        V value;
        int ID;
        list<Edge*> adjNodes;
        typename vector<Vertex*>::iterator vertexRef;
        
        Vertex(){
        }
        
        Vertex(V val, int ID)
        {
            value = val;
            this->ID = ID;
            //adjNodes = list<Edge*>();
        }
        
        bool operator< (const Vertex &a) const
        {
            return value < a.value;
        }
    };
    
    class Edge
    {
        public:
        E weight;
        Vertex* from;
        Vertex* to;
        typename list<Edge*>::iterator edgeRef;
        
        Edge(E wei, Vertex* fr, Vertex* t)
        {
            weight = wei;
            from = fr;
            to = t;
        }
    };
    
    int n = 0;
    vector<Vertex*> vertices;
    list<Edge*> edges;
    list<Edge> MST;
    
    Graph()
    {
        //vertices = new vector<Vertex>();
        //edges = list<Edge>();
        MST = list<Edge>();
    }
    
    Vertex* addVertex(V val)
    {
        Vertex* vertex = new Vertex(val, n);
        n++;
        vertex->vertexRef = vertices.emplace(vertices.end() , vertex);
        return vertex;
    }
    
    Edge* addEdge(E weight, Vertex* from, Vertex* to)
    {
        Edge* edge = new Edge(weight, from, to);
        from->adjNodes.push_back(edge);
        // from.adjNodes.insert(from.adjNodes.end(), edge);
        edge->edgeRef = edges.insert(edges.end(), edge);
        return edge;
    }
    
    int degree(Vertex vertex)
    {
        int result = 0;
        for(Edge edge : edges)
        {
            if (edge.from.value == vertex.value || edge.to.value == vertex.value)
                result++;
        }
        return result;
    }
    
    bool areAdjacent(Vertex v, Vertex u)
    {
        for(Edge edge : edges)
        {
            if ((edge.from.value == v.value && edge.to.value == u.value) || (edge.from.value == u.value && edge.to.value == v.value))
                return true;
        }
        return false;
    }
    
    void removeEdge(Edge edge)
    {
        edges.erase(edge.edgeRef);
    }
    
    void removeVertex(Vertex vertex)
    {
        vertices.erase(vertex.vertexRef);
        
        auto it = edges.begin();
        
        while(it != edges.end())
        {
            if ((*it).from.value == vertex.value || (*it).to.value == vertex.value)
            {
                it = edges.erase(it);
            }
            else
                it++;
        }
    }
    
    vector<E> dijkstra(Vertex* S)
    {
        set<pair<E, Vertex>> pq;
    
        vector<E> dist(n, 1e9);
        dist[S->ID] = 0;
    
        pq.insert({0, *S});
    
        while(!pq.empty())
        {
            auto it = *(pq.begin());
        
            Vertex node = it.second;
            E distance = it.first;
            
            pq.erase(it);
        
            for(auto it : node.adjNodes)
            {
                Graph<V, E>::Vertex* adjNode = it->to;
                E edgWeight = it->weight;
                
                if((distance + edgWeight) < dist[adjNode->ID])
                {
                    if(dist[adjNode->ID] == 1e9)
                        pq.erase({dist[adjNode->ID], *adjNode});
                    
                    dist[adjNode->ID] = distance + edgWeight;
                    pq.insert({dist[adjNode->ID], *adjNode});
                }
            }
        }
        return dist;
    }
};

int main()
{
    //Implementation of Kruskal's algorithm
    Graph<string, int> graph = Graph<string, int>();
    
    Graph<string, int>::Vertex* A = graph.addVertex("A");
    Graph<string, int>::Vertex* B = graph.addVertex("B");
    Graph<string, int>::Vertex* C = graph.addVertex("C");
    Graph<string, int>::Vertex* D = graph.addVertex("D");
    Graph<string, int>::Vertex* E = graph.addVertex("E");
    Graph<string, int>::Vertex* F = graph.addVertex("F");
    // Graph<string, int>::Vertex G = graph.addVertex("G");
    graph.addEdge(4, A, B);
    graph.addEdge(4, A, C);
    
    graph.addEdge(4, B, A);
    graph.addEdge(2, B, C);
    
    graph.addEdge(4, C, A);
    graph.addEdge(2, C, B);
    graph.addEdge(3, C, D);
    graph.addEdge(1, C, E);
    graph.addEdge(6, C, F);
    
    graph.addEdge(3, D, C);
    graph.addEdge(2, D, F);
    
    graph.addEdge(1, E, C);
    graph.addEdge(3, E, F);
    
    graph.addEdge(6, F, C);
    graph.addEdge(2, F, D);
    graph.addEdge(3, F, E);
    
    vector<int> res = graph.dijkstra(A);
    
    for(auto value : res)
        cout << value << " " << endl;

    return 0;
}
