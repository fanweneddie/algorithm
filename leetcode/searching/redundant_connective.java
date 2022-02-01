/*
Problem: https://leetcode-cn.com/problems/redundant-connection/

Solution: Using union set

Complexity:
	Time: O(nlgn) in worst case
	Space: O(n), where n is the number of nodes.
*/

class Solution {
    public int[] findRedundantConnection(int[][] edges) {
        int edge_num = edges.length;
        UnionSet us = new UnionSet(edge_num + 1);
        int[] result = new int [2];

        for (int i = 0; i < edge_num; ++i) {
            int head = edges[i][0];
            int tail = edges[i][1];
            if (!us.isConnective(head, tail)) {
                us.union(head, tail);
            } else {
                result[0] = head;
                result[1] = tail;
            }
        }
        return result;
    }
}

class UnionSet {
    // The representative node of each node
    private int[] roots;
    
    public UnionSet(int size) {
        roots = new int [size];
        for (int i = 0; i < size; ++i) {
            roots[i] = i;
        }
    }

    // Find the final root of node i
    private int findRoot(int i) {
        if (roots[i] == i) {
            return i;
        } else {
            return findRoot(roots[i]);
        }
    }

    // Union node i and node j
    // Let j's representative node link to i's
    public void union(int i, int j) {
        roots[findRoot(j)] = findRoot(i);
    }

    // Check whether node i and node j are in the same connective component
    public boolean isConnective(int i, int j) {
        return findRoot(i) == findRoot(j);
    }
}
