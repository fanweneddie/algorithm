/*
Problem: https://leetcode-cn.com/problems/find-eventual-safe-states/

Solution: queue

Complexity:
	Time: O(n+e)
	Space: O(n+e), where n and e are number of nodes and edges, respectively
*/

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int node_num = graph.size();
        // end_adj_graph[i] stores the nodes that point to i
        vector<vector<int>> end_adj_graph;
        end_adj_graph.resize(node_num);
        // the queue that stores the node whose out degree is 0
        queue<int> Q;
        // the out degree of each node
        vector<int> out_deg;
        out_deg.resize(node_num);
        // stores the result nodes
        vector<int> result;
        for (int i = 0; i < node_num; ++i) {
            vector<int> ends = graph[i];
            for (int end : ends) {
                end_adj_graph[end].push_back(i);
            }
            out_deg[i] = ends.size();
            if (out_deg[i] == 0) {
                Q.push(i);
                result.push_back(i);
            }
        }
	
	// searching by out-degree
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            for(int start : end_adj_graph[node]) {
                out_deg[start]--;
                if (out_deg[start] == 0) {
                    Q.push(start);
                    result.push_back(start);
                }
            }
        }

        sort(result.begin(), result.end());
        return result;
    }
};
