#include<iostream>
using namespace std;
/*
inversion pair: 
in array A, if i < j but A[i] > A[j],
then there is an inversion pair

e.g. A = {3,1,4,2} has 3 inversion pairs
    and they are (3,1),(3,2),(4,2)

solution:
revise merge_sort a little bit
to get the number of inversion pairs
in O(nlgn)
*/

// almost the biggest int number
// for sentinel
const int INFINITY = 2000000000;

// function declaration
void Merge_sort_inversion(int *arr,int start,int end,long& inversion_num);
void Merge_inversion(int* arr,int start,int mid,
            int end,long& inversion_num);


// use merge-sort to make the array ascending
// T(n) = O(nlogn)
// note that Arr[end] is included to be sorted
void Merge_sort_inversion(int *arr,int start,int end,long& inversion_num)
{
    if( start < end)
    {
        int mid = (start + end)/2;
        // divide
        Merge_sort_inversion(arr,start, mid,inversion_num);
        Merge_sort_inversion(arr,mid + 1, end,inversion_num);
        // merge
        Merge_inversion(arr,start,mid,end,inversion_num);
    }
}

// merge the sorted array of A[start,mid] 
// and A[mid+1,end] to A[start,end]
// NOTE: INCREMENT INVERSION_NUM WHEN MERGING
void Merge_inversion(int* arr,int start,int mid,
            int end,long& inversion_num)
{
    int i,j;
    // size of Left and Right
    int left_size = mid - start + 1;
    int right_size = end - mid;
    // initialize array Left and Right
    int *Left = new int[left_size + 1];
    int *Right = new int[right_size + 1];
    for(i = 0;i < left_size;++i)
        Left[i] = arr[start + i];
    for(j = 0;j < right_size;++j)
        Right[j] = arr[mid + 1 + j];
    // a sentinel to show that 
    // the Left or Right has nothing remaining
    Left[left_size] = INFINITY;
    Right[right_size] = INFINITY;
    // merge the data
    i = 0;
    j = 0;
    for(int k = start; k <= end;++k)
    {
        // Left[i,...,mid] > Right[j]
        // so there are (mid - start - i + 1) 
        // pairs of inversion 
        if( Left[i] > Right[j] )
        {
            arr[k] = Right[j];
            j++;
            if(Left[i] != INFINITY)
                inversion_num += mid - start - i + 1;
        }
        // Left[i] <= Left[j]
        else
        {
            arr[k] = Left[i];
            i++;
        }        
    }//for
    delete [] Left;
    delete [] Right;
}

int main()
{
    int size;
    cin >> size;
    int* arr = new int[size];
    for(int i = 0; i < size;++i)
        cin >> arr[i];
    long inversion_num = 0;
    Merge_sort_inversion(arr,0,size-1,inversion_num);
    inversion_num = inversion_num % 10000019;
    cout << inversion_num << endl;
    delete [] arr;
    return 0;
}
