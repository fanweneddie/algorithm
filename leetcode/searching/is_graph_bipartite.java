/*
Problem: https://leetcode-cn.com/problems/is-graph-bipartite/

Solution: using union set
For each node, union all of its neighboring nodes.
If one node connects to its neighboring node, then the graph is not a bipartite

Complexity:
	Time: O(elgn)
	Space: O(n), where e is edge number and n is node number.
*/

class Solution {
    public boolean isBipartite(int[][] graph) {
        int node_num = graph.length;
        UnionSet us = new UnionSet(node_num);
        for (int i = 0; i < node_num; ++i) {
            int neighbor_num = graph[i].length;
            for (int j = 0; j < neighbor_num; ++j) {
                if (us.isConnective(i, graph[i][j])) {
                    return false;
                } else {
                    us.union(graph[i][0], graph[i][j]);
                }
            }
        }
        return true;
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
