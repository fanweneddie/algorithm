/*
Problem: https://leetcode-cn.com/problems/course-schedule-ii/

Solution: topological sort

Complexity:
	Time: O(n + e)
	Space: O(n + e), where n is the number of nodes and e is the number of edges.
*/

class Solution {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        int node_num = numCourses;
        int edge_num = prerequisites.length;
        // in_degree[i] marks the in-degree of node i
        int[] in_degree = new int[node_num];
        // adjacent list
        List<List<Integer>> adj = new ArrayList<>(node_num);
        for (int i = 0; i < node_num; ++i) {
            adj.add(new ArrayList<Integer>());
        }
        for (int[] edge : prerequisites) {
            int start = edge[1];
            int end = edge[0];
            adj.get(start).add(end);
            in_degree[end] += 1; 
        }
        return topo_sort(adj, in_degree);
    }

    // Do topological sort on the graph
    private int[] topo_sort(List<List<Integer>> adj, int[] in_degree) {
        int node_num = adj.size();
        // stores a topological sequence
        Queue<Integer> topo_seq = new LinkedList<Integer>();
        // stores the nodes whose in_degree is 0
        Queue<Integer> zero_in_degree = new LinkedList<Integer>();
        for (int i = 0; i < node_num; ++i) {
            if (in_degree[i] == 0) {
                zero_in_degree.add(i);
            }
        }
        
        // check whether the graph is a DAG
        while (zero_in_degree.peek() != null) {
            int node = zero_in_degree.poll();
            topo_seq.add(node);
            for (int next : adj.get(node)) {
                in_degree[next]--;
                if (in_degree[next] == 0) {
                    zero_in_degree.add(next);
                }
            }
        }

        int[] result;
        if (topo_seq.size() != node_num) {
            result = new int[0];
        } else {
            result = new int[node_num];
            for (int i = 0; i < node_num; ++i) {
                result[i] = topo_seq.poll();
            }
        }
        return result;
    }
}
