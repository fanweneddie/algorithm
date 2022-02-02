/*
Problem: https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/

Solution: top-down dynamic programming
We set dp[n][i] as the max cost to node n within i steps.
Then we have dp[n][i] = max_{m \in pred(n) or n}(dp[m][i-1] + cost[m][n])
And finally we return dp[dst][k+1]

Complexity:
	Time: O(ek)
	Space: O(nk)
*/

// An directed weighted edge in graph
type Edge struct {
    head int
    cost int
}

func findCheapestPrice(n int, flights [][]int, src int, dst int, k int) int {
    // dp[n][i] stores the max cost to node n within i steps
    dp := make([][]int, n)
    for i := 0; i < n; i++ {
        dp[i] = make([]int, k + 2)
    }

    // reversed adjacent list
    re_adj :=  make([][]Edge, n)
    for _, edge := range flights {
        head := edge[0]
        tail := edge[1]
        cost := edge[2]
        re_adj[tail] = append(re_adj[tail], Edge{head, cost})
    }
    
    result := findCheapestPriceInternal(src, dst, k + 1, re_adj, dp)
    if result == math.MaxInt32 {
        return -1
    } else {
        return result
    }
}

// Solve dp[n][i]
func findCheapestPriceInternal(src int, n int, i int, re_adj [][]Edge, dp [][]int) int {
    if n == src {
        return 0
    }

    if i == 0 {
        return math.MaxInt32
    }

    if dp[n][i] != 0 {
        return dp[n][i]
    }
    cur := findCheapestPriceInternal(src, n, i - 1, re_adj, dp)
    for _, edge := range re_adj[n] {
        head := edge.head
        cost := edge.cost
        cur = get_min(cur, findCheapestPriceInternal(src, head, i - 1, re_adj, dp) + cost)
    }
    dp[n][i] = cur
    return dp[n][i]
}

func get_min(a int, b int) int {
    if a <= b {
        return a
    } else {
        return b
    }
}
