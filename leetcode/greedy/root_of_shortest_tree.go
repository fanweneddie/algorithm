/*
Problem: https://leetcode-cn.com/problems/minimum-height-trees/

Solution: topological sorting

Complexity:
	Time: O(en^2)
	Space: O(n+e)
*/

func findMinHeightTrees(n int, edges [][]int) []int {
    adj := make([][]int, n)
    degrees := make([]int, n)

    for _, edge := range edges {
        head := edge[0]
        tail := edge[1]
        adj[head] = append(adj[head], tail)
        adj[tail] = append(adj[tail], head)
        degrees[head]++
        degrees[tail]++
    }

    // temporarily stores the node whose degree = 1
    list := make([]int, 0)

    // clear all nodes whose degree = 1, until there is only one or two nodes left
    for ; n > 2;  {
        for i, _ := range degrees {
            if degrees[i] == 1 {
                degrees[i] = -1
                list = append(list, i)
            }
        }

        for _, node := range list {
            for _, next := range adj[node] {
                degrees[next]--
            }
            n--
        }
        list = list[:0]
    }

    result := make([]int, 0)
    for i, deg := range degrees {
        if deg >= 0 {
            result = append(result, i)
        }
    }
    return result
}
