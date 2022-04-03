/*
Problem: https://leetcode-cn.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
Solution: dfs from node 0 to other nodes in an undirected graph.
when dfs goes from node i to node j: if i->j, then cnt++

Complexity:
	Time: O(n)
	Space: O(n), where n is the number of nodes.
*/

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        // number of edges that change
        int change_cnt = 0;
        // solved[i] shows whether all edges starting from i has been changed properly
        vector<bool> solved;
        // init solved
        solved.resize(n);
        for (int i = 0; i < n;++i) {
            solved[i] = false;
        }
        // adjacent list in this graph
        // start_adj_list[i] stores the nodes that i points to
        // end_adj_list[i] stores the nodes that point to i
        vector<vector<int>> start_adj_list;
        vector<vector<int>> end_adj_list;
        // init adjacent list
        start_adj_list.resize(n);
        end_adj_list.resize(n);
        for (vector<int> connection : connections) {
            int start = connection[0];
            int end = connection[1];
            start_adj_list[start].push_back(end);
            end_adj_list[end].push_back(start);
        }
        // Search whether to change direction of edges starting from node,
        search(0, change_cnt, solved, start_adj_list, end_adj_list);
        
        return change_cnt;
    }

private:
    // Search whether to change direction of edges starting from node,
    // if so, increment change_cnt.
    // And this search is done recursively and greedily 
    void search(const int node, int& change_cnt,
                vector<bool>& solved,
                const vector<vector<int>>& start_adj_list,
                const vector<vector<int>>& end_adj_list) {
        for (int neighbor : start_adj_list[node]) {
            if (!solved[neighbor]) {
                change_cnt++;
                search(neighbor, change_cnt, solved, start_adj_list, end_adj_list);
            }
        }
        solved[node] = true;
        for (int neighbor : end_adj_list[node]) {
            search(neighbor, change_cnt, solved, start_adj_list, end_adj_list);
        }
    }

};
