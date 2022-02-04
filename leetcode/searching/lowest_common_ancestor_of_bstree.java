/*
Problem: https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/

Solution: DFS

Complexity: 
	Time: O(n)
	Space: O(n), where n is the size of the input BSTree.
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q) {
            return root;
        }
        
        TreeNode left_son = lowestCommonAncestor(root.left, p, q);
        TreeNode right_son = lowestCommonAncestor(root.right, p, q);
	
	// we find one in left_son, and another in right_son
        if (left_son != null && right_son != null) {
            return root;
        } else if (left_son != null) {
            return left_son;
        } else {
            return right_son;
        }
    }
}
