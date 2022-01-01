import java.io.IOException;

// the implementation of radix_sort
// and it extends the method of Sort
// and we still need to implement a new type of stable counting sort
// T(n) = O( d(n + k) ),
// where n = size, k = digit_bound and d = digit_length
// note that the sorted element are all non-negative integers
public class RadixSort extends Sort
{
    private final int NEG_INFINITY = -99999;
    // the array that stores one digit for each element
    private int[] digit_arr;

    // the implementation of radix sort
    public void radix_sort()
    {
        // the max digit length of elements
        int digit_len = 0;
        // the max element value
        int max_value = NEG_INFINITY;
        for(int i = 0; i < size;++i)
        {
            if(arr[i] > max_value)
                max_value = arr[i];
        }
        // get max_digit_len according to max_value
        if(max_value == 0)
            digit_len = 1;
        else
            digit_len = (int)Math.ceil( Math.log10(max_value + 1) );
        
        digit_arr = new int[size];
        // sorting based on each radix
        for(int i = 1;i <= digit_len; ++i )
        {
            // get the digit of each radix
            for(int j = 0;j < size;++j)
            { 
                // e.g. to get 2nd digit of 2314
                // we should calculate (2314%100)/10 = 1
                digit_arr[j] = (int)( (arr[j] % (int)Math.pow(10, i)) 
                            / (int)Math.pow(10,i-1) );
            }
            // use stable counting sort according to that digit
            counting_sort_stable();
        }
    }

    // the stable and O(n+k) counting sort
    // sort according to digit_arr
    // but make the change in arr
    // MUST BE STABLE!!!
    // not in-place since I allocate sorted-arr[0,n]
    public void counting_sort_stable()
    {
        // the array to store the sorted elements
        int[] sorted_arr = new int[size];
        // the upperbound of element's value
        int upper_bound = NEG_INFINITY;
        // looking for the upper bound    -----O(n)
        for(int i = 0; i < size;++i)
        {
            if(digit_arr[i] > upper_bound)
                upper_bound = digit_arr[i];
        }

        // count_arr[j] will store the number of elements that <= j
        int[] count_arr = new int[upper_bound + 1];
        // initialize count_arr[] as 0      ------O(k)
        for(int j = 0;j <= upper_bound;++j)
            count_arr[j] = 0;

        // later, count_arr[j] stores the number of element that = j
        //                                  -------O(n)   
        for(int i = 0; i < size;++i)  
            count_arr[ digit_arr[i] ]++;
    
        // later, count_arr[j] stores the number of elements that <= j
        //                                  -------O(k)
        for(int j = 1;j <= upper_bound;++j)
            count_arr[j] = count_arr[j] + count_arr[j-1];
        
        // place each elements in the right place in arr
        // according to its relative position in digit_arr 
        // note that i is descending,
        // because this can make counting sort stable.
        //                                  --------O(n)
        for(int i = size - 1;i >= 0;--i)
        {
            sorted_arr[ count_arr[ digit_arr[i] ] - 1] = arr[i];
            count_arr[ digit_arr[i] ]--;
        }
        
        // move the data from sorted_arr to arr     
        // note that we need to subtract to complement
        // to restore the original elements   --------O(n)
        for(int i = 0;i < size;++i)
            arr[i] = sorted_arr[i];
    }

    // implement radix sort on each testcase,
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
            // implement radix sort
            radix_sort();
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
        RadixSort rs_demo = new RadixSort();
        rs_demo.Input_test_data();
        rs_demo.auto_test_sort();
    }
}
