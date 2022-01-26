/*
Problem: https://leetcode-cn.com/problems/next-permutation/

Solution:
1. find the greatest index k s.t. nums[k] < nums[k+1]
2. find the greatest index l s.t. nums[l] > nums[k]
3. swap nums[k] and nums[l]
4. reverse nums[k+1: -1]

Complexity:
Time: O(n)
Space: O(1), where n is the size of nums
*/

class Solution {
    private void swapInArray(int l, int k, int[] nums) {
        int temp = nums[l];
        nums[l] = nums[k];
        nums[k] = temp;
    }

    private void reverseArray(int start, int end, int[] nums) {
        int tot = start + end;
        int mid = tot / 2;
        for (int i = start; i <= mid; ++i) {
            swapInArray(i, tot - i, nums);
        }
    }

    public void nextPermutation(int[] nums) {
        int size = nums.length;
        int k = size - 2;
        int l = size - 1;
        
        // 1. find the greatest index k s.t. nums[k] < nums[k+1]
        for (; k >= 0; --k) {
            if (nums[k] < nums[k+1]) {
                break;
            }
        }
        // nums is ascending
        if (k == -1) {
            reverseArray(0, size - 1, nums);
            return;
        }

        // 2. find the greatest index l s.t. nums[l] > nums[k]
        for (; l > k; --l) {
            if (nums[l] > nums[k]) {
                break;
            }
        }

        // 3. swap nums[k] and nums[l]
        swapInArray(l, k, nums);

        // 4. reverse nums[k+1: -1]
        reverseArray(k + 1, size - 1, nums);
    }
}
