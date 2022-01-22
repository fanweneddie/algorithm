/*
Problem: https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/

Solution: In order traverse

Complexity: 
Time: O(k), where k is from input
Space: O(1)
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
    void inOrderTraverse(TreeNode* root, int& k, int & element) {
        if (root->left) {
            inOrderTraverse(root->left, k, element);
        }

        k--;
        if (k == 0) {
            element = root->val;
            return;
        }

        if (root->right) {
            inOrderTraverse(root->right, k, element);
        }
    } 

    int kthSmallest(TreeNode* root, int k) {
        int element = -1;
        inOrderTraverse(root, k, element);
        return element;
    }   
};
