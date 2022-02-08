/*
Problem: https://leetcode-cn.com/problems/OrIXps/

Solution: double-directed linkedlist + hashmap

Complexity:
	For each get and put operation, time cost is O(1).
*/

class MyListNode {
    public int key;
    public int value;
    public MyListNode last;
    public MyListNode next;

    public MyListNode(int key, int value) {
        this.key = key;
        this.value = value;
        this.last = null;
        this.next = null;
    }
}

class MyList {
    private MyListNode head;
    private MyListNode tail;
    private int capacity;
    private int size;

    public MyList(int capacity) {
        this.head = new MyListNode(-1, -1);
        this.tail = new MyListNode(-2, -2);
        head.next = tail;
        tail.last = head;
        this.capacity = capacity;
        this.size = 0;
    }

    // we make sure that node is in MyList
    // and it is not null
    public void deleteNode(MyListNode node) {
        MyListNode last_node = node.last;
        MyListNode next_node = node.next;
        last_node.next = next_node;
        next_node.last = last_node;
        size--;
    }

    // we make sure that node is not null and it is not in MyList.
    // Also, MyList is not full
    public void addFront(MyListNode node) {
        MyListNode first_node = head.next;
        first_node.last = node; 
        node.next = first_node;
        head.next = node;
        node.last = head;
        size++;
    }

    public MyListNode getLastNode() {
        return tail.last;
    }

    public boolean isFull() {
        return size == capacity;
    }

    public boolean checkFirstNode(MyListNode node) {
        return head.next == node;
    }
}

class LRUCache {
    private HashMap<Integer, MyListNode> map;
    private MyList list; 

    public LRUCache(int capacity) {
        this.map = new HashMap<Integer, MyListNode>();
        this.list = new MyList(capacity);
    }
    
    public int get(int key) {
        int value;
        if (map.containsKey(key)) {
            MyListNode node = map.get(key);
            // move the node to front
            if (!list.checkFirstNode(node)) {
                list.deleteNode(node);
                list.addFront(node);
            }
            value = node.value;
        } else {
            value = -1;
        }
        return value;
    }
    
    public void put(int key, int value) {
        if (map.containsKey(key)) {
            MyListNode node = map.get(key);
            node.value = value;
            // move the node to front
            if (!list.checkFirstNode(node)) {
                list.deleteNode(node);
                list.addFront(node);
            }
        } else {
            // delete the least recently used key
            if (list.isFull()) {
                MyListNode last_node = list.getLastNode();
                int last_key = last_node.key;
                int last_value = last_node.value;
                map.remove(last_key);
                list.deleteNode(last_node);
            }
            // init a new node and put it to front
            MyListNode new_node = new MyListNode(key, value);
            map.put(key, new_node);
            list.addFront(new_node);
        }
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
