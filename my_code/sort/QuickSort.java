import java.util.Scanner;

// the implementation of quick_sort
// and it extends the method of Sort
public class QuickSort extends Sort
{
    // quick sort arr[start,..., end](both inclusive)
    // average T(n) = O(nlgn)
    // worst T(n) = O(n^2)
    public void quick_sort(int start, int end)
    {
        // the condition to do recursion
        if(start < end)
        {   
            // get the index of pivot element
            int pivot_index = partition(start,end);
            // sort the subarray 
            // at the left and right of pivot element 
            quick_sort(start,pivot_index - 1);
            quick_sort(pivot_index + 1,end);
        }
    }

    // find the index of pivot element( = arr[end])
    // partition as left part, pivot element and right part
    // s.t. left_part_element <= pivot_element < right_part_element
    private int partition(int start,int end)
    {
        int pivot_ele = arr[end];
        // i is the right most position of the left part
        int i = start - 1;
        int temp;
        for(int j = start; j < end;++j)
        {
            // if arr[j] is less,
            // let it be in the left part
            if(arr[j] <= pivot_ele )
            {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // exchange arr[i+1] with arr[end]
        arr[end] = arr[i+1];
        arr[i+1] = pivot_ele;
        // i+1 is the index of pivot element
        return i+1;
    }

    public static void main(String args[])
    {
        QuickSort qs_demo = new QuickSort();
        Scanner scan = new Scanner(System.in);
        qs_demo.Input_data(scan);
        qs_demo.quick_sort(0,qs_demo.size - 1);
        qs_demo.Output_data();
        scan.close();
    }
}   
