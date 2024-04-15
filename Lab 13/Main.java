// Ali Jnadi

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Comparator;

class Graph<V, E> {
    List<Vertex> vertices;
    List<Edge> edges;
    final int inf = Integer.MAX_VALUE;
    
    public Graph() {
        this.vertices = new ArrayList<Vertex>();
        this.edges = new ArrayList<Edge>();
    }
    
    class Vertex {
        V lable;
        List<Edge> adjacent;
        int dist;
        
        public Vertex(V lable) {
            this.lable = lable;
            this.adjacent = new ArrayList<Edge>();
        }
    }
    
    class Edge {
        Vertex from;
        Vertex to;
        E weight;
        
        public Edge(Vertex from, Vertex to, E weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }
    }
    
    class Node implements Comparator<Node> {
        public Vertex node;
        public int cost;
        
        public Node() {
        }
        
        public Node(Vertex node, int cost) {
            this.node = node;
            this.cost = cost;
        }
        
        @Override
        public int compare(Node node1, Node node2) {
            if (node1.cost < node2.cost)
                return -1;
            if (node1.cost > node2.cost)
                return 1;
            return 0;
        }
    }
    
    Vertex addVertex(V lable) {
        Vertex v = new Vertex(lable);
        this.vertices.add(v);
        return v;
    }
    
    void removeVertex(Vertex v) {
        for(Edge e : v.adjacent) {
            if(!e.from.equals(v)) e.from.adjacent.remove(e);
            if(!e.to.equals(v)) e.to.adjacent.remove(e);
            this.edges.remove(e);
        }
        
        this.vertices.remove(v);
    }
    
    Edge addEdge(Vertex from, Vertex to, E weight) {
        Edge e = new Edge(from, to, weight);
        this.edges.add(e);
        from.adjacent.add(e);
        to.adjacent.add(e);
        return e;
    }
    
    void removeEdge(Edge e){
        e.from.adjacent.remove(e);
        e.to.adjacent.remove(e);
        this.edges.remove(e);
    }
    
    boolean adjacent(Vertex u, Vertex v) {
        for(Edge e : u.adjacent) {
            if(e.from.equals(v) || e.to.equals(v))
                return true;
        }
        return false;
    }
    
    void dijkstra(Vertex source) {
        int n = this.vertices.size();
        PriorityQueue<Node> pQueue = new PriorityQueue<Node>(n, new Node());
        
        for(Vertex v : vertices) {
            v.dist = this.inf;
        }
        source.dist = 0;
        
        pQueue.add(new Node(source, source.dist));
        
        while(pQueue.size() != 0) {
            Node element = pQueue.poll();
            Vertex v = element.node;
            int dist = element.cost;
            
            for(Edge e : v.adjacent) {
                if (dist + (int)e.weight < e.to.dist) {
                    e.to.dist = dist + (int)e.weight;
                    pQueue.add(new Node(e.to, e.to.dist));
                }
            }
        }
    }
}


public class Main
{
	public static void main(String[] args) {
		Graph<String, Integer> graph = new Graph<String, Integer>();
		Graph<String, Integer>.Vertex A, B, C, D, E, F;
		
		A = graph.addVertex("A");
		B = graph.addVertex("B");
		C = graph.addVertex("C");
		D = graph.addVertex("D");
		E = graph.addVertex("E");
		F = graph.addVertex("F");
		
		Graph.Edge AB = graph.addEdge(A, B, 4);
		Graph.Edge BA = graph.addEdge(B, A, 4);
		
		Graph.Edge AC = graph.addEdge(A, C, 4);
		Graph.Edge CA = graph.addEdge(C, A, 4);
		
		Graph.Edge BC = graph.addEdge(B, C, 2);
		Graph.Edge CB = graph.addEdge(C, B, 2);
		
		Graph.Edge CD = graph.addEdge(C, D, 3);
		Graph.Edge DC = graph.addEdge(D, C, 3);
		
		Graph.Edge CE = graph.addEdge(C, E, 1);
		Graph.Edge EC = graph.addEdge(E, C, 1);
		
		Graph.Edge CF = graph.addEdge(C, F, 6);
		Graph.Edge FC = graph.addEdge(F, C, 6);
		
		Graph.Edge DF = graph.addEdge(D, F, 2);
		Graph.Edge FD = graph.addEdge(F, D, 2);
		
		Graph.Edge EF = graph.addEdge(E, F, 3);
		Graph.Edge FE = graph.addEdge(F, E, 3);
		
		graph.dijkstra(A);
		
		for(Graph.Vertex v : graph.vertices) {
		    System.out.println("Path from " + A.lable + " to " + v.lable + " costs " + v.dist);
		}
	}
}
