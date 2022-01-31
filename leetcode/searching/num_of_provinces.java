/*
Problem: https://leetcode-cn.com/problems/number-of-provinces/

Solution: DFS to find the number of connective components in a undirected graph

Complexity:
	Time: O(n^2)
	Space: O(n), where n is the number of nodes.
*/

class Solution {
    public int findCircleNum(int[][] isConnected) {
        int node_num = isConnected.length;
        // flags[i] shows whether node i has been searched
        int[] flags = new int[node_num];

        int num = 0;
        for (int i = 0; i < node_num; ++i) {
            if (flags[i] == 0) {
                dfs(i, isConnected, flags);
                num++;
            }
        }
        return num;
    }

    // DFS to search all nodes in a connective component
    private void dfs(int node, int[][] isConnected, int[] flags) {
        flags[node] = 1;
        int node_num = isConnected.length;
        for (int j = 0; j < node_num; ++j) {
            if (isConnected[node][j] == 1) {
                if (flags[j] == 0) {
                    dfs(j, isConnected, flags);
                }
            }
        }
    }
}
