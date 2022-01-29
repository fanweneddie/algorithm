/*
Problem: https://leetcode-cn.com/problems/median-of-two-sorted-arrays/

Solution: Binary search
We set the size of nums1 and nums2 as m and n.
If m + n is odd, then we try to find the (m + n + 1)/2 th smallest element;
If m + n is even, then we try to find the average of the (m + n + 1)/2 th and (m + n + 2)/2 th smallest element.
So we define method findKthMinIn2Arrays().
In this method,
if m = 0 or n = 0, (since nums1 and nums2 are sorted) then we just get the k th element from the other array.
If k = 1, return the min value of nums1[0] and nums2[0]
Else, let mid1 = max{k/2 - 1, m - 1} and mid2 = max{k/2 - 1, n - 1}.
	If nums1[mid1] < nums[mid2], then there is at most k/2 - 1 + k/2 - 1 = k - 2 elements that is smaller than nums1[mid1],
		so nums1[mid1] at most can be (k-1)th smallest element. 
		Therefore, we just need to search the (k - mid1 - 1)th element in nums1[mid+1:-1] and nums2.
	And vice versa

Complexity:
Time: O(lg(m+n))
Space: O(lg(m+n)) for recursive stack. Here, m and n are the size of nums1 and nums2, respectively.
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        int mid1 = (size1 + size2 + 1) / 2;
        int mid2 = (size1 + size2 + 2) / 2;
        float result;
        if (mid1 == mid2) {
            result = findKthMinIn2Arrays(mid1, nums1, 0, nums2, 0);
        } else {
            result = (findKthMinIn2Arrays(mid1, nums1, 0, nums2, 0) + 
                        findKthMinIn2Arrays(mid2, nums1, 0, nums2, 0)) / 2.0;
        }
        return result;
    }
    
    // find the Kth minimum element in 2 arrays
    int findKthMinIn2Arrays(int k, vector<int>& nums1, int start1, 
                                vector<int>& nums2, int start2) {
        int size1 = nums1.size();
        int size2 = nums2.size();

        // special cases
        if (size1 - start1 == 0) {
            return nums2[start2 + k - 1];
        }
        if (size2 - start2 == 0) {
            return nums1[start1 + k - 1];
        }
        if (k == 1) {
            return min(nums1[start1], nums2[start2]);
        }
        
        // binary search
        int mid = k/2 - 1;
        int mid1 = start1 + mid < size1 ? start1 + mid : size1 - 1;
        int mid2 = start2 + mid < size2 ? start2 + mid : size2 - 1;

        if (nums1[mid1] >= nums2[mid2]) {
            int new_k = k - (mid2 - start2 + 1);
            int new_start2 = mid2 + 1;
            return findKthMinIn2Arrays(new_k, nums1, start1, nums2, new_start2);
        } else {
            int new_k = k - (mid1 - start1 + 1);
            int new_start1 = mid1 + 1;
            return findKthMinIn2Arrays(new_k, nums1, new_start1, nums2, start2);
        }
    }
};
