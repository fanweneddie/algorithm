#include <iostream>
#include <vector>
#include <deque>
#include <map>
using namespace std;
#define INF 999999
// the page stored in the cache
class Page
{
    public:
    // the ID number of the page
    int id;
    // the order of the next ID page
    int next;
};

// the page stored in the list
class Page_info
{
    public:
    // position in cache
    int cache_pos;
    // the page pos
    deque<int> page_pos;
};

// stores the appearing pos of each page
map<int,Page_info> page_list;

// a max heap
// note that we need to alter the cache_pos in 
// the Page's corresponding page_info in page_list
// (in order to increase data in heap more efficiently)
class MaxHeap
{
    private:
    // in a heap: the first index is 1(not 0)
    int arr_len;
    // the length of the heap
    int heap_len;
    // the max length of the heap
    int max_len;
    // page array
    vector<Page> arr;
    
    public:
    // init the MaxHeap with the max_len
    MaxHeap(int size)
    {
        arr_len = 0;
        heap_len = 0;
        max_len = size;
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

    bool is_full()
    {
        return heap_len == max_len;
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

    // maintain the struture of max heap
    // @param node_i: the possible node that 
    // - might damage the structure of max heap 
    // assume that node_i's left_child and right_child
    // are both the root of a max heap
    void max_heapify(int node_i)
    {
        int l_child = get_left_child(node_i);
        int r_child = get_right_child(node_i);
        // the index of max data 
        // - among arr[node_i],arr[l_child] and arr[r_child]
        int max_index = node_i;
        // check whether l_child is in heap 
        // - and data in l_child's rest is smaller
        if( l_child <= heap_len && 
            arr[l_child].next > arr[max_index].next )
            max_index = l_child;
        // check whether r_child is in heap
        // - and data in r_child's rest is smaller
        if( r_child <= heap_len && 
            arr[r_child].next > arr[max_index].next )
            max_index = r_child;
        // if node_i's rest is not the smallest
        // - exchange arr[node_i] with arr[min_index]
        // - and continue min_heapify arr[min_index] 
        if(max_index != node_i)
        {
            Page temp = arr[max_index];
            arr[max_index] = arr[node_i];
            // update the info in page_list
            page_list[ arr[node_i].id ].cache_pos = max_index;
            arr[node_i] = temp;
            // update the info in page_list
            page_list[ temp.id ].cache_pos = node_i;
            max_heapify(max_index);
        }
    }

    // get and pop out the max element in the heap
    Page extract_max()
    {
        if(heap_len < 1)
        {
            cout << "error: heap underflow\n";
        }

        // max is the maximal element
        Page max = arr[1];
        // maintain the maxheap structure
        arr[1] = arr[heap_len];
        page_list[ arr[heap_len].id ].cache_pos = 1;
        heap_len--;
        max_heapify(1);
        return max;
    }

    // increase the rest value of arr[node_i]
    void increase_key(int node_i,Page new_page)
    {
        arr[node_i] = new_page;
        page_list[ new_page.id ].cache_pos = node_i;
        // maintain the structure of maxheap
        while( node_i > 1 && 
            arr[get_parent(node_i)].next < arr[node_i].next )
        {
            Page temp = arr[get_parent(node_i)];
            arr[get_parent(node_i)] = arr[node_i];
            page_list[ arr[node_i].id ].cache_pos = get_parent(node_i);
            arr[node_i] = temp;
            page_list[temp.id].cache_pos = node_i;
            node_i = get_parent(node_i);
        }
    }

    // insert a new task into the heap
    void insert_key(Page new_page)
    {
        heap_len++;
        Page temp;
        temp.next = -INF;
        // allocate space for arr
        if(heap_len >= arr.size())
            arr.resize(2*heap_len);
        arr[heap_len] = temp;
        page_list[new_page.id].cache_pos = heap_len;
        increase_key(heap_len,new_page);
    }

};


// use a heap to simulate a cache
// to search whether the page is in the cache
// and search the latest in page
// T(n) = nlgk, where n is page number and k is cache size
int main()
{
    // the number of data
    // and the size of cache
    int page_num,cache_size;
    // the input page sequence
    vector<int> page_sequence;
    // the iterator for page_list
    map<int, Page_info>::iterator iter;
    // cache miss time
    int miss_time = 0;
    // input data
    cin >> page_num >> cache_size;
    for(int i = 1;i <= page_num;++i)
    {
        // the temp page id
        int page_id;
        cin >> page_id;
        // add the current page into page sequence
        page_sequence.push_back(page_id);
        // add the position into data_list
        iter = page_list.find(page_id);
        if( iter == page_list.end() )
        {
            Page_info temp_page_info;
            temp_page_info.cache_pos = 0;
            page_list.insert(pair<int,Page_info>
                    ( page_id,temp_page_info ));
        }
        // update the page position
        page_list[page_id].page_pos.push_back(i);
    }

    // push back INFINITY as last position for each page
    for(iter = page_list.begin(); iter != page_list.end(); iter++)
        iter->second.page_pos.push_back(INF);

    // use a maxHeap to act as a cache
    MaxHeap cache = MaxHeap(cache_size);

    for(int i = 0;i < page_num;++i)
    {
        int page_id = page_sequence[i];
        // cache miss
        if(page_list[page_id].cache_pos == 0)
        {
            miss_time++;
            // alter the next pos for this page
            page_list[page_id].page_pos.pop_front();
            // cache is full
            // substitution strategy: "kick out the latest in"
            if( cache.is_full() )
            {
                // kick out the latest in page
                Page out = cache.extract_max();
                page_list[out.id].cache_pos = 0;
            }
            // push this page into the cache
            Page temp_page;
            temp_page.id = page_id;
            temp_page.next = page_list[page_id].page_pos.front();
            // cache_pos will be altered
            cache.insert_key(temp_page);
        }
        // cache hit
        else
        {
            // alter the next pos for this page
            page_list[page_id].page_pos.pop_front();
            Page temp_page;
            temp_page.id = page_id;
            temp_page.next = page_list[page_id].page_pos.front();
            cache.increase_key(page_list[page_id].cache_pos,temp_page);   
        }
    }

    cout << miss_time << endl;
    return 0;
}
