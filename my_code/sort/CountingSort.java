import java.io.IOException;

// the implementation of counting_sort
// and it extends the method of Sort
// T(n) = O(n + k),
// where n = size and k = bound
// note that the sorted element are integers(negative is fine)
// but they can't be real numbers
public class CountingSort extends Sort
{
    private final int NEG_INFINITY = -99999;

    // the stable and O(n+k) counting sort
    // not in-place since I allocate sorted-arr[0,n]
    public void counting_sort_stable()
    {
        // the array to store the sorted elements
        int[] sorted_arr = new int[size];
        // the upperbound of element's value
        int upper_bound = NEG_INFINITY;
        // the negative lower bound of element's value
        // and the positive complement to make arr non-negative
        int neg_lower_bound = 0;
        int complement = 0;
        // looking for the upper bound
        // and negative lower bound     -----O(n)
        for(int i = 0; i < size;++i)
        {
            if(arr[i] > upper_bound)
                upper_bound = arr[i];
            if(arr[i] < neg_lower_bound)
                neg_lower_bound = arr[i];
        }
        
        // there exists negative integers,
        // so we need to add a constant to the arr
        // s.t. the new arr is non negative
        if(neg_lower_bound < 0)
        {
            complement = -neg_lower_bound;
            for(int i = 0;i < size;++i)
            {
                arr[i] += complement;
            }
            upper_bound += complement;
        }

        // count_arr[j] will store the number of elements that <= j
        int[] count_arr = new int[upper_bound + 1];
        // initialize count_arr[] as 0      ------O(k)
        for(int j = 0;j <= upper_bound;++j)
            count_arr[j] = 0;

        // later, count_arr[j] stores the number of element that = j
        //                                  -------O(n)   
        for(int i = 0; i < size;++i)  
            count_arr[ arr[i] ]++;
    
        // later, count_arr[j] stores the number of elements that <= j
        //                                  -------O(k)
        for(int j = 1;j <= upper_bound;++j)
            count_arr[j] = count_arr[j] + count_arr[j-1];
        
        // place each elements in the right place
        // according to its relative position in the arr
        // note that i is descending,
        // because this can make counting sort stable.
        //                                  --------O(n)
        for(int i = size - 1;i >= 0;--i)
        {
            sorted_arr[ count_arr[ arr[i] ] - 1] = arr[i];
            count_arr[ arr[i] ]--;
        }
        
        // move the data from sorted_arr to arr     
        // note that we need to subtract to complement
        // to restore the original elements   --------O(n)
        for(int i = 0;i < size;++i)
            arr[i] = sorted_arr[i] - complement;
    }

    // the in-place and O(n+k) counting sort
    // but not stable
    public void counting_sort_inplace()
    {
        // the upperbound of element's value
        int upper_bound = NEG_INFINITY;
        // the negative lower bound of element's value
        // and the positive complement to make arr non-negative
        int neg_lower_bound = 0;
        int complement = 0;
        // looking for the upper bound
        // and negative lower bound     -----O(n)
        for(int i = 0; i < size;++i)
        {
            if(arr[i] > upper_bound)
                upper_bound = arr[i];
            if(arr[i] < neg_lower_bound)
                neg_lower_bound = arr[i];
        }
        
        // there exists negative integers,
        // so we need to add a constant to the arr
        // s.t. the new arr is non negative
        if(neg_lower_bound < 0)
        {
            complement = -neg_lower_bound;
            for(int i = 0;i < size;++i)
            {
                arr[i] += complement;
            }
            upper_bound += complement;
        }

        // count_arr[j] will store the number of elements that <= j
        int[] count_arr = new int[upper_bound + 1];
        // initialize count_arr[] as 0      ------O(k)
        for(int j = 0;j <= upper_bound;++j)
            count_arr[j] = 0;

        // later, count_arr[j] stores the number of element that = j
        //                                  -------O(n)   
        for(int i = 0; i < size;++i)  
            count_arr[ arr[i] ]++;
    
        // later, count_arr[j] stores the number of elements that <= j
        //                                  -------O(k)
        for(int j = 1;j <= upper_bound;++j)
            count_arr[j] = count_arr[j] + count_arr[j-1];
        // when count_arr[j] == repeat_end,
        // put next element into arr
        int repeat_end = 0;
        for(int j = upper_bound;j >= 0;--j)
        {
            if(j > 0)
                repeat_end = count_arr[j-1];
            else
                repeat_end = 0;
            while( count_arr[j] > repeat_end)
            {
                arr[ count_arr[j] - 1 ] = j;
                count_arr[j]--;
            }
        }

        for(int i = 0; i < size;++i)
        {
            arr[i] -= complement;
        }
    }
    

    // implement counting sort on each testcase,
    // compare the expected result and actual result,
    // and give an answer to show whether the sorting
    // is correct or not.
    void auto_test_sort()
    {
        System.out.println("########################################################");
        for( TestCase tc : testcases)
        {
            size = tc.input_size;
            arr = new int[size + 0];
            for(int i = 0; i < size;++i)
                arr[i] = tc.input_arr[i];
            // implement counting sort
            counting_sort_inplace();
            // print the expected output result:
            System.out.println("expected result:");
            for(int i = 0;i < size;++i)
            {
                System.out.print(tc.output_arr[i] + " ");
            }
            System.out.print("\n");
            // print the actual output result:
            System.out.println("actual result:");
            for(int i = 0;i < size;++i)
            {
                System.out.print(arr[i] + " ");
            }
            System.out.print("\n");
            // check the whether the sorting is correct
            boolean correct = true;
            for(int i = 0; i < size;++i)
            {
                if(arr[i] != tc.output_arr[i])
                {
                    correct = false;
                    break;
                }
            }
            if(correct)
                System.out.println("this testcase is correct");
            else
                System.out.println("this testcase is incorrect");
            System.out.println("----------------------------------");
        }
    }

    public static void main(String args[]) throws IOException
    {
        CountingSort cs_demo = new CountingSort();
        cs_demo.Input_test_data();
        cs_demo.auto_test_sort();
    }
}
