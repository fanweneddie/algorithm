/*
Problem: https://leetcode-cn.com/problems/diameter-of-binary-tree/

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
    int diameterOfBinaryTree(TreeNode* root) {
        int max_d = 0;
        dfs(root, max_d);
        return max_d;
    }

    // Return the height of the current node and update the max diameter
    // The node at the bottom has height 1
    int dfs(TreeNode* root, int& max_d) {
        if (!root) {
            return 0;
        }
        // the height of left and right child
        int left_h = dfs(root->left, max_d);
        int right_h = dfs(root->right, max_d);
        
        max_d = max(max_d, left_h + right_h);
        return max(left_h, right_h) + 1;
    }
};
