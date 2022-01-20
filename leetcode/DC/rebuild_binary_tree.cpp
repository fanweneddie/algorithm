/**
 * Problem: https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // num of nodes in Binary Tree
        int size = preorder.size();
        if (size == 0) {
            return NULL;
        }

        // double pointer
        int pre_left = 0;
        int pre_right = size -1;
        int in_left = 0;
        int in_right = size - 1;

        return buildSubTree(pre_left, pre_right, in_left, in_right, preorder, inorder);
    }

    TreeNode* buildSubTree(int pre_left, int pre_right, int in_left, int in_right, 
            vector<int>& preorder, vector<int>& inorder) {
        int size = preorder.size();

        // no node left
        if (pre_left > pre_right || in_left > in_right) {
            return NULL;
        }

        // one node left
        if (pre_left == pre_right) {
            return new TreeNode(preorder[pre_left]);
        }

        // find the place of root in inorder
        int root = preorder[pre_left];
        int root_index;
        for (root_index = in_left; root_index <= in_right; ++root_index) {
            if (inorder[root_index] == root) {
                break;
            }
        }
        int root_offset = root_index - in_left;

        // divide by root and conquer
        TreeNode* root_node = new TreeNode(root);
        root_node->left = buildSubTree(pre_left + 1, pre_left + root_offset, 
                            in_left, root_index - 1, preorder, inorder);
        root_node->right = buildSubTree(pre_left + root_offset + 1, pre_right,
                            root_index + 1, in_right, preorder, inorder);
        return root_node;
    }
};
