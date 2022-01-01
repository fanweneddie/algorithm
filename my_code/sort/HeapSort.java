import java.util.Scanner;

public class HeapSort 
{
    // in a heap: the first index is 1(not 0)
    private int arr_len;
    private int heap_len;
    private int[] arr;
    HeapSort()
    {
        arr_len = 0;
        heap_len = 0;
    }

    public int get_arr_len()
    {
        return arr_len;
    }

    public void set_arr_len(int arr_len)
    {
        this.arr_len = arr_len;
    }

    public int get_heap_len()
    {
        return heap_len;
    }

    // return parent node's index of node_i
    private int get_parent(int node_i)
    {
        return node_i/2;
    }

    // return left node's index of node_i
    private int get_left_child(int node_i)
    {
        return node_i*2;
    }

    // return right node's index of node_i
    private int get_right_child(int node_i)
    {
        return node_i * 2 + 1;
    }

    // maintain the struture of max heap
    // @param node_i: the possible node that 
    // - might damage the structure of max heap 
    // assume that node_i's left_child and right_child
    // are both the root of a max heap
    private void max_heapify(int node_i)
    {
        int l_child = get_left_child(node_i);
        int r_child = get_right_child(node_i);
        // the index of max data 
        // - among arr[node_i],arr[l_child] and arr[r_child]
        int max_index = node_i;
        // check whether l_child is in heap 
        // - and data in l_child is larger
        if( l_child <= heap_len && 
            arr[l_child] > arr[max_index] )
            max_index = l_child;
        // check whether r_child is in heap
        // - and data in r_child is larger
        if( r_child <= heap_len && 
            arr[r_child] > arr[max_index] )
            max_index = r_child;
        // if node_i's data is not the largest
        // - exchange arr[node_i] with arr[max_index]
        // - and continue max_heapify arr[max_index] 
        if(max_index != node_i)
        {
            int temp = arr[max_index];
            arr[max_index] = arr[node_i];
            arr[node_i] = temp;
            max_heapify(max_index);
        }
    }

    // maintain the struture of max heap
    // in a non-recursive method
    // @param node_i: the possible node that 
    // - might damage the structure of max heap 
    // assume that node_i's left_child and right_child
    // are both the root of a max heap
    private void max_heapify_non_recur(int node_i)
    {
        // index of left child and right child
        // of node_i
        int l_child;
        int r_child;
        // the index of max data 
        // - among arr[node_i],arr[l_child] and arr[r_child]
        int max_index;
        // use non-recursive way rather than recursion
        while(true)
        {
            l_child = get_left_child(node_i);
            r_child = get_right_child(node_i);
            // check whether l_child is in heap 
            // - and data in l_child is larger
            if( l_child <= heap_len && 
                arr[l_child] > arr[node_i] )
                max_index = l_child;
            else
                max_index = node_i;
            // check whether r_child is in heap
            // - and data in r_child is larger
            if( r_child <= heap_len && 
                arr[r_child] > arr[max_index] )
                max_index = r_child;
            // max_index = node_i,
            // so just break
            if(max_index == node_i)
                break;
            // if node_i's data is not the largest
            // - exchange arr[node_i] with arr[max_index]
            // - and continue max_heapify arr[max_index] 
            else
            {
                int temp = arr[max_index];
                arr[max_index] = arr[node_i];
                arr[node_i] = temp;
                node_i = max_index;
            }            
        }
    }

    // build the max heap 
    // -based on arr(data starts from arr[1])
    private void build_max_heap()
    {
        heap_len = arr_len;
        // maintain the structure of max heap
        // -from the last non-leaf node
        for(int i = heap_len/2;i >= 1;--i)
            max_heapify_non_recur(i);
    }
    // use heap_sort algo to sort arr
    // - in an ascending sequence
    // T(n) = O(nlgn)
    public void heap_sort()
    {
        build_max_heap();
        for(int i = arr_len;i >= 2;--i)
        {
            int temp = arr[i];
            arr[i] = arr[1];
            arr[1] = temp;
            heap_len--;
            max_heapify_non_recur(1);
        }
    }

    // input an integer
    public int Input_int(Scanner scan)
    {
        int num_in = 0;
        if( scan.hasNext() )
        {
            try
            {
                num_in = Integer.parseInt( scan.next() );
            } catch(NumberFormatException e)
            {
                e.printStackTrace();
            }
        }
        return num_in;
    }
    
    // input the data for array
    public void Input_data(Scanner scan)
    {
        // input original numbers of arr_len
        System.out.println("please input " + arr_len + " numbers.");
        arr = new int[arr_len + 1];
        // array's data starts from index 1
        for(int i = 1; i <= arr_len;++i)
        {
            if( scan.hasNext() )
            {
                try
                {
                    arr[i] = Integer.parseInt( scan.next() );
                } catch(NumberFormatException e)
                {
                    e.printStackTrace();
                }
            }
        }
    }
    
    // output the numbers in the array
    public void Output_data()
    {
        if(arr_len == 0)
            System.out.println("output failure due to no data.");
        else
        {
            System.out.println("the data of array are");
            // array's data starts from 1
            for(int i = 1;i <= arr_len;++i)
                System.out.print(arr[i] + " ");
            System.out.print('\n');
        }
    }

    public static void main(String args[])
    {
        HeapSort HS_demo = new HeapSort();
        Scanner scan = new Scanner(System.in);
        // input the length of array
        System.out.println("please input the length of array.");
        int arr_len = HS_demo.Input_int(scan);
        HS_demo.set_arr_len(arr_len);
        // input the data of array
        HS_demo.Input_data(scan);
        // heap_sort the input data
        HS_demo.heap_sort();
        // print the sorted data
        System.out.println("after sorting.");
        HS_demo.Output_data();
    }

}