#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// implementation of RBTree
enum Color
{
    RED,BLACK
};

// the node for RBTree
// each node represents a interval
typedef struct RBNode
{
    // the low end of an interval
    int low;
    // the high end of an interval
    int high;
    // the max end of the node's subtree
    int max;
    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
    enum Color color;
}RBNode;

// red-black tree 
typedef struct RBTree
{
    struct RBNode* root;
    struct RBNode* nil;
}RBTree;

// ------------------------------------------
// function declarations
int get_max(int a,int b,int c);
RBNode* init_RBNode(RBNode* init,int low_in,int high_in);
RBTree* init_RBTree();
void left_rotate(RBTree* tree,RBNode* orig_parent);
void right_rotate(RBTree* tree,RBNode* orig_parent);
void RB_insert(RBTree* tree,RBNode* new_node);
void RB_insert_fixup(RBTree* tree,RBNode* new_node);
int do_overlap(int x_low,int x_high,int y_low,int y_high);
int search_overlap_interval(RBTree* tree,int low_in,int high_in);
void RB_transplant(RBTree* tree,RBNode* orig_node,RBNode* new_node);
RBNode* RB_minimum(RBTree* tree,RBNode* node);
RBNode* RB_maximum(RBTree* tree,RBNode* node);
//void RB_delete(RBTree* tree,RBNode* z);
//void RB_delete_fixup(RBTree* tree,RBNode* x);
RBNode* RB_predecessor(RBTree* tree,RBNode* node);
void RB_inorder_traverse(RBTree* tree,RBNode* node);
void RB_release_node(RBTree* tree,RBNode* node);
void RB_release_tree(RBTree* tree);
// ------------------------------------------


// *******************************************
// function definitions

// get the max number of a,b,c
int get_max(int a,int b,int c)
{
    int max;
    max = a > b ? a:b;
    max = max > c ? max:c;
    return max;
}

// the constructor for RBNode
RBNode* init_RBNode(RBNode* init,int low_in,int high_in)
{
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->low = low_in;
    node->high = high_in;
    node->max = high_in;
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
    tree->nil = init_RBNode(NULL,-1,-1);
    // the attributes that denote a nil
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

    // 4. maintain the max of new x and y
    orig_right->max = orig_parent->max;
    orig_parent->max = get_max(orig_parent->left->max,
            orig_parent->right->max,orig_parent->high);
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

    // 4. maintain the max of new x and y
    orig_left->max = orig_parent->max;
    orig_parent->max = get_max(orig_parent->left->max,
            orig_parent->right->max,orig_parent->high);
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
        if( new_node->low < down_node->low )
            down_node = down_node->left;
        else
            down_node = down_node->right;
    }
    // connect new_node and up_node
    new_node->parent = up_node;
    if(up_node == tree->nil)
        tree->root = new_node;
    else if(new_node->low < up_node->low)
        up_node->left = new_node;
    else
        up_node->right = new_node;
    // revise the attribute of new_node
    new_node->left = tree->nil;
    new_node->right = tree->nil;
    new_node->color = RED;
    // increment the size after insert in a bottom up way
    RBNode* temp_node = new_node->parent;
    while(temp_node != tree->nil)
    {
        temp_node->max = get_max(temp_node->left->max,
            temp_node->right->max,temp_node->high);
        temp_node = temp_node->parent;
    }
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


// check whether the interval of node_x and node_y overlaps
// if they overlaps, return 1; else return 0;
int do_overlap(int x_low,int x_high,int y_low,int y_high)
{
    // overlap
    if( x_low <= y_high && 
        y_low <= x_high )
        return 1;
    // no overlap
    else
        return 0;
}

// let a node represents [low_in,high_in]
// search node's overlap interval in tree
// if found a temp_node whose interval overlaps with node's, 
// return 1
// else, return 0;
int search_overlap_interval(RBTree* tree,int low_in,int high_in)
{
    RBNode* temp_node = tree->root;
    // the while loop to search for the possible overlap interval
    while( temp_node != tree->nil 
        && do_overlap(temp_node->low,
            temp_node->high,low_in,high_in) == 0 )
    {
        // search for the left
        if(temp_node->left != tree->nil 
            && temp_node->left->max >= low_in)
            temp_node = temp_node->left;
        // search for the right
        else
            temp_node = temp_node->right;
    }
    if(temp_node != tree->nil)
        return 1;
    else
        return 0;
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

// get the first node whose key is smaller
// than node's key
RBNode* RB_predecessor(RBTree* tree,RBNode* node)
{
    RBNode* this_node = node;
    if(this_node -> left != tree->nil)
        return RB_maximum(tree,this_node -> left);
        
    RBNode* up_node = this_node->parent;
    while(up_node != tree->nil 
        && this_node == up_node -> left)
    {
        this_node = up_node;
        up_node = this_node -> parent;
    }
    return up_node;
}

/*
// delete node z in tree
// similar to delete in BSTree,
// but we need to fixup to maintain RBTree's structure
void RB_delete(RBTree* tree,RBNode* z)
{
    // hope:
    // y is the node being removed or moved
    // x is the node that take the place of original y
    // z_parent is the node of original z's parent
    RBNode* y = z;
    RBNode* x;
    RBNode* z_parent = z->parent;
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
        {
            x->parent = y;
            y->size = z->size-1;
        }
        // link x to y's parent, link y to z's rightchild
        else
        {
            RB_transplant(tree,y,y->right);
            z_parent = y->right->parent;
            y->right = z->right;
            y->right->parent = y;
            y->size = z->size;
        }
        // substitute z with y
        RB_transplant(tree,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        //y->size--;
        //y->size = y->left->size + y->right->size + 1;
    }// else
    
    // decrement size from z_parent in a bottom up way
    while(z_parent != tree->nil)
    {
        z_parent->size--;
        z_parent = z_parent->parent;
    }
    // do fix up on x
    if(y_orig_color == BLACK)
        RB_delete_fixup(tree,x);
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
*/

// inorder traverse the node 
// if we want to traverse the tree, traverse its root
void RB_inorder_traverse(RBTree* tree,RBNode* node)
{
    if(node != tree->nil)
    {
        RB_inorder_traverse(tree,node->left);
        printf("[%d,%d] ",node->low,node->high);
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


// print the info of this node whose depth is _depth_
void print_node(RBTree* tree, RBNode* node,int depth,int pos)
{
    char buffer[100];
    buffer[0] = '\0';
    if(node == tree->nil)
        return;
    for(int i = 1;i < depth;++i)
        strcat(buffer,"     ");
    if(depth > 0)
    {
        if(pos == 0)
            strcat(buffer,"|L---");
        else
            strcat(buffer,"|R---");
    }
    char C;
    if(node->color == RED)
        C = 'R';
    else
        C = 'B';
    
    printf("%s[%d,%d]\n",buffer,node->low,node->high);
    print_node(tree,node->left,depth+1,0);
    print_node(tree,node->right,depth+1,1);     
}

int main()
{
    // number of requests
    int req_num;
    // temporary low end and high end
    int temp_low,temp_high;
    // a 0-(-1) array to store results
    int *results;

    scanf("%d",&req_num);
    results = (int*)malloc(req_num*sizeof(int));
    RBTree* mem_record = init_RBTree();
    // malloc
    for(int i = 0;i < req_num;++i)
    {
        scanf("%d%d",&temp_low,&temp_high);
        // no overlap,malloc success,insert that interval
        if( search_overlap_interval(mem_record,
                temp_low,temp_high) == 0 )
        {
            RBNode* new_node = init_RBNode(NULL,temp_low,temp_high);
            RB_insert(mem_record,new_node);
            results[i] = 0;
        }
        // overlap,malloc failed
        else
            results[i] = -1;
    }
    // print results
    for(int i = 0; i < req_num;++i)
    {
        printf("%d\n",results[i]);
    }
    RB_release_tree(mem_record);
    free(results);
    return 0;
}
