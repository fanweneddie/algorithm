#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// the infinity of start time
#define INF 100000000

// a task to schedule
class Task
{
    public:
    // the start time of this task
    int start;
    // the remaining time to process this task
    int rest;
};

// a min heap
class MinHeap
{
    private:
    // in a heap: the first index is 1(not 0)
    int arr_len;
    // the length of the heap
    int heap_len;
    // task array
    vector<Task> arr;
    
    public:
    MinHeap()
    {
        arr_len = 0;
        heap_len = 0;
    }

    // some setters and getters
    int get_arr_len()
    {
        return arr_len;
    }

    void set_arr_len(int arr_len)
    {
        this->arr_len = arr_len;
    }

    int get_heap_len()
    {
        return heap_len;
    }

    bool is_empty()
    {
        return heap_len == 0;
    }

    // return parent node's index of node_i
    int get_parent(int node_i)
    {
        return node_i/2;
    }

    // return left node's index of node_i
    int get_left_child(int node_i)
    {
        return node_i*2;
    }

    // return right node's index of node_i
    int get_right_child(int node_i)
    {
        return node_i * 2 + 1;
    }

    // maintain the struture of min heap
    // @param node_i: the possible node that 
    // - might damage the structure of min heap 
    // assume that node_i's left_child and right_child
    // are both the root of a min heap
    void min_heapify(int node_i)
    {
        int l_child = get_left_child(node_i);
        int r_child = get_right_child(node_i);
        // the index of max data 
        // - among arr[node_i],arr[l_child] and arr[r_child]
        int min_index = node_i;
        // check whether l_child is in heap 
        // - and data in l_child's rest is smaller
        if( l_child <= heap_len && 
            arr[l_child].rest < arr[min_index].rest )
            min_index = l_child;
        // check whether r_child is in heap
        // - and data in r_child's rest is smaller
        if( r_child <= heap_len && 
            arr[r_child].rest < arr[min_index].rest )
            min_index = r_child;
        // if node_i's rest is not the smallest
        // - exchange arr[node_i] with arr[min_index]
        // - and continue min_heapify arr[min_index] 
        if(min_index != node_i)
        {
            Task temp = arr[min_index];
            arr[min_index] = arr[node_i];
            arr[node_i] = temp;
            min_heapify(min_index);
        }
    }

    // get and pop out the min element in the heap
    Task extract_min()
    {
        if(heap_len < 1)
        {
            cout << "error: heap underflow\n";
        }
        // min is the minimal element
        Task min = arr[1];
        // maintain the minheap structure
        arr[1] = arr[heap_len];
        heap_len--;
        min_heapify(1);
        return min;
    }

    // decrease the rest value of arr[node_i]
    void decrease_key(int node_i,Task new_task)
    {
        arr[node_i] = new_task;
        // maintain the structure of minheap
        while( node_i > 1 && 
            arr[get_parent(node_i)].rest > arr[node_i].rest )
        {
            Task temp = arr[get_parent(node_i)];
            arr[get_parent(node_i)] = arr[node_i];
            arr[node_i] = temp;
            node_i = get_parent(node_i);
        }
    }

    // insert a new task into the heap
    void insert_key(Task new_task)
    {
        heap_len++;
        Task temp;
        temp.rest = INF;
        // allocate space for arr
        if(heap_len >= arr.size())
            arr.resize(2*heap_len);
        arr[heap_len] = temp;
        decrease_key(heap_len,new_task);
    }

};


// to sort the original tasks
// in a ascending sequence(by starting time)
bool compare(Task task_1,Task task_2) 
{ 
    return task_1.start < task_2.start;
}

int main()
{
    // number of tasks
    int task_num;
    // the vector to store tasks
    vector<Task> task_list;
    // the minheap to store tasks for processing
    MinHeap task_heap = MinHeap();
    // temporary task variable
    Task temp;
    // total process time
    int total = 0;
    
    // input data
    cin >> task_num;
    for(int i = 0;i < task_num;++i)
    {
        cin >> temp.start >> temp.rest;
        // firstly, push the tasks into task_list
        task_list.push_back(temp);
    }

    // sort the task_list by the starting time
    sort(task_list.begin(),task_list.end(),compare);
    // push back a virtual task whose start time is INFINITY
    // into the sort_list 
    temp.start = INF;
    task_list.push_back(temp);

    // index to traverse task_list
    int i = 0;
    // current time, and the gap between current and next start
    int current,duration;

    while(i < task_num)
    {
        // focus on the current start time
        current = task_list[i].start;
        task_heap.insert_key(task_list[i]);
        // insert them all
        while(i < task_num && 
            task_list[i].start == task_list[i+1].start)
        {
            i++;
            task_heap.insert_key(task_list[i]);
        }
        // gap between current and next start time
        duration = task_list[i+1].start - current;
        // deal with the tasks during the duration
        while( current < task_list[i+1].start )
        {
            if( !task_heap.is_empty() )
                temp = task_heap.extract_min();
            else
                break;

            // this task can be finished during this duration
            if(temp.rest <= duration)
            {
                current += temp.rest;
                total += current - temp.start;
                duration = task_list[i+1].start - current;
            }
            // this task cannot be finished during this duration
            // revise the remaining time of this task
            else
            {
                current = task_list[i+1].start;
                temp.rest -= duration;
                task_heap.insert_key(temp);
            }
        }
        i++;
    }

    // output the total process time
    cout << total << endl;
    return 0;
}
