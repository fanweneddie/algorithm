#include <stdio.h>
#include <stdlib.h>
// implementation of RBTree

enum Color
{
    RED,BLACK
};

// the node for RBTree
typedef struct RBNode
{
    int key;
    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
    enum Color color;
    // constructor for RBNode
}RBNode;

// red-black tree 
typedef struct RBTree
{
    struct RBNode* root;
    struct RBNode* nil;
}RBTree;

// ------------------------------------------
// function declarations
RBNode* init_RBNode(RBNode* init,int key_in);
RBTree* init_RBTree();
void left_rotate(RBTree* tree,RBNode* orig_parent);
void right_rotate(RBTree* tree,RBNode* orig_parent);
void RB_insert(RBTree* tree,RBNode* new_node);
void RB_insert_fixup(RBTree* tree,RBNode* new_node);
RBNode* RB_search_node(RBTree* tree,RBNode* node,int key_search);
RBNode* RB_search_tree(RBTree* tree,int key_search);
void RB_transplant(RBTree* tree,RBNode* orig_node,RBNode* new_node);
RBNode* RB_minimum(RBTree* tree,RBNode* node);
RBNode* RB_maximum(RBTree* tree,RBNode* node);
void RB_delete(RBTree* tree,RBNode* z);
void RB_delete_fixup(RBTree* tree,RBNode* x);
void RB_inorder_traverse(RBTree* tree,RBNode* node);
void RB_release_node(RBTree* tree,RBNode* node);
void RB_release_tree(RBTree* tree);
// ------------------------------------------


// *******************************************
// function definitions

// the constructor for RBNode
RBNode* init_RBNode(RBNode* init,int key_in)
{
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key_in;
    // for insert, node->color is RED
    // however, for nil, node->color is BLACK 
    node->color = RED;
    node->left = init;
    node->right = init;
    node->parent = init;
    return node;
}

// the constructor for RBTree
RBTree* init_RBTree()
{
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = init_RBNode(NULL,-1);
    tree->nil->color = BLACK;
    // root = nil denotes an empty tree
    tree->root = tree->nil;
    return tree;
}

// left_rotate between node orig_parent(x in CRLS) 
// and node orig_right( y = x->right in CRLS) 
void left_rotate(RBTree* tree,RBNode* orig_parent)
{
    // 1. reconnect x and y's original left child 
    RBNode* orig_right = orig_parent->right;
    orig_parent->right = orig_right->left;
    if(orig_right->left != tree->nil)
        orig_right->left->parent = orig_parent;
    
    // 2. reconnect y and x's original parent
    orig_right->parent = orig_parent->parent;
    if(orig_parent->parent == tree->nil)
        tree->root = orig_right;
    else 
    {
        if(orig_parent == orig_parent->parent->left)
            orig_parent->parent->left = orig_right;
        else
            orig_parent->parent->right = orig_right;
    }

    // 3. reconnect x and y
    orig_right->left = orig_parent;
    orig_parent->parent = orig_right;
}

// right_rotate between node orig_parent(x in CLRS)
// and node orig_left(y = x->left in CLRS) 
void right_rotate(RBTree* tree,RBNode* orig_parent)
{
    // 1. reconnect x and y's original right child 
    RBNode* orig_left = orig_parent->left;
    orig_parent->left = orig_left->right;
    if(orig_left->right != tree->nil)
        orig_left->right->parent = orig_parent;
    
    // 2. reconnect y and x's original parent
    orig_left->parent = orig_parent->parent;
    if(orig_parent->parent == tree->nil)
        tree->root = orig_left;
    else 
    {
        if(orig_parent == orig_parent->parent->left)
            orig_parent->parent->left = orig_left;
        else
            orig_parent->parent->right = orig_left;
    }

    // 3. reconnect x and y
    orig_left->right = orig_parent;
    orig_parent->parent = orig_left;
}


// insert new_node into RBTree tree
void RB_insert(RBTree* tree,RBNode* new_node)
{
    RBNode* up_node = tree->nil;
    RBNode* down_node = tree->root;
    // use up_node and down_node to search
    while(down_node != tree->nil)
    {
        up_node = down_node;
        if( new_node->key < down_node->key )
            down_node = down_node->left;
        else
            down_node = down_node->right;
    }
    // connect new_node and up_node
    new_node->parent = up_node;
    if(up_node == tree->nil)
        tree->root = new_node;
    else if(new_node->key < up_node -> key)
        up_node->left = new_node;
    else
        up_node->right = new_node;
    // revise the attribute of new_node
    new_node->left = tree->nil;
    new_node->right = tree->nil;
    new_node->color = RED;
    // maintain RB-tree structure
    RB_insert_fixup(tree,new_node);
}


// suppose new_node is just inserted into tree
// maintain the structure of RBTree
void RB_insert_fixup(RBTree* tree,RBNode* new_node)
{
    RBNode *uncle;
    while( new_node != tree->root 
        && new_node->parent->color == RED)
    {
        // uncle is the right uncle
        if(new_node->parent == new_node->parent->parent->left)
        {
            uncle = new_node->parent->parent->right;
            // case 1: uncle is red
            // cast the problem to the upper layer
            if(uncle->color == RED)
            {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            // uncle is black
            else
            {
                // case 2: uncle is black and new_node is a r_child
                // transform it to case 3
                if(new_node == new_node->parent->right)
                {
                    new_node = new_node->parent;
                    left_rotate(tree,new_node);
                }
                // case 3: uncle is black and new_node is a l_child
                // solve the problem
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                right_rotate(tree,new_node->parent->parent);
            }
        }
        // uncle is a left uncle
        else
        {
            uncle = new_node->parent->parent->left;
            // case 1: uncle is red
            // cast the problem to the upper layer
            if(uncle->color == RED)
            {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            // uncle is black
            else
            {
                // case 2: uncle is black and new_node is a l_child
                // transform it to case 3
                if(new_node == new_node->parent->left)
                {
                    new_node = new_node->parent;
                    right_rotate(tree,new_node);
                }
                // case 3: uncle is black and new_node is a r_child
                // solve the problem
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                left_rotate(tree,new_node->parent->parent);
            }// else
        }// else
    }// while
    tree->root->color = BLACK;
}


// search the key_search in RBNode node in RBTree tree recursively
// if found, return the RBNode that stores the key_search
// if not found, return tree->nil
RBNode* RB_search_node(RBTree* tree,RBNode* node,int key_search)
{
    if(node == tree->nil || node->key == key_search)
        return node;
    else if(key_search < node->key)
        return RB_search_node(tree,node->left,key_search);
    else
        return RB_search_node(tree,node->right,key_search);
}

// search the key_search in RBtree tree
// call RB_search_node
// if found, return the RBNode that stores the key_search
// if not found, return NULL
RBNode* RB_search_tree(RBTree* tree,int key_search)
{
    RBNode* node = RB_search_node(tree,tree->root,key_search);
    if(node == tree->nil)
        return NULL;
    else
        return node;
}

// replace orig_node with new_node
// can be used in node deletion
void RB_transplant(RBTree* tree,RBNode* orig_node,RBNode* new_node)
{
    // revise the root info if possible
    if(orig_node->parent == tree->nil)
        tree->root = new_node;
    // reconnect orig_node's parent and new_node
    else if(orig_node == orig_node->parent->left)
        orig_node->parent->left = new_node;
    else
        orig_node->parent->right = new_node;
    new_node->parent = orig_node->parent;
}

// get the min_node of node's subtree
RBNode* RB_minimum(RBTree* tree,RBNode* node)
{
    // search the leftmost node
    // and that is the minimal
    while(node->left != tree->nil)
        node = node->left;
    return node;
}

// get the max_node of node's subtree
RBNode* RB_maximum(RBTree* tree,RBNode* node)
{
    // search the rightmost node
    // and that is the maximal
    while(node->right != tree->nil)
        node = node->right;
    return node;
}

// delete node z in tree
// similar to delete in BSTree,
// but we need to fixup to maintain RBTree's structure
void RB_delete(RBTree* tree,RBNode* z)
{
    // hope:
    // y is the node being removed or moved
    // x is the node that take the place of original y
    RBNode* y = z;
    RBNode* x;
    // record y's original color
    // if that is red, we don't need to fixup
    // else, we should do fixup on x
    enum Color y_orig_color = y->color;
    // z only has right child
    if(z->left == tree->nil)
    {
        x = z->right;
        RB_transplant(tree,z,z->right);
    }
    // z only has left child
    else if(z->right == tree->nil)
    {
        x = z->left;
        RB_transplant(tree,z,z->left);
    }
    // z has left child and right child
    else
    {
        // y is z's successor
        y = RB_minimum(tree,z->right);
        // record y's original color
        y_orig_color = y->color;
        // y's left child must be nil
        // so y->right will take the place of y
        x = y->right;
        // link x to y directly
        if(y->parent == z)
            x->parent = y;
        // link x to y's parent, link y to z's rightchild
        else
        {
            RB_transplant(tree,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        // substitute z with y
        RB_transplant(tree,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        // do fix up on x
        if(y_orig_color == BLACK)
            RB_delete_fixup(tree,x);
    }
}

void RB_delete_fixup(RBTree* tree,RBNode* x)
{
    // w is x's brother
    RBNode* w;
    while(x != tree->root && x->color == BLACK )
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;
            // case 1: w is RED
            // let w = BLACK
            // transform to case 2/3/4
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree,x->parent);
                w = x->parent->right;
            }
            // case 2: w is BLACK and w's both children are BLACK
            // cast the problem to an upper layer
            if(w->left->color == BLACK && 
                    w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            // w is BLACK,but not both of w's children are BLACK
            else
            {
                // case 3: w's rightchild is BLACK
                // transform to case 4
                if(w->right->color == BLACK)
                {
                    w->color = RED;
                    w->left->color = BLACK;
                    right_rotate(tree,w);
                    w = x->parent->right;
                }
                // case 4: w's rightchild is RED
                // rotate to absorb the additional black
                // SOLVE IT!!!
                if(w->right->color == RED)
                {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(tree,x->parent);
                    // to break from while loop
                    x = tree->root;
                }
            }
        }
        // symmetrical to the upper case
        // exchange left and right
        else
        {
            w = x->parent->left;
            // case 1: w is RED
            // let w = BLACK
            // transform to case 2/3/4
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree,x->parent);
                w = x->parent->left;
            }
            // case 2: w is BLACK and w's both children are BLACK
            // cast the problem to an upper layer
            if(w->left->color == BLACK && 
                    w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            // w is BLACK,but not both of w's children are BLACK
            else
            {
                // case 3: w's leftchild is BLACK
                // transform to case 4
                if(w->left->color == BLACK)
                {
                    w->color = RED;
                    w->right->color = BLACK;
                    left_rotate(tree,w);
                    w = x->parent->left;
                }
                // case 4: w's leftchild is RED
                // rotate to absorb the additional black
                // SOLVE IT!!!
                if(w->left->color == RED)
                {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(tree,x->parent);
                    // to break from while loop
                    x = tree->root;
                }
            }// else
        }// else
    }// while
    x->color = BLACK;
}

// inorder traverse the node 
// if we want to traverse the tree, traverse its root
void RB_inorder_traverse(RBTree* tree,RBNode* node)
{
    if(node != tree->nil)
    {
        RB_inorder_traverse(tree,node->left);
        printf("%d ",node->key);
        RB_inorder_traverse(tree,node->right);
    }
}

// release node's subtree in a postorder way
void RB_release_node(RBTree* tree,RBNode* node)
{
    if(node!= tree->nil)
    {
        RB_release_node(tree,node -> left);
        RB_release_node(tree,node -> right);
        free(node);
    }
}

// release the RBTree
// by releasing its root and nil
void RB_release_tree(RBTree* tree)
{
    // if tree is empty, its root is nil
    // so RB_release_node does nothing
    RB_release_node(tree,tree->root);
    free(tree->nil);
    free(tree);
}

// *******************************************
int main()
{
    RBTree* T = init_RBTree();
    int a[10] = {41,38,31,12,19,8,0,4,5,100};
    for(int i = 0;i < 10;++i)
    {
        printf("inserting %d.\n",a[i]);
        RBNode* new_node = init_RBNode(NULL,a[i]);
        RB_insert(T,new_node);
        RB_inorder_traverse(T,T->root);
        printf("\n-----------------------------\n");
        
    }

    for(int i = 0;i < 8;++i)
    {
        if( RB_search_tree(T,i) )
            printf("find %d\n",i);
        else
            printf("fail to find %d\n",i);
    }

    for(int i = 0;i < 10;++i)
    {
        printf("deleting %d.\n",a[i]);
        RBNode* temp_node = RB_search_tree(T,a[i]);
        if(temp_node)
            RB_delete(T,temp_node);
        RB_inorder_traverse(T,T->root);
        printf("\n-----------------------------\n");
        
    }

    for(int i = 0;i < 10;++i)
    {
        printf("inserting %d.\n",a[i]);
        RBNode* new_node = init_RBNode(NULL,a[i]);
        RB_insert(T,new_node);
        RB_inorder_traverse(T,T->root);
        printf("\n-----------------------------\n");
        
    }

    RB_release_tree(T);
    return 0;
}

