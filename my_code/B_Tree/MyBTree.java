import java.util.LinkedList;

// my implementation of B-tree
// the data stored in this B-tree are integer
class MyBTreeNode
{
    // the minimal degree of a non-root node is 2
    // and the maximal degree of a non-root node is 4
    public static final int MIN_DEGREE = 2;
    // marks whether this node is a leaf node
    public boolean is_leaf;
    // child_num = key_num + 1;
    public int key_num;
    // the set of keys and children of this node
    public LinkedList<Integer> keys;
    public LinkedList<MyBTreeNode> children;

    // constructor to initialize a new node
    public MyBTreeNode()
    {
        this.is_leaf = true;
        this.key_num = 0;
        this.keys = new LinkedList<Integer>();
        this.children = new LinkedList<MyBTreeNode>();
    }

    // split the node's i_th child
    // Note that the node is not full
    // and its i_th child is full
    public void split_child(int i)
    {
        MyBTreeNode orig_child = children.get(i);
        // temporarily stores the middle key to be raised up
        int key_up = orig_child.keys.get(MIN_DEGREE-1);
        MyBTreeNode new_child = new MyBTreeNode();
        // -----------------------------------------
        // firstly, copy the last half keys and children 
        // from orig_child to new child
        // -----------------------------------------
        new_child.is_leaf = orig_child.is_leaf;
        new_child.key_num = MIN_DEGREE - 1;
        // copy MIN_DEGREE - 1 keys from orig_child to new_child
        for(int j = 0; j < MIN_DEGREE -1;++j)
        {
            new_child.keys.addLast(0);
            new_child.keys.set( j,orig_child.keys.get(MIN_DEGREE + j) );
            orig_child.keys.remove(MIN_DEGREE + j);
        }
        orig_child.keys.removeLast();
        // copy MIN_DEGREE - 1 children from orig_child to new child
        if( !orig_child.is_leaf )
        {
            for(int j = 0; j < MIN_DEGREE ;++j)
            {
                new_child.children.addLast(null);
                new_child.children.set( j, 
                        orig_child.children.get(MIN_DEGREE) ); 
                orig_child.children.remove(MIN_DEGREE);
            }
        }
        // truncate the orignal child
        orig_child.key_num = MIN_DEGREE - 1;
        // -----------------------------------------
        // secondly, save the changes to this child
        // -----------------------------------------
        // right shift the children in this node one by one
        this.children.addLast(null);
        for(int j = key_num;j >= i + 1;--j)
        {   
            this.children.set( j+1, this.children.get(j) );
        }
        // link the new child to this child
        this.children.set(i+1, new_child);
        // right shift the keys in this node one by one
        this.keys.addLast(0);
        for(int j = key_num;j > i;--j)
        {
            this.keys.set( j,this.keys.get(j-1) );
        }
        // add the new key to this child
        this.keys.set( i, key_up );
        this.key_num++;
    }

    // insert key k to a nonfull node(this node)
    public void insert_to_nonfull(int k)
    {
        int i = this.key_num - 1;
        // 1. this node is a leaf node,
        // insert the key into this node
        if(this.is_leaf)
        {
            // just expand the length of keys
            this.keys.addLast(0);
            // right shift the keys in this node one by one
            while( i >= 0 && k < this.keys.get(i) )
            {
                this.keys.set(i+1, this.keys.get(i));
                --i;
            }
            // insert the new key into the keys in this node
            this.keys.set(i+1, k);
            this.key_num++;
        }
        // 2. this node is not a leaf node
        // insert the key into its proper child node
        else
        {
            // look for k's closest key
            while( i>=0 && k < this.keys.get(i) )
                --i;
            i++;
            // if children[i] is full, split it 
            if( this.children.get(i).key_num == 2*MIN_DEGREE - 1 )
            {
                split_child(i);
                // after split, adjust the right child to insert
                if( k > this.keys.get(i) )
                    ++i;
            }
            // insert k to children[i] recursively
            this.children.get(i).insert_to_nonfull(k);
        }
    }

    // print the info of this node whose depth is _depth_
    public void print_node(int depth)
    {
        StringBuilder sb = new StringBuilder();
        for(int i = 1;i < depth;++i)
            sb.append("|    ");
        if(depth > 0)
            sb.append("|----");
        sb.append(this.keys);
        System.out.println( sb.toString() );
        for( MyBTreeNode child : this.children )
        {
            child.print_node(depth+1);
        }
    }
}

// the class of B-tree
// the data type of key is int(integer)
public class MyBTree
{
    private MyBTreeNode root;
    private int height;

    public MyBTreeNode get_root()
    {
        return root;
    }

    public int get_height()
    {
        return height;
    }

    // constructor to initialize
    // the empty root of a B-Tree
    public MyBTree()
    {
        root = new MyBTreeNode();
        height = 0;
    }

    // insert a key "k" to this B-Tree
    public void insert(int k)
    {
        // 1. the root is full
        // find another node as a new_root
        // and split its 0th child
        if(root.key_num == 2*MyBTreeNode.MIN_DEGREE - 1)
        {
            MyBTreeNode new_root = new MyBTreeNode();
            new_root.is_leaf = false;
            new_root.children.add(0,root);
            root = new_root;
            root.split_child(0);
            // insert k to the proper child of root
            root.insert_to_nonfull(k);
        }
        // 2. the root is not full
        // insert k to the proper child of root
        else
            root.insert_to_nonfull(k);
    }

    // print this B-Tree to show the result
    public void print_BTree()
    {
        root.print_node(0);
    }

    public static void main(String args[])
    {
        MyBTree mbt = new MyBTree();
        for(int i = 0; i < 15;++i)
            mbt.insert(i);
        mbt.print_BTree();
    }
}