/*
Problem: https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/

Solution: Double pointers
We use a start pointer and an end pointer, and their gap is just n

Complexity:
Time: O(m)
Space: O(1), where m is the size of linked list
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func removeNthFromEnd(head *ListNode, n int) *ListNode {
    // end (fast) pointer
    end := head
    // before the start (slow) pointer
    var pre *ListNode = new(ListNode)
    pre.Next = head
    // whether the head is deleted
    var delete_head bool = false

    // build the gap
    for i := 0; i < n; i++ {
        end = end.Next
    }
    // traverse the linked list
    for ; end != nil; end = end.Next {
        pre = pre.Next
    }
    // special case
    if pre.Next == head {
        delete_head = true
    }
    // delete
    pre.Next = pre.Next.Next
    // return
    if delete_head {
        return pre.Next
    } else {
        return head
    }
}
