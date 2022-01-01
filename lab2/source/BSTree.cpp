#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BSNode
{   
public:
    T key;
    BSNode* parent;
    BSNode* l_child;
    BSNode* r_child;
    // constructor without parameter
    BSNode()
    {
        parent = NULL;
        l_child = NULL;
        r_child = NULL;
    }
    // constructor with parameter
    BSNode(const T key_in)
    {
        key = key_in;
        parent = NULL;
        l_child = NULL;
        r_child = NULL;
    }
};

template<typename T>
class BSTree
{
private:
    BSNode<T>* root;
public:
    // constructor
    BSTree()
    {
        root = new BSNode<T>();
        root = NULL;
    }

    // get root ptr
    BSNode<T>* get_root() const
    {
        return root;
    } 

    // insert a key into the BSTree
    void insert(const T key_in)
    {
        BSNode<T>* up_node = NULL;
        BSNode<T>* down_node = root;
        BSNode<T>* new_node = new BSNode<T>(key_in);
        while(down_node)
        {
            up_node = down_node;
            if(key_in < down_node->key)
                down_node = down_node->l_child;
            else
                down_node = down_node->r_child;
        }
        new_node->parent = up_node;
        if(!up_node)
            root = new_node;
        else if(key_in < up_node -> key)
            up_node -> l_child = new_node;
        else
            up_node -> r_child = new_node;
    }

    // delete node in this BSTree,
    // and do some operation to maintain the BST
    // (note that node is not NULL).
    // before return, delete node
    void delete_node(BSNode<T>* node)
    {
        // by default, node is not NULL
        if(node == NULL)
            return;

        // node's left child is NULL
        if(node->l_child == NULL)
            transplant(node,node->r_child);
        // node's left child is not NULL
        // but its right child is NULL
        else if(node->r_child == NULL)
            transplant(node,node->l_child);
        // node has both children
        else
        {
            BSNode<T>* suc = successor(node);
            if(suc->parent != node)
            {
                transplant(suc,suc->r_child);
                suc->r_child = node->r_child;
                suc->r_child->parent = suc;
            }
            transplant(node,suc);
            suc->l_child = node->l_child;
            suc->l_child->parent = suc;
        }
        delete node;
    }

    // search the node of key_search in BSTree 
    BSNode<T>* search_tree(T key_search)
    {
        return search_node(root,key_search);
    }

    // search key_search in the tree in a special way
    void search_tree_special(T key_search)
    {
        if(root)
            search_node_special(root,key_search);
    }

    // in order traverse the tree
    void inorder_traverse_tree()
    {
        inorder_traverse_node(root);
        cout << endl;
    }

    // destructor
    ~BSTree()
    {
        release_node(root);
    }

private:
    
    //delete the the tree in a post order.
    void release_node(BSNode<T>* node)
    {
        if(node)
        {
            release_node(node -> l_child);
            release_node(node -> r_child);
            delete node;
            node = NULL;
        }
    }
    
    // inorder traverse the node 
    void inorder_traverse_node(const BSNode<T>* node)
    {
        if(node)
        {
            inorder_traverse_node(node->l_child);
            cout << node->key << " ";
            inorder_traverse_node(node->r_child);
        }
    }

    // get the min_node of node's subtree
    BSNode<T>* minimum(BSNode<T>* node)
    {
        while(node -> l_child)
            node = node -> l_child;
        return node;
    }

    // get the max_node of node's subtree
    BSNode<T>* maximum(BSNode<T>* node)
    {
        while(node -> r_child)
            node = node -> r_child;
        return node;
    }

    // get the first node whose key is bigger
    // than node's key
    BSNode<T>* successor(BSNode<T>* node)
    {
        BSNode<T>* this_node = node;
        if(this_node -> r_child)
            return minimum(this_node -> r_child);
        
        BSNode<T>* up_node = this_node->parent;
        while(up_node && this_node == up_node -> r_child)
        {
            this_node = up_node;
            up_node = this_node -> parent;
        }
        return up_node;
    }

    // get the first node whose key is smaller
    // than node's key
    BSNode<T>* predecessor(BSNode<T>* node)
    {
        BSNode<T>* this_node = node;
        if(this_node -> l_child)
            return maximum(this_node -> l_child);
        
        BSNode<T>* up_node = this_node->parent;
        while(up_node && this_node == up_node -> l_child)
        {
            this_node = up_node;
            up_node = this_node -> parent;
        }
        return up_node;
    }

    // search key_search in node
    // if we have found, return the node
    // if we haven't found that key in the tree, return null
    // else search recursively
    BSNode<T>* search_node(BSNode<T>* node,const T key_search)
    {
        // have found or haven't found
        if(node == NULL || key_search == node->key)
        {
            return node;
        }
        // search recursively in left child
        if(key_search < node->key)
            return search_node(node->l_child,key_search);
        // search recursively in right child
        else
            return search_node(node->r_child,key_search);
    }

    // special case in search for a specific OJ problem
    void search_node_special(BSNode<T>* node,const T key_search)
    {
        if(key_search == node->key)
        {
            cout << key_search << endl;
            return;
        }
        else
        {
            if(key_search < node->key)
            {
                if(node->l_child)
                {
                    search_node_special(node->l_child,key_search);
                    return;
                }
                else
                {
                    cout << predecessor(node) -> key << endl;
                    return;
                }
            }
            // key_search > node->key
            else
            {
                if(node->r_child)
                {
                    search_node_special(node->r_child,key_search);
                    return;
                }
                else
                {
                    cout << node -> key << endl;
                    return;
                }
            }
        }
    }

    // in a tree, substitute orig_node with new_node
    // so it also transplant new_node's subtree into that tree
    // note that I haven't deleted orig_node, 
    // and it may cause memory leakage
    void transplant(BSNode<T>* orig_node,BSNode<T>* new_node)
    {
        // orig_node is root
        if( !orig_node -> parent )
            root = new_node;
        else if(orig_node == orig_node -> parent -> l_child)
            orig_node -> parent -> l_child = new_node;
        else
            orig_node -> parent -> r_child = new_node;
        if(new_node)
            new_node -> parent = orig_node -> parent;
    }
};


int main()
{
    int a[5] = {2,1,4,5,3};
    // test insert
    BSTree<int> bst = BSTree<int>();
    for(int i = 0;i < 5;++i)
    {
        bst.insert(a[i]);
    }

    // test delete
    for(int i = 0; i < 5;++i)
    {
        bst.delete_node( bst.search_tree(a[i]) );
        cout << "delete " << a[i] << " in BSTree.\n";
        bst.inorder_traverse_tree();
    }

/*  
    // test special search
    int s[5] = {1,2,6,6,6};
    for(int i = 0;i < 5;++i)
    {
        bst.search_tree_special(s[i]);
    }
*/
    return 0;
}
