#include <iostream>
using namespace std;

void slide(int *arr,int n, int k)
{
    int * queue = new int[n];
    int left =0,right = 0;
    queue[0] = 0;

    for(int i = 0; i < n;++i)
    {
        if(i - k >= queue[left])
            left++;
        while(left <= right 
            && arr[ queue[right] ] <= arr[i] )
            right--;
        right++;
        queue[right] = i;
        if(i >= k-1)
            cout << arr[ queue[left] ] << " " ;
    }
    delete [] queue;
}

int main()
{
    int n,k;
    cin >> n >> k;
    int* arr = new int[n];
    for(int i = 0;i < n;++i)
        cin >> arr[i];
    slide(arr,n,k);
    delete [] arr;
}
