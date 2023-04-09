

/******************************************************************************

                              Kruskal algorithm implementation in c++
                                  a.jnadi@innopolis.university
                                          DSA2023_LAB12
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
    list<Edge> MST;
    
    Graph()
    {
        vertices = list<Vertex>();
        edges = list<Edge>();
        MST = list<Edge>();
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

class Disjoint_int_set
{
    private:
        int *parent;
        int *rnk;
        int n;
    
    public:
    
    void makeSet()
    {
        for (int i = 0; i < n; i++) 
        {
            parent[i] = i;
            rnk[i] = 1;
        }
    }
    
    Disjoint_int_set(int n)
    {
        this->n = n;
        parent = new int[n];
        rnk = new int[n];
        makeSet();
    }
    
    int find(int i)
    {
        if(parent[i] != i)
            parent[i] = find(parent[i]);
        return parent[i];
    }
    
    void Union(int i, int j)
    {
        i = find(i);
        j = find(j);
        
        if(i != j)
        {
            if (rnk[i] < rnk[j])
                swap(i, j);
                
            parent[j] = i;
            
            rnk[i] += rnk[j];
        }
    }
};

template<typename V,typename E>
int Kruskal(Graph<V, E> &graph)
{
    // convert vertices and edges to numeric so we can apply the algorithm
    int cost = 0;
    int n = graph.vertices.size();
    graph.MST.clear();
    
    // Initialize the set
    Disjoint_int_set obj(n);
    
    // Todo
    // Sort Edges w.r.t weights
    graph.edges.sort([](const Graph<V, E>::Edge& a, const Graph<V, E>::Edge& b)
        {
            return a.weight < b.weight;
        });
    // Todo
    // For each of sorted edges add the edge that dosen't lead to cycle
    // and update total cost
    
    for(auto e : graph.edges)
    {
        int from_root = obj.find(e.from.ID);
        int to_root = obj.find(e.to.ID);
        
        if(from_root != to_root)
        {
            graph.MST.push_back(e);
            cost += e.weight;
            obj.Union(e.from.ID, e.to.ID);
        }
    }
    
    for(auto edg : graph.MST)
    {
        cout << edg.from.value <<" ->[" << edg.weight <<"]<- " << edg.to.value << endl;
    }
    
    // Return weight which is the minimum cost 
    return cost;
}

int main()
{
    //Implementation of Kruskal's algorithm
    Graph<string, int> graph = Graph<string, int>();
    
    Graph<string, int>::Vertex A = graph.addVertex("A");
    Graph<string, int>::Vertex B = graph.addVertex("B");
    Graph<string, int>::Vertex C = graph.addVertex("C");
    Graph<string, int>::Vertex D = graph.addVertex("D");
    Graph<string, int>::Vertex E = graph.addVertex("E");
    Graph<string, int>::Vertex F = graph.addVertex("F");
    Graph<string, int>::Vertex G = graph.addVertex("G");
    
    graph.addEdge(28, A, B);
    graph.addEdge(10, A, F);
    
    graph.addEdge(16, B, C);
    graph.addEdge(14, B, G);
    
    graph.addEdge(12, C, D);
    
    graph.addEdge(22, D, E);
    
    graph.addEdge(25, E, F);
    graph.addEdge(18, B, G);
    
    int cost = Kruskal(graph);
    
    cout << "Kruscal minimum cost = " << cost << endl;
    return 0;
}
