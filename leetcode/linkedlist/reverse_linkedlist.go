/*
Problem: https://leetcode-cn.com/problems/reverse-linked-list/

Solution1: Traversing the linkedlist and reverse each link one by one

Complexity:
Time: O(n)
Space: O(1), where n is the size of linked list

Solution2: Using recursion

Complexity:
Time: O(n)
Space: o(n), where n is the size of linked list
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseList1(head *ListNode) *ListNode {
    // special case
    if head == nil {
        return head
    }

    // for traversing
    last := head
    cur := head.Next
    next := head
    // avoid making a circle
    last.Next = nil

    // reverse one by one
    for ; cur != nil; {
        next = cur.Next
        cur.Next = last
        last = cur
        cur = next
    }

    return last
}

func reverseList2(head *ListNode) *ListNode {
    if (head == nil || head.Next == nil) {
        return head
    }

    last := reverseList(head.Next)
    head.Next.Next = head
    head.Next = nil
    return last
}
