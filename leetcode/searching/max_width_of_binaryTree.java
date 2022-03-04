/*
Problem: https://leetcode-cn.com/problems/maximum-width-of-binary-tree/

Solution: Use an integer to show the position of each node.
	Also, use a map to store the position of the first node in this depth.
	Due to the exponential feature of binary tree, if a node's position is p,
	then its left child's position is 2*p and its right child's position is 2*p + 1.
	So the width between left node L and right node R is R - L + 1.

Complexity:
	Time: O(n)
	Space: O(n), where n is the size of the binary tree

*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    // storing start position of each depth
    public HashMap<Integer, Integer> start_pos;
    public int max_width = 0;

    public int widthOfBinaryTree(TreeNode root) {
        start_pos = new HashMap<Integer, Integer>();
        dfs(root, 0, 0);
        return max_width;
    }

    public void dfs(TreeNode root, int pos, int depth) {
        if (root == null) {
            return;
        }
        // record the starting position of this depth
        if (!start_pos.containsKey(depth)) {
            start_pos.put(depth, pos);
        }
        // update max_width
        int cur_width = pos - start_pos.get(depth) + 1;
        max_width = Math.max(max_width, cur_width);
        // recursive searching
        dfs(root.left, pos*2, depth + 1);
        dfs(root.right, pos*2 + 1, depth + 1);
    }
}
