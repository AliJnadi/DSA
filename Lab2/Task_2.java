// Ali Jnadi

class Node<T>{
    T value;
    Node<T> next;
    
    public Node(T value, Node<T> next){
        this.value = value;
        this.next = next;
    }
}

interface Queue<T>{
    void offer(T item);
    T pool();
    T peek();
    int size();
    boolean isEmpty();
}

class NodeQueue<T> implements Queue<T>{
    Node<T> head;
    Node<T> tail;
    
    int queueSize;
    
    public NodeQueue(){
        this.head = null;
        this.tail = null;
        
        this.queueSize = 0;
    }
    
    @Override
    public int size(){
        return this.queueSize;
    }
    
    @Override
    public boolean isEmpty(){
        return (this.queueSize == 0);
    }
    
    @Override
    public void offer(T item)
    {
        if (this.head == null){
            this.head = new Node<>(item, null);
            this.tail = this.head;
        }
        else{
            this.tail.next = new Node<>(item, null);
            this.tail = this.tail.next;
        }
        this.queueSize++;
    }
    
    @Override 
    public T pool()
    {
        T item = this.head.value;
        this.head = this.head.next;
        if(this.head == null){
            this.tail = null;
        }
        this.queueSize--;
        return item;
    }
    
    @Override 
    public T peek(){
        return this.head.value;
    }
}

public class Main
{
	public static void main(String[] args) {
		Queue<Integer> queue = new NodeQueue<>();
		
		queue.offer(1);
		queue.offer(2);
		queue.offer(3);
		
		System.out.println(queue.pool());
		System.out.println(queue.pool());
		
		queue.offer(4);
		
		System.out.println(queue.peek());
		
		queue.offer(5);
		queue.offer(6);
		
		System.out.println(queue.pool());
        System.out.println(queue.pool());
        System.out.println(queue.pool());
        System.out.println(queue.pool());
        System.out.println(queue.pool());
	}
}
