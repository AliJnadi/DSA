/******************************************************************************
                               Generic Graph implementation in c++
                                  a.jnadi@innopolis.university
                                          DSA2023_LAB10
*******************************************************************************/

#include <iostream>
#include <list>

using namespace std;

template<typename V,typename E>
class Graph
{
    public:
    class Vertex
    {
        public:
        V value;
        int ID;
        typename list<Vertex>::iterator vertexRef;
        
        Vertex(){
        }
        
        Vertex(V val, int ID)
        {
            value = val;
            this->ID = ID;
        }
    };
    
    class Edge
    {
        public:
        E weight;
        Vertex from;
        Vertex to;
        typename list<Edge>::iterator edgeRef;
        
        Edge(E wei, Vertex fr, Vertex t)
        {
            weight = wei;
            from = fr;
            to = t;
        }
    };
    
    int n = 0;
    list<Vertex> vertices;
    list<Edge> edges;
    
    Graph()
    {
        vertices = list<Vertex>();
        edges = list<Edge>();
    }
    
    Vertex addVertex(V val)
    {
        Vertex vertex = Vertex(val, n);
        n++;
        vertex.vertexRef = vertices.insert(vertices.end() ,vertex);
        return vertex;
    }
    
    Edge addEdge(E weight, Vertex from, Vertex to)
    {
        Edge edge = Edge(weight, from, to);
        edge.edgeRef = edges.insert(edges.end(), edge);
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
};

int main()
{
    Disjoint_int_set obj(5);
    obj.Union(0, 2);
    obj.Union(4, 2);
    obj.Union(3, 1);
   
    if (obj.find(4) == obj.find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
        
    if (obj.find(1) == obj.find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
    
    //Implementation of Kruskal's algorithm
    
    Graph<string, int> graph = Graph<string, int>();
    
    Graph<string, int>::Vertex kazan     = graph.addVertex("Kazan");
    Graph<string, int>::Vertex moscow    = graph.addVertex("Moscow");
    Graph<string, int>::Vertex innopolis = graph.addVertex("Innopolis");
    Graph<string, int>::Vertex spb = graph.addVertex("Saint Petersburg");
    
    graph.addEdge(600, moscow, spb);
    graph.addEdge(719, kazan, moscow);
    graph.addEdge(38, kazan, innopolis);
    
    graph.edges.sort([](const Graph<string, int>::Edge& a, const Graph<string, int>::Edge& b)
        {
            return a.weight < b.weight;
        });
    
    for(auto edg: graph.edges)
    {
        cout << edg.from.value <<" ->[" << edg.weight <<"]<- " << edg.to.value << endl;
    }
    
    cout << graph.degree(kazan) << endl;
    cout << graph.areAdjacent(moscow, innopolis) << endl;
    cout << graph.areAdjacent(moscow, kazan) << endl;
    
    cout << "Before Removing" << endl;
    
    for(auto edg: graph.edges)
    {
        cout << edg.from.value <<" ->[" << edg.weight <<"]<- " << edg.to.value << endl;
    }
    
    graph.removeVertex(kazan);
    
    cout << "After Removing" << endl;
    
    for(auto edg: graph.edges)
    {
        cout << edg.from.value <<" ->[" << edg.weight <<"]<- " << edg.to.value << endl;
    }
    
    return 0;
}
