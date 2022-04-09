/*
Problem: https://leetcode-cn.com/problems/shortest-path-with-alternating-colors/

Solution: BFS

complexity:
	Time: O(n+e)
	Space: O(n), where n and e are number of nodes and edges.
*/

class Solution {
    private final int MY_INFINITY = 999999;
    // the color of edge
    private enum Color {
        RED,
        BLUE
    }
    // a node during search
    private class Node {
        public int ID;
        public int parent_ID;
        public Color from_edge_color;
        public Node(int ID, int parent_ID, Color from_edge_color) {
            this.ID = ID;
            this.parent_ID = parent_ID;
            this.from_edge_color = from_edge_color;
        } 
    }
    public int[] shortestAlternatingPaths(int n, int[][] redEdges, int[][] blueEdges) {
        int red_edge_num = redEdges.length;
        int blue_edge_num = blueEdges.length;
        // adjacent list for red and blue edges
        List<List<Integer>> red_adj_list = new ArrayList<>(n);
        List<List<Integer>> blue_adj_list = new ArrayList<>(n);
        for (int i = 0; i < n; ++i) {
            red_adj_list.add(new ArrayList<>());
            blue_adj_list.add(new ArrayList<>());
        }
        for (int[] red_edge : redEdges) {
            int start = red_edge[0];
            int end = red_edge[1];
            red_adj_list.get(start).add(end);
        }
        for (int[] blue_edge : blueEdges) {
            int start = blue_edge[0];
            int end = blue_edge[1];
            blue_adj_list.get(start).add(end);
        }
        // the shortest distance between node 0 and each node,
        // where that node is from red edge
        int[] from_red_dists = new int[n];
        // the shortest distance between node 0 and each node,
        // where that node is from blue edge
        int[] from_blue_dists = new int[n];

        // BFS
        // init
        for (int i = 1; i < n; ++i) {
            from_red_dists[i] = MY_INFINITY;
            from_blue_dists[i] = MY_INFINITY;
        }
        Queue<Node> queue = new LinkedList<>();
        for (int node : red_adj_list.get(0)) {
            queue.add(new Node(node, 0, Color.RED));
        }
        for (int node : blue_adj_list.get(0)) {
            queue.add(new Node(node, 0, Color.BLUE));
        }
        
        // Iteration on queue
        while (queue.peek() != null) {
            Node cur = queue.poll();
            // current node has been searched
            if (cur.from_edge_color == Color.RED && from_red_dists[cur.ID] == MY_INFINITY) {
                from_red_dists[cur.ID] = from_blue_dists[cur.parent_ID] + 1;
                // explore successors
                for (int succ : blue_adj_list.get(cur.ID)) {
                    queue.add(new Node(succ, cur.ID, Color.BLUE));
                }
            } else if (cur.from_edge_color == Color.BLUE && from_blue_dists[cur.ID] == MY_INFINITY) {
                from_blue_dists[cur.ID] = from_red_dists[cur.parent_ID] + 1;
                // explore successors
                for (int succ : red_adj_list.get(cur.ID)) {
                    queue.add(new Node(succ, cur.ID, Color.RED));
                }
            }
        }

        // shortest distance from node 0 to each node
        int[] dists = new int[n];
        for (int i = 0; i < n; ++i) {
            dists[i] = Math.min(from_red_dists[i], from_blue_dists[i]);
            if (dists[i] == MY_INFINITY) {
                dists[i] = -1;
            }
        }
        return dists;
    }
}
