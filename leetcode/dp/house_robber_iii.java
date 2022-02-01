/*
Problem: https://leetcode-cn.com/problems/house-robber-iii/

Solution1: top-down dynamic programming

Complexity:
	Time: O(n)
	Space: O(n), where n is the size of input tree
	
Solution2: recursion
for each node, we set result[0] as the max amount from the bottom if we doesn't rob it,
and we set result[1] as the max amount from the bottom if we rob it.
Then we have
result[0] = max{node.left.result[0], node.left.result[1]} + max{node.right.result[0], node.right.result[1]}
result[1] = node.left.result[0] + node.right.result[0] + node.val

Complexity:
	Time: O(n)
	Space: O(n) only for recursive stack
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
class Solution1 {
    // money[root] stores the bottom-up money at node root
    private HashMap<TreeNode, Integer> money = new HashMap<TreeNode, Integer>();

    public int rob(TreeNode root) {
        if (root == null) {
           return 0;
        }

        if (!money.containsKey(root)) {
            // the current value to be returned
            int cur;
            // the sum of money without choosing the current node
            int wo_cur = rob(root.left) + rob(root.right);
            // the sum of money with choosing the current node
            int with_cur = root.val;
            if (root.left != null) {
                with_cur += rob(root.left.left) + rob(root.left.right);
            }
            if (root.right != null) {
                with_cur += rob(root.right.left) + rob(root.right.right);
            }
            cur = Math.max(wo_cur, with_cur); 
            money.put(root, cur);
        }
        return money.get(root);
    }
}

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
class Solution2 {
    public int rob(TreeNode root) {
        int [] result = intervalRob(root);
        return Math.max(result[0], result[1]);
    }

    private int[] intervalRob(TreeNode root) {
        // result[0] means the max money if I don't rob root
        // result[0] means the max money if I rob root
        int [] result = new int[2];
        if (root == null) {
            return result;
        }

        int[] left = intervalRob(root.left);
        int[] right = intervalRob(root.right);

        result[0] = Math.max(left[0], left[1]) + Math.max(right[0], right[1]);
        result[1] = left[0] + right[0] + root.val;
        return result;
    }
}
