#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
get the max gap between two consecutive elements in an array
INPUT: an array with random order
OUTPUT: the max gap between 
    two consecutive elements in that array(after sorting)

e.g.
INPUT: 6 4 1 9
OUTPUT: 3

method: 
1. implements some bucket and figure out the capacity of each bucket
2. figure out the max and min value in each bucket
3. then figure out the gap between two consecutive buckets.
4. The max gap is the answer
Time complexity: T(n) = O(n)
*/

// almost the biggest integer, acts as infinity
const int INF = 2000000000;

class Bucket
{
    public:
    int max = -INF;
    int min = INF;
    bool is_empty = true;
};

// function declaration
int get_max_gap(int* arr,int size);

// get the maximal gap between two consecutive
// element in arr[size]
int get_max_gap(int* arr,int size)
{
    // get max value and min value in arr
    int max_value = arr[0],min_value = arr[0];
    for(int i = 1 ; i < size;++i)
    {
        if(arr[i] > max_value)
        {
            max_value = arr[i];
        }
        else if(arr[i] < min_value)
        {
            min_value = arr[i];   
        }
    }

    // the gap between two consecutive buckets
    double gap = ( (double)(max_value - min_value) ) / (size + 1);
    if(gap == 0)
        return 0;
    // (size + 1) buckets
    Bucket* bptr = new Bucket[size+1];
    // the index of each element's bucket
    int bucket_index;
    for(int i = 0;i < size;++i)
    {
        // get arr[i]'s bucket index
        // consider max_value specially
        if(arr[i] == max_value)
            bucket_index = size;
        else
            bucket_index = floor( (arr[i] - min_value)/gap );
        
        // after pushing that element, 
        // that bucket will not be empty
        bptr[bucket_index].is_empty = false;
        // update the max or min value in this bucket
        if( arr[i] < bptr[bucket_index].min )
            bptr[bucket_index].min = arr[i];
        if( arr[i] > bptr[bucket_index].max )
            bptr[bucket_index].max = arr[i];
    }

    int max_gap = 0;
    int last_max,this_min,next_min;
    // search the max_gap between two consecutive buckets
    for(int i = 1; i < size + 1;++i)
    {
        // NOTE that last bucket is always not empty
        // bucket[i] is not empty
        if( !bptr[i].is_empty )
        {
            // gap = this_min - last_max
            last_max = bptr[i-1].max;
            this_min = bptr[i].min;
            if(this_min - last_max > max_gap)
                max_gap = this_min - last_max;
        }
        // bucket[i] is empty
        // then, i becomes the index of next unempty bucket
        else
        {
            last_max = bptr[i-1].max;
            do
            {
                i++;
            } while(bptr[i].is_empty);
            next_min = bptr[i].min;
            if(next_min - last_max > max_gap)
                max_gap = next_min - last_max;
        }
    }
    
    delete [] bptr;
    return max_gap;
}

int main()
{
    // close cin's synchronization with stdin
    // to make it faster
    ios::sync_with_stdio(false);
    // the size of input data
    int size;
    cin >> size;
    int* arr = new int[size];
    for(int i = 0; i < size;++i)
        cin >> arr[i];
    // get the max gap between two consecutive elements
    int max_gap = get_max_gap(arr,size);
    cout << max_gap << endl;
    delete [] arr;
    return 0;
}
