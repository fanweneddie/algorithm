/*
Problem: https://leetcode-cn.com/problems/validate-binary-tree-nodes/

Solution: validating whether the graph is connected and acyclic.
1. get the indegree of each node, if there is no node or more than 1 nodes whose indegree is 0, return false.
2. DFS from the unique 0-indegree node. In DFS, if we have detected a (undirected) cycle, return false.
3. For all nodes, if there is a node that is not visited in DFS, then it is not connected with other nodes, so we return false.

Complexity:
	Time: O(n),
	Space: O(n), where n is the number of nodes in the graph.
*/

class Solution {
    public boolean validateBinaryTreeNodes(int n, int[] leftChild, int[] rightChild) {
        // the in-degree of each node
        int[] in_degs = new int[n];
        for (int left_child : leftChild) {
            if (left_child != -1) {
                in_degs[left_child]++;
            }
        }
        for (int right_child : rightChild) {
            if (right_child != -1) {
                in_degs[right_child]++;
            }
        }
        // the node of unique root
        // if there are multiple roots or no root, then unique_root = -1
        int unique_root = -1;
        for (int i = 0; i < n; ++i) {
            if (in_degs[i] == 0) {
                if (unique_root == -1) {
                    unique_root = i;
                } else {
                    unique_root = -1;
                }   
            }
        }

        if (unique_root == -1) {
            return false;
        }

        // DFS from unique root
        boolean[] visited = new boolean[n];
        boolean has_cycle = DFS(unique_root, visited, leftChild, rightChild);
        // check whether there are nodes that are not connected, if so, return false.
        for (boolean visit : visited) {
            if (!visit) {
                has_cycle = false;
            }
        }
        return has_cycle;
    }

    // Do DFS on current node.
    // If we have visited this node, we return false.
    // Else, we recursively visit its children nodes.
    private boolean DFS(int current, boolean[] visited,
                        int[] leftChild, int[] rightChild) {
        if (visited[current]) {
            return false;
        }
        visited[current] = true;
        // the flag of visiting children node
        boolean flag_child = true;
        if (leftChild[current] != -1) {
            flag_child &= DFS(leftChild[current], visited, leftChild, rightChild);
        }
        if (rightChild[current] != -1 && flag_child) {
            flag_child &= DFS(rightChild[current], visited, leftChild, rightChild);
        }
        return flag_child;
    }
}
