/*
Problem: https://leetcode-cn.com/problems/middle-of-the-linked-list/

Solution: Double pointers (a slow pointer and a fast pointer)
The step of fast pointer is 2, and the step of slow pointer is 1.
When fast pointer reaches the end, slow pointer reaches the middle.

Complexity:
Time: O(n),
Space: O(1), where n is the size of linked list.
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func middleNode(head *ListNode) *ListNode {
    // we use double pointers
    // the step of fast pointer is 2, 
    // and the step of slow pointer is 1
    slow := head
    fast := head

    // when fast pointer reaches the end,
    // slow pointer reaches the middle
    for ; fast != nil && fast.Next != nil; {
        fast = fast.Next.Next
        slow = slow.Next
    }

    return slow    
}
