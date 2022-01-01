#include <stdio.h>
#include <stdlib.h>
#define INF 99999
// implementation of RBTree

// for RBNode's attribute color
enum Color
{
    RED,BLACK
};

// the node for RBTree
typedef struct RBNode
{
    // basic attributes for RBNode
    int key;
    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
    enum Color color;
    // additional attributes for RBNode
    // p = 1: this node is left endpoint
    // p = -1: this node is right endpoint
	int posFlag; // p in CLRS
    // v(x): the sum of p in x's subtree
	int sum_posFlag; // v in CLRS
    // m(x) = max s(l(x),i)
	int max_sum_posFlag_value;  // m in CLRS
    // o(x) = i such that s(l(x),i) is the max one
	int max_sum_posFlag_point; // o in CLRS
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
void left_rotate(RBTree* tree,RBNode* x);
void right_rotate(RBTree* tree,RBNode* x);
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
int max_among_3(int num_1,int num_2,int num_3,int* choice);
void maintain_maxOverlap_to_root(RBTree* tree,RBNode* node);
void maintain_maxOverlap_node(RBTree* tree,RBNode* node);
int find_maxOverlap_point(RBTree *tree);
int find_maxOverlap_value(RBTree* tree);
void RB_release_node(RBTree* tree,RBNode* node);
void RB_release_tree(RBTree* tree);
// ------------------------------------------


// *******************************************
// function definitions

// the constructor for RBNode
// initiate it as nil
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
    // initialize additional attributes for nil
    // nil's posflag can't be used
    node->posFlag = 1;
    node->sum_posFlag = 0;
    node->max_sum_posFlag_value = 0;
    node->max_sum_posFlag_point = key_in; 
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

// left_rotate between node x and node y(x->right) 
void left_rotate(RBTree* tree,RBNode* x)
{
    // 1. reconnect x and y's original left child 
    RBNode* y = x->right;
    x->right = y->left;
    if(y->left != tree->nil)
        y->left->parent = x;
    
    // 2. reconnect y and x's original parent
    y->parent = x->parent;
    if(x->parent == tree->nil)
        tree->root = y;
    else 
    {
        if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    // 3. reconnect x and y
    y->left = x;
    x->parent = y;

    maintain_maxOverlap_node(tree,x);
    maintain_maxOverlap_node(tree,y);
}

// right_rotate between node x and node y(x->left) 
void right_rotate(RBTree* tree,RBNode* x)
{
    // 1. reconnect x and y's original right child 
    RBNode* y = x->left;
    x->left = y->right;
    if(y->right != tree->nil)
        y->right->parent = x;
    
    // 2. reconnect y and x's original parent
    y->parent = x->parent;
    if(x->parent == tree->nil)
        tree->root = y;
    else 
    {
        if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    // 3. reconnect x and y
    y->right = x;
    x->parent = y;

    maintain_maxOverlap_node(tree,x);
    maintain_maxOverlap_node(tree,y);
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
        if( new_node->key < down_node->key || 
                (new_node->key == down_node->key 
                    && new_node->posFlag > down_node->posFlag) )
            down_node = down_node->left;
        else
            down_node = down_node->right;
    }
    // connect new_node and up_node
    new_node->parent = up_node;
    if(up_node == tree->nil)
        tree->root = new_node;
    else if(new_node->key < up_node -> key || 
                (new_node->key == up_node->key 
                    && new_node->posFlag > up_node->posFlag) )
        up_node->left = new_node;
    else
        up_node->right = new_node;
    // revise the attribute of new_node
    new_node->left = tree->nil;
    new_node->right = tree->nil;
    new_node->color = RED;
    // maintain maxOverlap 
    maintain_maxOverlap_to_root(tree,new_node);
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

        // maintain maxOverlap
        maintain_maxOverlap_to_root(tree,x->parent);
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
        printf("key: %d, posflag: %d,color: ",node->key,node->posFlag);
        if(node->color == RED)
            printf("red\n");
        else
            printf("black\n");
        printf("----- v: %d, m: %d, o: %d\n",node->sum_posFlag,node->max_sum_posFlag_value,node->max_sum_posFlag_point);
        printf("----- left key: %d, posflag: %d,\n",node->left->key,node->left->posFlag);
        printf("----- right key: %d, posflag: %d,\n",node->right->key,node->right->posFlag);

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

// return the max number among 3 input numbers
// and *choice denotes which number is selected as max
// number with lower index has a high priority when they equal.
int max_among_3(int num_1,int num_2,int num_3,int *choice)
{
    int max;
    if(num_1 >= num_2)
    {
        max = num_1;
        *choice = 1;
    }
    else
    {
        max = num_2;
        *choice = 2;
    }
    
    if(max < num_3)
    {
        max = num_3;
        *choice = 3;
    }
    return max; 
}

// get the max_overlap_point in RBTree in O(1)
int find_maxOverlap_point(RBTree *tree)
{
    return tree->root->max_sum_posFlag_point;
}

// get the overlap time of max_overlap_point in RBTree in O(1)
int find_maxOverlap_value(RBTree* tree)
{
    return tree->root->max_sum_posFlag_value;
}

// maintain the attribute of maxOverlap from node to root
void maintain_maxOverlap_to_root(RBTree* tree,RBNode* node)
{
    int *choice = (int*)malloc(sizeof(int));
    // from bottom to top
    while(node != tree->nil)
    {
        // maintain sum_posFlag(v)
        // v(x) = v(x.left) + x.p + v(x.right)
        node->sum_posFlag = node->left->sum_posFlag 
            + node->posFlag + node->right->sum_posFlag;
        // in case of x.posFlag = -1 and left_child is nil
        // then, x.left.m = 0 is bigger than -1
        int left_max_sum_posFlag_value;
        if(node->left == tree->nil)
            left_max_sum_posFlag_value = -INF;
        else
            left_max_sum_posFlag_value = node->left->max_sum_posFlag_value;
        // maintain max_sum_posFlag_value(m)
        // m(x) = max( m(x.left),v(x.left) + x.p,v(x.left) + x.p + m(x.right) )
        node->max_sum_posFlag_value 
            = max_among_3(left_max_sum_posFlag_value,
                node->left->sum_posFlag + node->posFlag,
                node->left->sum_posFlag + node->posFlag 
                    + node->right->max_sum_posFlag_value,choice);
        // maintain max_sum_posFlag_point(o)
        // depends on the choice of m
        if(*choice == 1)
            node->max_sum_posFlag_point 
                = node->left->max_sum_posFlag_point;
        else if(*choice == 2)
            node->max_sum_posFlag_point = node->key;
        else
            node->max_sum_posFlag_point 
                = node->right->max_sum_posFlag_point;
        node = node->parent;
    }
    free(choice);
}

// maintain the attribute of maxOverlap of the node
void maintain_maxOverlap_node(RBTree* tree,RBNode* node)
{
    int *choice = (int*)malloc(sizeof(int));
    // maintain sum_posFlag(v)
    // v(x) = v(x.left) + x.p + v(x.right)
    node->sum_posFlag = node->left->sum_posFlag 
        + node->posFlag + node->right->sum_posFlag;
    // in case of x.posFlag = -1 and left_child is nil
    // then, x.left.m = 0 is bigger than -1
    int left_max_sum_posFlag_value;
    if(node->left == tree->nil)
        left_max_sum_posFlag_value = -INF;
    else
        left_max_sum_posFlag_value = node->left->max_sum_posFlag_value;
    // maintain max_sum_posFlag_value(m)
    // m(x) = max( m(x.left),v(x.left) + x.p,v(x.left) + x.p + m(x.right)
    node->max_sum_posFlag_value 
        = max_among_3(left_max_sum_posFlag_value,
            node->left->sum_posFlag + node->posFlag,
            node->left->sum_posFlag + node->posFlag 
                + node->right->max_sum_posFlag_value,choice);
    // maintain max_sum_posFlag_point(o)
    // depends on the choice of m
    if(*choice == 1)
        node->max_sum_posFlag_point 
            = node->left->max_sum_posFlag_point;
    else if(*choice == 2)
        node->max_sum_posFlag_point = node->key;
    else
        node->max_sum_posFlag_point 
            = node->right->max_sum_posFlag_point;
    node = node->parent;
    free(choice);
}

// *******************************************
int main()
{
    RBTree* T = init_RBTree();
    int interval[5][2] = { {1,2},{3,5},{4,6},{5,7},{8,9} };
    int flag[2] = {1,-1};
    for(int i = 0;i < 5;++i)
    {
        for(int j = 0;j <=1;++j)
        {
            printf("inserting %d\n",interval[i][j]);
            RBNode* new_node = init_RBNode(NULL,interval[i][j]);
            new_node->posFlag = flag[j];
            RB_insert(T,new_node);
            RB_inorder_traverse(T,T->root);
            printf("\n-----------------------------\n");
        }   
    }

    int maxOverlap_point = find_pom(T);
    int maxOverlap_time = find_overlap_time(T);
    printf("max overlap point is %d, max overlap time is %d.\n",maxOverlap_point,maxOverlap_time);
    RB_release_tree(T);
    return 0;
}
