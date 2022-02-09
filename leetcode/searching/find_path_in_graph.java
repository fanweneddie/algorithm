/*
Problem: https://leetcode-cn.com/problems/find-if-path-exists-in-graph/

Solution: BFS

Complexity:
	Time: O(n+e)
	Space: O(n+e), where n is node number and e is edge number
*/

class Solution {
    public boolean validPath(int n, int[][] edges, int source, int destination) {
        int node_num = n;
        int edge_num = edges.length;
        // adjacent list for an undirected graph
        List<List<Integer>> adj_list = new ArrayList<List<Integer>>(node_num);
        for (int i = 0; i < node_num; ++i) {
            adj_list.add(new ArrayList<Integer>());
        }
        for (int[] edge : edges) {
            int head = edge[0];
            int tail = edge[1];
            adj_list.get(head).add(tail);
            adj_list.get(tail).add(head);
        }

        // only stores gray nodes during BFS
        Queue<Integer> queue = new LinkedList<Integer>();
        // 0 is white (unvisited), 1 is gray (visited)
        boolean[] visited = new boolean[node_num];
        boolean found = false;

        // init
        visited[source] = false;
        queue.offer(source);
        // do BFS to search the dest
        while (queue.peek() != null) {
            int cur = queue.poll();
            for (int next : adj_list.get(cur)) {
                if (visited[next] == false) {
                    visited[next] = true;
                    queue.offer(next);
                }
            }
            if (cur == destination) {
                found = true;
                break;
            }
        }
        return found;
    }
}
