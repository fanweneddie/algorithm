/*
Problem: https://leetcode-cn.com/problems/network-delay-time/

Solution: dijkstra (with priority queue)

Complexity:
	Time: O(n + elge)
	Space: O(n + e), where n is node number and e is edge number
*/

class Edge {
    public int tail;
    public int cost;
    public Edge(int tail, int cost) {
        this.tail = tail;
        this.cost = cost;
    }
}

class Node {
    public int node;
    public int dist;
    public Node(int node, int dist) {
        this.node = node;
        this.dist = dist;
    }
}

class NodeComparator implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
        if (n1.dist < n2.dist) {
            return -1;
        } else if (n1.dist > n2.dist) {
            return 1;
        } else {
            return 0;
        }
    }
}

class Solution {
    private final int INF = 99999;
    public int networkDelayTime(int[][] times, int n, int k) {
        int node_num = n;
        int edge_num = times.length;
        // adjacent list for an undirected graph
        List<List<Edge>> adj_list = new ArrayList<List<Edge>>(node_num + 1);
        // a list of nodes with their distance
        List<Node> node_list = new ArrayList<Node>(node_num + 1);
        // priority queue for dijkstra
        Queue<Node> pq = new PriorityQueue<Node>(node_num, new NodeComparator());
        int max_dist = -1;

        // initialize adj_list
        for (int i = 0; i <= node_num; ++i) {
            adj_list.add(new ArrayList<Edge>());
        }
        for (int[] edge : times) {
            int head = edge[0];
            int tail = edge[1];
            int cost = edge[2];
            Edge new_edge = new Edge(tail, cost);
            adj_list.get(head).add(new_edge);
        }
        // initialize node_list
        for (int i = 0; i <= node_num; ++i) {
            Node new_node = new Node(i, INF);
            node_list.add(new_node);
        }

        // dijkstra
        node_list.get(k).dist = 0;
        for (int i = 1; i <= node_num; ++i) {
            pq.offer(node_list.get(i));
        }

        while (pq.size() > 0) {
            Node cur = pq.poll();
            int cur_node = cur.node;
            int cur_dist = cur.dist;
            // decrease the distance of the neighbring nodes
            for (Edge edge : adj_list.get(cur_node)) {
                int next_node = edge.tail;
                Node next = node_list.get(next_node);
                int cost = edge.cost;
                int next_dist = next.dist;
                if (cur_dist + cost < next_dist) {
                    pq.remove(next);
                    next.dist = cur_dist + cost;
                    pq.offer(next);
                }
            }
            max_dist = cur_dist;
        }

        if (max_dist == INF) {
            max_dist = -1;
        }
        return max_dist;
    }
}
