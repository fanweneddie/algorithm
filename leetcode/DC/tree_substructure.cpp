/*
Problem: https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) {
            return false;
        } else {
            return IsSameTree(A, B) || 
                isSubStructure(A->left, B) || isSubStructure(A->right, B);
        }
    }

    bool IsSameTree(TreeNode* A, TreeNode* B) {
        if (!B) {
            return true;
        } else if (!A) {
            return false;
        } else if (A->val == B->val) {
            return IsSameTree(A->left, B->left) && IsSameTree(A->right, B->right);
        } else {
            return false;
        }
    }
};
