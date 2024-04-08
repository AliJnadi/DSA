// Ali Jandi

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

interface DisjointSet {
    int find(int i);
    void union(int i, int j);
}

public class Kruskal {
    static class Edge implements Comparable<Edge> {
        int src;
        int dest;
        int weight;
        
        public Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }
        
        public int compareTo(Edge other) {
            return Integer.compare(weight, other.weight);
        }
    }
    
    public static List<Edge> kruskalMST(List<Edge> edges, int n) {
        DisjointSet disjoint = new DisjointSet() {
            int[] parent = new int[n];
            
            public int find(int i) {
                if (parent[i] == 0) {
                    return i;
                }
                parent[i] = find(parent[i]);
                return parent[i];
            }
            
            public void union(int i, int j) {
                parent[find(i)] = find(j);
            }
        };
        
        List<Edge> mst = new ArrayList<Edge>();
        Collections.sort(edges);
        
        for (Edge edge : edges) {
            if (disjoint.find(edge.src) != disjoint.find(edge.dest)) {
                disjoint.union(edge.src, edge.dest);
                mst.add(edge);
            }
        }
        
        return mst;
    }
    
    public static void main(String[] args) {
        List<Edge> edges = new ArrayList<Edge>();
        
        // Graph 1
        edges.add(new Edge(0, 1, 2));
        edges.add(new Edge(0, 2, 3));
        edges.add(new Edge(1, 2, 1));
        edges.add(new Edge(1, 3, 1));
        edges.add(new Edge(2, 3, 1));
        List<Edge> mst = kruskalMST(edges, 4); 
        
        // Graph 2
        // edges.add(new Edge(0, 1, 1));
        // edges.add(new Edge(1, 2, 2));
        // edges.add(new Edge(2, 3, 4));
        // edges.add(new Edge(3, 4, 3));
        // edges.add(new Edge(4, 5, 6));
        // edges.add(new Edge(5, 0, 7));
        // edges.add(new Edge(1, 4, 5));
        // List<Edge> mst = kruskalMST(edges, 6);
        
        System.out.println("Minimum Spanning Tree: ");
        for(Edge edge : mst) {
            System.out.println(edge.src + " -- " + edge.dest + " with weight " + edge.weight);
        }
    }
}