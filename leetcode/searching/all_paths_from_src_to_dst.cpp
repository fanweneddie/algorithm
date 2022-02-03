/*
Problem: https://leetcode-cn.com/problems/all-paths-from-source-to-target/

Solution: recursive DFS
I tried to use a stack, but I find that it is hard to implement path reconstruction.

Complexity:
	Time: O(n*2^n)
	Space: O(n)
*/

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        // stores the temporary path
        vector<int> path;
        // stores all paths in result
        vector<vector<int>> paths;

        path.push_back(0);
        dfs(0, graph, path, paths);
        return paths;
    }

    // DFS from the current node
    // we make sure that current node is in path
    void dfs(int cur, vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& paths) {
        if (cur == graph.size() - 1) {
            paths.push_back(path);
        } else {
            int next_num = graph[cur].size();
            for (int j = 0; j < next_num; ++j) {
                int next = graph[cur][j];
                path.push_back(next);
                dfs(next, graph, path, paths);
                path.pop_back();
            }
        }
    }
};
