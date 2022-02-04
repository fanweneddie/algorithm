/*
Problem: https://leetcode-cn.com/problems/find-bottom-left-tree-value/

Solution: level-order traverse using a queue

Solution:
	Time: O(n)
	Space: O(n), where n is the size of the binary tree
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
    int findBottomLeftValue(TreeNode* root) {
        // the result value
        int result;
        // for level-order traverse
        queue<TreeNode*> Q;
        Q.push(root);
        
        while(!Q.empty()) {
            int num = Q.size();
            result = Q.front()->val;
            for (int i = 0; i < num; ++i) {
                TreeNode* node = Q.front();
                Q.pop();
                if (node->left) {
                    Q.push(node->left);
                }
                if (node->right) {
                    Q.push(node->right);
                }
            }
        }

        return result;
    }
};
