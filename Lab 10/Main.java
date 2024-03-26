// Ali Jnadi

import java.util.ArrayList;
import java.util.List;

class Graph<V, E> {
    List<Vertex> vertices;
    List<Edge> edges;
    
    public Graph() {
        this.vertices = new ArrayList<Vertex>();
        this.edges = new ArrayList<Edge>();
    }
    
    class Vertex {
        V lable;
        List<Edge> adjacent;
        
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
}


public class Main
{
	public static void main(String[] args) {
		Graph<String, Integer> graph = new Graph<String, Integer>();
		Graph<String, Integer>.Vertex innopolis, kazan, moscow, cairo, tokyo, damascus;
		
		innopolis = graph.addVertex("Innopolis");
		kazan = graph.addVertex("Kazan");
		moscow = graph.addVertex("Moscow");
		cairo = graph.addVertex("Cairo");
		tokyo = graph.addVertex("Tokyo");
		damascus = graph.addVertex("Damascus");
		
		Graph.Edge e1 = graph.addEdge(innopolis, kazan, 40);
		Graph.Edge e2 = graph.addEdge(kazan, moscow, 1000);
		Graph.Edge e3 = graph.addEdge(moscow, cairo, 50000);
		Graph.Edge e4 = graph.addEdge(damascus, cairo, 5000);
		Graph.Edge e5 = graph.addEdge(kazan, tokyo, 60000);
		Graph.Edge e6 = graph.addEdge(moscow, tokyo, 40000);
		
		for(Graph.Vertex v : graph.vertices) {
		    System.out.println(v.lable);
		}
		
		for(Graph.Edge e : graph.edges) {
		    System.out.println(e.from.lable + " <--[ " + e.weight + " ]--> " + e.to.lable);
		}
		
		graph.removeVertex(cairo);
		
		for(Graph.Vertex v : graph.vertices) {
		    System.out.println(v.lable);
		}
		
	    System.out.println(graph.adjacent(innopolis, moscow));
	    System.out.println(graph.adjacent(moscow, cairo));
		
		for(Graph.Edge e : graph.edges) {
		    System.out.println(e.from.lable + " <--[ " + e.weight + " ]--> " + e.to.lable);
		}
		
		System.out.println(graph.adjacent(innopolis, moscow));
	    System.out.println(graph.adjacent(moscow, cairo));
	}
}
