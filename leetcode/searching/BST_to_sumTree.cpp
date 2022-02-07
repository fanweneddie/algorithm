/*
Problem: https://leetcode-cn.com/problems/convert-bst-to-greater-tree/

Solution1: reverse in-order traverse

Complexity1:
	Time: O(n)
	Space: O(n), where n is the size of BST

Solution2: morris traverse

Complexity:
	Time: O(n)
	Space: O(1), where n is the size of BST
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
class Solution1 {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        revInOrderTraverse(root, sum);
        return root;
    }
    void revInOrderTraverse(TreeNode* root, int& sum) {
        if (root == nullptr) {
            return;
        }
        
        revInOrderTraverse(root->right, sum);
        sum += root->val;
        root->val = sum;
        revInOrderTraverse(root->left, sum);
    }
};

class Solution2 {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        TreeNode* node = root;
        // Morris traversal
        while (node) {
            // right child is null, visit current node and go to left child
            if (!node->right) {
                sum += node->val;
                node->val = sum;
                node = node->left;
            } 
            // right child is not null, find the predecessor of reverse in-order traversal
            else {
                TreeNode* succ = getSuccessor(node);
                // add a link and go to right child
                if (!succ->left) {
                    succ->left = node;
                    node = node->right;
                }
                // cancel the link, deal with current node and go to left child
                else {
                    succ->left = nullptr;
                    sum += node->val;
                    node->val = sum;
                    node = node->left;
                }
            }
        }
        return root;
    }

    // Get the leftmost node of root's right subtree,
    // which is the predecessor of reverse in-order traversal 
    TreeNode* getSuccessor(TreeNode* root) {
        TreeNode* cur = root->right;
        while (cur->left && cur->left != root) {
            cur = cur->left;
        }
        return cur;
    }
};

