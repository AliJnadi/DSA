// Ali Jnadi
import java.util.ArrayList;

interface Stack<T> {
    void push(T item);
    T pop();
    T peek();
    int size();
    boolean isEmpty();
}

class ArrayStack<T> implements Stack<T>{
    final int totalSize = 123;
    ArrayList<T> items;
    int stackSize;
    
    public ArrayStack(){
        this.items = new ArrayList<>();
        this.items.ensureCapacity(totalSize);
        this.stackSize = 0;
    }
    
    @Override
    public int size(){
        return this.stackSize;
    }
    
    @Override
    public boolean isEmpty(){
        return (this.stackSize == 0);
    }
    
    @Override
    public void push(T item){
        this.items.add(this.stackSize, item);
        this.stackSize++;
    }
    
    @Override
    public T pop(){
        if (this.stackSize <= 0){
            throw new RuntimeException("Cannot pop() from an empty stack");
        }
        this.stackSize--;
        T item = this.items.get(this.stackSize);
        this.items.remove(this.stackSize);
        return item;
    }
    
    @Override
    public T peek(){
        return this.items.get(this.stackSize - 1);
    }
}

public class Main
{
	public static void main(String[] args) {
		Stack<Integer> my_stack = new ArrayStack<>();
		my_stack.push(1);
        my_stack.push(2);
        System.out.println(my_stack.pop());
        my_stack.push(3);
        my_stack.push(4);
        my_stack.push(5);
        System.out.println(my_stack.pop());
        System.out.println(my_stack.pop());
        my_stack.push(6);
        System.out.println(my_stack.pop());
        System.out.println(my_stack.pop());
        System.out.println(my_stack.pop());
        System.out.println(my_stack.pop());
	}
}
