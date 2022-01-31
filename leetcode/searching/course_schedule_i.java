/*
Problem: https://leetcode-cn.com/problems/course-schedule/

Solution: DFS to check whether the graph is a DAG.

Complexity:
	Time: O(n+e)
	Space: O(n+e), where n is the number of nodes and e is the number of edges.
*/

class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        int node_num = numCourses;
        int edge_num = prerequisites.length;
        // flag[i] marks the time of dfs where node i is visited
        int[] flags = new int[node_num];
        // adjacent list
        List<List<Integer>> adj = new ArrayList<>(node_num);
        for (int i = 0; i < node_num; ++i) {
            adj.add(new ArrayList<>());
        }
        for (int[] edge : prerequisites) {
            int start = edge[0];
            int end = edge[1];
            adj.get(start).add(end);   
        }

        // whether the course schedule is valid
        boolean valid = true;
        for (int node = 0; node < node_num; ++node) {
            valid &= dfs(node, adj, flags);
            if (!valid) {
                break;
            }
        }
        return valid;
    }

    // do dfs that starts on _start_
    private boolean dfs(int start, List<List<Integer>> adj, int[] flags) {
        // this node has been visited by the former iteration
        if (flags[start] == -1) {
            return true;
        } 
        // a circle is detected
        else if (flags[start] == 1) {
            return false;
        }
        // start searching
        else {
            flags[start] = 1;
            boolean no_circle = true;
            for (int next : adj.get(start)) {
                no_circle &= dfs(next, adj, flags);
                if (!no_circle) {
                    break;
                } 
            }
            flags[start] = -1;
            return no_circle;
        }
    }
}
