/*
Problem: https://leetcode-cn.com/problems/longest-univalue-path/

Solution: DFS

Complexity:
	Time: O(n)
	Space: O(n), where n is the size of binary tree
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
    // the global max length of a path
    int max_len = 0;
    int longestUnivaluePath(TreeNode* root) {
        dfs(root);
        return max_len;
    }

    // dfs gets the length of longest path (containning root) in root's subtree
    int dfs(TreeNode* root) {
        if (!root) {
            return 0;
        }
        // max length on current node, left child and right child
        int max_cur_len = 0;
        int max_left_len = 0;
        int max_right_len = 0;
        
        // recursion
        max_left_len = dfs(root->left);
        max_right_len = dfs(root->right);

        // whether it is worthwhile to explore left child and right child
        bool explore_left = root->left && root->left->val == root->val;
        bool explore_right = root->right && root->right->val == root->val;

        // backtrack
        if (explore_left) {
            max_left_len++;
        } else {
            max_left_len = 0;
        }
        if (explore_right) {
            max_right_len++;
        } else {
            max_right_len = 0;
        }
        
        // update local and global max length
        max_cur_len = max(max_left_len, max_right_len);
        max_len = max(max_len, max_left_len + max_right_len);
        return max_cur_len;
    }
};
