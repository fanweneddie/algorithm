/*
Problem: https://leetcode-cn.com/problems/delete-node-in-a-bst/

Solution1: search a node in BST and delete that node, which is a little troublesome to implement

Complexity:
	Time: O(n),
	Space: O(1), where n is the size of BST
	
Solution2: DFS

Complexity:
	Time: O(n),
	Space: O(n), where n is the size of BST
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution1 {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* node = nullptr; 
        TreeNode* node_parent = nullptr;
        searchKey(root, key, node_parent, node);
        TreeNode* parent = nullptr;
        TreeNode* leaf = nullptr;
        // key is not found
        if (!node) {
            return root;
        }
        // key is found, delete that node by replacement
        else {
            if (node->left) {
                getRightMostOfLeftChild(node, parent, leaf);
                deleteChild(parent, leaf, 1);
                substitute(node_parent, node, leaf);
                if (node_parent) {
                    return root;
                } else {
                    return leaf;
                }
            } else if (node->right) {
                getLeftMostOfRightChild(node, parent, leaf);
                deleteChild(parent, leaf, 0);
                substitute(node_parent, node, leaf);
                if (node_parent) {
                    return root;
                } else {
                    return leaf;
                }
            } else {
                if (node_parent) {
                    deleteChild(node_parent, node, 0);
                    return root;
                } else {
                    return nullptr;
                }
            }
        }
    }

private:
    // Search the key in the subtree of root
    // If the key is found, return the parent and the node that contains that key.
    // Else, return null
    void searchKey(TreeNode* root, int key, TreeNode*& parent, TreeNode*& cur) {
        parent = nullptr;
        cur = root;
        while (cur) {
            if (key == cur->val) {
                break;
            } else if (key < cur->val) {
                parent = cur;
                cur = cur->left;
            } else {
                parent = cur;
                cur = cur->right;
            }
        }
    }

    // we should make sure that root->right is not null
    void getLeftMostOfRightChild(TreeNode* root, TreeNode*& parent, TreeNode*& leaf) {
        TreeNode* cur = root->right;
        if (!cur->left) {
            parent = root;
            leaf = cur;
            return;
        }

        while (cur->left && cur->left->left) {
            cur = cur->left;
        }
        parent = cur;
        leaf = cur->left;
    }

    // we should make sure that root->left is not null
    void getRightMostOfLeftChild(TreeNode* root, TreeNode*& parent, TreeNode*& leaf) {
        TreeNode* cur = root->left;
        if (!cur->right) {
            parent = root;
            leaf = cur;
            return;
        }

        while (cur->right && cur->right->right) {
            cur = cur->right;
        }
        parent = cur;
        leaf = cur->right;
    }

    // Subtitute node with sub
    // we make sure that root and sub are not null
    void substitute(TreeNode*& node_parent, TreeNode*& node, TreeNode*& sub) {
        sub->left = node->left;
        sub->right = node->right;
        
        if (node_parent) {
            if (node_parent->left == node) {
                node_parent->left = sub;
            } else {
                node_parent->right = sub;
            }
        }
    }
    
    void deleteChild(TreeNode*& parent, TreeNode* child, int opt) {
        // after calling getRightMostOfLeftChild
        if (opt == 1) {
            if (parent->left == child) {
                parent->left = child->left;
            } else {
                parent->right = child->left;
            }
        } 
        // after calling getLeftMostOfRightChild
        else {
            if (parent->left == child) {
                parent->left = child->right;
            } else {
                parent->right = child->right;
            }
        }
    } 
};

class Solution2 {
public:
    // Return the root node of tree after the deletion of key in root's subtree
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        // delete current node 
        else {
            if (!root->left) {
                return root->right;
            } else if (!root->right) {
                return root->left;
            } else {
                TreeNode* new_root = root->right;
                TreeNode* pre = root->left;
                TreeNode* next = root->right;
                while (next->left) {
                    next = next->left;
                }
                next->left = pre;
                root = new_root;
            }
        }

        return root;
    }
};
