/*
Problem: https://leetcode-cn.com/problems/maximum-binary-tree/

Solution: Divide and Conquer as it's definition.
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
    // we ensure that nums is not empty
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        auto itr = max_element(nums.begin(), nums.end());
        TreeNode* root = new TreeNode(*itr);

        // left child
        if (itr == nums.begin()) {
            root->left = nullptr;
        } else {
            vector<int> left_nums = {nums.begin(), itr};
            root->left = constructMaximumBinaryTree(left_nums); 
        }

        // right child
        if (itr == nums.end() - 1) {
            root->right = nullptr;
        } else {
            vector<int> right_nums = {itr + 1, nums.end()};
            root->right = constructMaximumBinaryTree(right_nums); 
        }

        return root;
    }
};
