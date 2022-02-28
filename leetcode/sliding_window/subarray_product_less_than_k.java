/*
Problem: https://leetcode-cn.com/problems/subarray-product-less-than-k/

Solution: sliding window with 2 pointers.
For a window, as its left pointer moves right, its product will decrease;
as its right pointer moves right, its product will increase.
Then, We can iterate over the right pointer, and get the count of the products 
of the right pointers on each position.

Complexity:
	Time: O(n)
	Space: O(1), where n is the size of input array
*/

class Solution {
    public int numSubarrayProductLessThanK(int[] nums, int k) {
        int size = nums.length;
        // sliding window
        int left = 0;
        int right = 0;
        int product = 1;
        int count = 0;

        for (right = 0; right < size; ++right) {
            product *= nums[right];
            while (product >= k && left <= right) {
                product /= nums[left];
                left++;
            }
            count += right - left + 1;
        }
        
        return count;
    }
}
