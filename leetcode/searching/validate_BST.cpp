/*
Problem: https://leetcode-cn.com/problems/validate-binary-search-tree/
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
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        } else {
            long long temp1 = 0;
            long long temp2 = 0;
            return isValidBSTWithValue(root, temp1, temp2);
        }
    } 
	
    // This function not only checks whether the subtree of current root is valid BST by inorder iteration,
    // but also get the min value and max value in this subtree	
    // we guarantee that root is not NULL
    bool isValidBSTWithValue(TreeNode* root, long long& min_val, long long& max_val) {
    	// use long long (instead of int) to store INFINITY, since the max valid value is 2^31 - 1.
        long long left_max_val = LONG_MIN;
        long long left_min_val = LONG_MIN;
        long long right_max_val = LONG_MAX;
        long long right_min_val = LONG_MAX;
        bool left_is_valid_BST = true;
        bool right_is_valid_BST = true;
	
	// check left subtree
        if (root->left) {
            left_min_val = LONG_MAX;
            left_is_valid_BST = isValidBSTWithValue(root->left, left_min_val, left_max_val); 
        }

        // pruning
        if (!left_is_valid_BST || left_max_val >= root->val) {
            return false;
        }
	
	// check right subtree
        if (root->right) {
            right_max_val = LONG_MIN;
            right_is_valid_BST = isValidBSTWithValue(root->right, right_min_val, right_max_val);
        }

        if (!right_is_valid_BST || right_min_val <= root->val) {
            return false;
        } else {
            min_val = left_min_val == LONG_MIN ? root->val : left_min_val;
            max_val = right_max_val == LONG_MAX ? root->val : right_max_val;
            return true;
        }
    }   
};
