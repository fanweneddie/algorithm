/*
Problem: https://leetcode-cn.com/problems/jump-game-ii/

Solution: Greedy

Complexity:
	Time: O(n),
	Space: O(1), where n is the size of input array
*/

func jump(nums []int) int {
    size := len(nums)
    // special case
    if size == 1 {
        return 0
    }
    // the furthest reachable location in the array
    furthest := 0
    // number of necessary jumps
    jumps := 0
    // the limit location in each step
    limit := 0

    // greedy: get the potentially furthest position on each jump
    for i := 0; i < size && limit < size - 1; i++ {
        if i + nums[i] > furthest {
            furthest = i + nums[i]
        }
        if i == limit {
            limit = furthest
            jumps++
        }
    }

    return jumps
}
