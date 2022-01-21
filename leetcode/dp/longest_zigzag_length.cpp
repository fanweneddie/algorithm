/*
Problem: https://leetcode-cn.com/problems/longest-zigzag-path-in-a-binary-tree/
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
    // stores the length of longest left zigzag that starts from a node
    map<TreeNode*, int> LZZ_map;
    // stores the length of longest right zigzag that starts from a node
    map<TreeNode*, int> RZZ_map;

    int longestZigZag(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int cur_lzz = max(longestLeftZigZag(root), longestRightZigZag(root));
        return max(cur_lzz, max(longestZigZag(root->left), longestZigZag(root->right)));
    }

    int longestLeftZigZag(TreeNode* root) {
        if (!root) {
            return -1;
        } else {
            if (LZZ_map.find(root) == LZZ_map.end()) {
                LZZ_map[root] = longestRightZigZag(root->left) + 1;
            }
            return LZZ_map[root];
        }
    }

    int longestRightZigZag(TreeNode* root) {
        if (!root) {
            return -1;
        } else {
            if (RZZ_map.find(root) == RZZ_map.end()) {
                RZZ_map[root] = longestLeftZigZag(root->right) + 1;
            }
            return RZZ_map[root];
        }
    }

};
