#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


// function declaration
int get_max_gap(int* arr,int size);
int get_min(vector<int>* bucket,int i);
int get_last_max(vector<int>* bucket,int i);
int get_next_min(vector<int>* bucket,int &i);

// get bucket[i]'s min value
// suppose that bucket[i] is not empty
int get_min(vector<int>* bucket,int i)
{
    int min = bucket[i][0];
    int size = bucket[i].size();
    for(int j = 0; j < size;++j)
    {
        if(bucket[i][j] < min)
            min = bucket[i][j];
    }
    return min;
}

// get the max value in bucket[i]'s last bucket
// suppose that last bucket is not empty.
int get_last_max(vector<int>* bucket,int i)
{
    int last_max = bucket[i-1][0];
    int last_size = bucket[i-1].size();
    for(int j = 1; j < last_size;++j)
    {
        if(bucket[i-1][j] > last_max)
            last_max = bucket[i-1][j];
    }
    return last_max;
}

// get the max value in bucket[i]'s 
// next unempty bucket
// then, i is the index of that unempty bucket
int get_next_min(vector<int>* bucket,int &i)
{
    // let i be the next unempty bucket
    // of bucket[original_i]
    do
    {
        i++;
    }
    while(bucket[i].size() == 0);

    int next_min = bucket[i][0];
    int next_size = bucket[i].size();
    for(int j = 1; j < next_size;++j)
    {
        if(bucket[i][j] < next_min)
            next_min = bucket[i][j];
    }
    return next_min;
}

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

    double gap = ( (double)(max_value - min_value) ) / (size + 1);
    if(gap == 0)
        return 0;
    // (size + 1) buckets
    vector<int>* bucket = new vector<int>[size+1];
    int bucket_index;
    for(int i = 0;i < size;++i)
    {
        // get arr[i]'s bucket index
        // consider max_value specially
        if(arr[i] == max_value)
            bucket_index = size;
        else
            bucket_index = floor( (arr[i] - min_value)/gap );
        // push arr[i] in the right bucket
        bucket[bucket_index].push_back(arr[i]);
    }

    int max_gap = 0;
    int last_max,this_min,next_min;
    for(int i = 1; i < size + 1;++i)
    {
        // bucket[i] is not empty
        if(bucket[i].size() != 0)
        {
            last_max = get_last_max(bucket,i);
            this_min = get_min(bucket,i);
            if(this_min - last_max > max_gap)
                max_gap = this_min - last_max;
        }
        // bucket[i] is empty
        // then, i becomes the index of next unempty bucket
        else
        {
            last_max = get_last_max(bucket,i);
            next_min = get_next_min(bucket,i);
            if(next_min - last_max > max_gap)
                max_gap = next_min - last_max;
        }
    }
    
    delete [] bucket;
    return max_gap;
}

int main()
{
    // close cin's synchronization with stdin
    // to make it faster
    ios::sync_with_stdio(false);
    int size;
    cin >> size;
    int* arr = new int[size];
    for(int i = 0; i < size;++i)
        cin >> arr[i];
    int max_gap = get_max_gap(arr,size);
    cout << max_gap << endl;
    delete [] arr;
    return 0;
}
