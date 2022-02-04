/*
Problem: https://leetcode-cn.com/problems/recover-binary-search-tree/

Solution: using flags during in-order traverse to find two nodes, and then swap their values.

Complexity:
	Time: O(n)
	Space: O(1), where n is the size of BSTree.
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
    // the first and second node of the wrong pair
    TreeNode* first = nullptr;
    TreeNode* after_first = nullptr;
    TreeNode* second = nullptr;
    // the last node during in-order traverse
    TreeNode* last = nullptr;
    void recoverTree(TreeNode* root) {
        inOrderTraverse(root);
        if (!second) {
            second = after_first;
        }
        // swap first and second
        swapNode(first, second);
    }

    // we make sure that root is not null
    void inOrderTraverse(TreeNode* root) {
        // we have found the wrong pair
        if (first && second) {
            return;
        }

        if (root->left) {
            inOrderTraverse(root->left);
        }

        // record the nodes
        if (first && !second && root->val < last->val) {
            second = root;
        }
        if (last && !first && root->val < last->val) {
            first = last;
            after_first = root;
        }
        last = root;
        
        if (root->right) {
            inOrderTraverse(root->right);
        }
    }

    // swap node1 and node2 by swapping their value
    // we make sure that node1 and node2 are not null
    void swapNode(TreeNode* node1, TreeNode* node2) {
        int temp = node1->val;
        node1->val = node2->val;
        node2->val = temp;
    }
};
