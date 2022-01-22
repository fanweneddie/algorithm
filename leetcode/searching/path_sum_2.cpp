/*
Problem: https://leetcode-cn.com/problems/path-sum-ii/

Solution: DFS

Complexity:
Time: O(n)
Space: O(n), where n is the number of nodes in the binary tree.
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
    vector<int> cur_path;
    int cur_sum = 0;
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> results;
        vector<vector<int>> left_results;
        vector<vector<int>> right_results;

        // special case
        if (!root) {
            return results;
        }

        // visit this node
        cur_sum += root->val;
        cur_path.push_back(root->val);

        // if the current node is a leave node and current sum = targetSum
        // add current path to results
        if (cur_sum == targetSum && !root->left && !root->right) {
            vector<int> result;
            result.assign(cur_path.begin(), cur_path.end());
            results.push_back(result);
        }

        // search left child
        if (root->left) {
            left_results = pathSum(root->left, targetSum);
            results.insert(results.end(), left_results.begin(), left_results.end());
        }

        // search right child
        if (root->right) {
            right_results = pathSum(root->right, targetSum);
            results.insert(results.end(), right_results.begin(), right_results.end());
        }

        // backtrack
        cur_sum -= root->val;
        cur_path.pop_back();

        return results;
    }
};
