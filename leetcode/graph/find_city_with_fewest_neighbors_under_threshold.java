/*
Problem: https://leetcode-cn.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

Solution: Floyd-Warshall

Complexity:
	Time: O(n^3)
	Space: O(n^2), where n is the number of nodes.
*/

// a pair that represents a city
class City {
    public int ID;
    // number of reachable cities whose distance is within threshold
    public int reachable_num;
    public City(int ID, int reachable_num) {
        this.ID = ID;
        this.reachable_num = reachable_num;
    }
}

class Solution {
    private final int MY_INFINITY = 9999999;
    public int findTheCity(int n, int[][] edges, int distanceThreshold) {
        // init distance matrix as an adjacent matrix
        int[][] dist_matrix = new int[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist_matrix[i][j] = MY_INFINITY;
            }
        }
        for (int[] edge : edges) {
            int head = edge[0];
            int tail = edge[1];
            int weight = edge[2];
            dist_matrix[head][tail] = weight;
            dist_matrix[tail][head] = weight;
        }
        // floyd-warshall
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist_matrix[i][j] > dist_matrix[i][k] + dist_matrix[j][k]) {
                        dist_matrix[i][j] = dist_matrix[i][k] + dist_matrix[j][k];
                    }
                }
            }
        }
        // count the number of reachable cities of each city
        List<City> list = new ArrayList<City>(n);
        for (int i = 0; i < n; ++i) {
            int reachable_num = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist_matrix[i][j] <= distanceThreshold) {
                    reachable_num++;
                }
            }
            list.add(new City(i, reachable_num));
        }
        // find min
        // since we search from city 0 to city 1,
        // we can only compare reachable_num.
        City min_city = new City(0, MY_INFINITY);
        for (City city : list) {
            if (city.reachable_num <= min_city.reachable_num) {
                min_city = city;
            }
        }
        return min_city.ID;
    }
}
