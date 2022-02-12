/*
Problem: https://leetcode-cn.com/problems/critical-connections-in-a-network/

Solution: Tarjan algorithm

Complexity:
	Time: O(n+e)
	Space: O(n+e)
*/

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        int node_num = n;
        int edge_num = connections.size();
        int index = 0;
        // adjacent list
        vector<vector<int>> adj;
        adj.resize(node_num);
        for (int i = 0; i < edge_num; ++i) {
            int head = connections[i][0];
            int tail = connections[i][1];
            adj[head].push_back(tail);
            adj[tail].push_back(head);
        }
        dfs_index.resize(node_num);
        low_index.resize(node_num);

        for (int i = 0; i < node_num; ++i) {
            if (dfs_index[i] == 0) {
                tarjan(i, -1, adj, index);
            }
        }
        return bridges;
    }

    // tarjan algo to find the bridge
    // we make sure that current node has not been visited
    void tarjan(int cur, int parent, vector<vector<int>>& adj, int& index) {
        // visit current node
        index++;
        dfs_index[cur] = index;
        low_index[cur] = index;
        // visit neighboring nodes
        int degree = adj[cur].size();
        for (int i = 0; i < degree; ++i) {
            int next = adj[cur][i];
            if (next == parent) {
                continue;
            }
            if (dfs_index[next] == 0) {
                tarjan(next, cur, adj, index);
                low_index[cur] = min(low_index[cur], low_index[next]);
                // detect bridge here
                if (low_index[next] > dfs_index[cur]) {
                    bridges.push_back({cur, next});
                }
            } else {
                low_index[cur] = min(low_index[cur], dfs_index[next]);
            }
        }
    }

private:
    // stores the cut edges as a result
    vector<vector<int>> bridges;
    // the index of node in dfs
    vector<int> dfs_index;
    // the lowest index that a node can reach
    vector<int> low_index;
};
