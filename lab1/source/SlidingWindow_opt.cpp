#include <iostream>
#include <deque>
using namespace std;
// FanWen 2020.10.29
/*
GET THE MAX NUMBER IN A SLIDING WINDOW
INPUT: AN ARRAY AND A WINDOW SIZE
OUTPUT: THE MAX NUMBER IN EACH WINDOW, AS THE WINDOW MOVES RIGHTWARD.
e.g.
INPUT: 6 3(array size = n and window size = k)
6 1 6 4 1 9(array)
OUTPUT:
6 6 6 9
solution: use a monotonic deque to act as a window
for each number, it can only be pushed and popped,
so T(n) = O(n) in this case
*/

// implement a monotonic(descending) deque
// to act as a window.
// so the max value of each window is the front element.
// in order to maintain it,
// - I need to pop out the expired element and the element
// - that can't be the max number.
// @param arr: the input array
// @param n: the input array size
// @param k: the input window size
void slide(int *arr,int n, int k)
{
    // the deque to ack as a window
    // NOTE: dq STORES THE INDEX OF ELEMENTS IN THE WINDOW
    // if I use an array as implementation,
    // it will consume much memory 
    // to avoid segmentation fault. 
    deque<int> dq;
    // Initially, dq's first element is arr[0]'s index(that is 0)
    dq.push_front(0);

    // traverse each element to check
    // whether to push or throw away
    for(int i = 0; i < n;++i)
    {
        // the element in the front is expired,
        // throw it away
        if( i - k >= dq.front() )
            dq.pop_front();
        // the small numbers between two big numbers
        // -can never be max number,
        // so throw them away
        // (note that those small numbers should be 
        // at the back of the deque
        // since we assume that the deque is descending )
        while( !dq.empty()
            && arr[ dq.back() ] <= arr[i] )
            dq.pop_back();
        // the current element still has a chance
        // to be the max in the future,
        // so push it into dq
        dq.push_back(i);

        // print the max number(dq.front)
        // when current number becomes the back of dq
        if(i >= k-1)
            cout << arr[ dq.front() ] << " " ;
    }// for
}

// monotonic deque
// T(n) = O(n)
int main()
{
    int n,k;
    cin >> n >> k;
    int* arr = new int[n];
    for(int i = 0;i < n;++i)
        cin >> arr[i];
    // get the max number in each window
    slide(arr,n,k);
    delete [] arr;
}
