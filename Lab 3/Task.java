// Ali Jnadi


import java.util.LinkedList;
import java.util.List;


// Interface of Map ADT 
interface Map<K,V> 
{
    V get(K key);
    void put(K key, V value);
    void remove(K key);
    int size();
    boolean isEmpty();
}

class KeyValuePair<K, V> 
{
    K key;
    V value;

    public KeyValuePair(K key, V value)
    {
        this.key = key;
        this.value = value;
    }
}

class HashMap<K, V> implements Map<K, V> {
    List<KeyValuePair<K, V>>[] hashTable;
    int capacity; // size of hashTable (# of slots)
    int numberOfElements; // number of key-value pairs

    public HashMap(int capacity) 
    {
        this.capacity = capacity;
        this.numberOfElements = 0;
        this.hashTable = new List[capacity];
        for (int i = 0; i < capacity; i++)
            this.hashTable[i] = new LinkedList<>();
    }
    
    @Override 
    public void put(K key, V value) {
        int i = key.hashCode() % this.capacity;
        if(i < 0)
            i *= -1;
        for (KeyValuePair<K,V> kv : this.hashTable[i]) 
        {
            if (kv.key.equals(key))
            {
                kv.value = value;
                return;
            }
        }
        this.hashTable[i].add(
            new KeyValuePair(key, value)
        );
        ++this.numberOfElements;
        
    }
    
    @Override 
    public void remove(K key) 
    {
        int i = key.hashCode() % this.capacity;
        if(i < 0)
            i *= -1;
        for (KeyValuePair<K,V> kv : this.hashTable[i]) 
        {
            if (kv.key.equals(key))
                kv.value = null;
                break;
        }
    }
    
    @Override
    public V get(K key) 
    {
        int i = key.hashCode() % this.capacity;
        for (KeyValuePair<K,V> kv : this.hashTable[i]) 
        {
            if (kv.key.equals(key))
                return kv.value;
        }
        return null;
    }

    @Override
    public int size() { return this.numberOfElements; }

    @Override
    public boolean isEmpty() { return (this.numberOfElements == 0); }
}

public class Main {

    public static void main(String[] args) 
    {
        Map<String, Integer> hashMap = new HashMap<>(5);
    	hashMap.put("a", 123214);
    	hashMap.put("b", 123213);
    	
    	System.out.println("Value at key a " + hashMap.get("a"));
    	System.out.println("Value at key b " + + hashMap.get("b"));
    	System.out.println("size : " + hashMap.size());
    	System.out.println("is Empty: " + hashMap.isEmpty());
    	hashMap.remove("a");
    	System.out.println("size : " + hashMap.size());
    	hashMap.put("c", 234324);
    	System.out.println("size : " + hashMap.size());
    }
}
