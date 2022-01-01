import java.util.Scanner;

/*
given an array
find out the subarray with max sum
e.g 
1. arr = {13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7},
then max subarray = arr[7 ... 10] ={18,20,-7,12}, whose sum is 43

2. arr = {1,2,3,4} > 0
then max subarray = arr[0 ... 3] ={1,2,3,4}, whose sum is 10

3. arr = {-1,-2,-3,-4}
then max subarray = arr[0,...0] = {-1},whose sum is -1

here I use divide-and-conquer method.
then we have T(n) = 2T(n/2) + n,
so T(n) = O(nlgn)
*/

// the struct of subarray info 
// to be sent back
class Subarray_info
{
    public int l_bound;
    public int r_bound;
    public int sum;
    Subarray_info()
    {
        l_bound = 0;
        r_bound = 0;
        sum = 0;
    }

    Subarray_info(int l_bound,int r_bound,int sum)
    {
        this.l_bound = l_bound;
        this.r_bound = r_bound;
        this.sum = sum;
    }

}

// given an array
// find out the subarray with
// max sum
public class Max_subarray
{
    private int arr[];
    public int size;
    private final int NEG_INFINITY = -9999;
    Max_subarray()
    {
        size = 0;
    }

    // input numbers in the array
    public void Input_array(Scanner scan)
    {
        // input size
        System.out.println("please input the array size.");
        if( scan.hasNext() )
        {
            try
            {
                size = Integer.parseInt( scan.next() );
            } catch(NumberFormatException e)
            {
                e.printStackTrace();
            }
        }
        // input original numbers of size
        System.out.println("please input " + size + " numbers.");
        arr = new int[size];
        for(int i = 0; i < size;++i)
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

    // output numbers in the array
    public void Output_data()
    {
        if(size == 0)
            System.out.println("output failure due to no data.");
        else
        {
            System.out.println("the data of array are");
            for(int i = 0;i < size;++i)
                System.out.print(arr[i] + " ");
            System.out.print('\n');
        }
    }

    // find out the max subarray of
    // arr[low,...,high]
    // use divide-and-conquer method
    // then we have T(n) = 2T(n/2) + n
    // so T(n) = O(nlgn)
    public Subarray_info find_max_subarray(int low,int high)
    {
        if(high == low)
        {
            Subarray_info ret_si 
                = new Subarray_info(low,high,arr[low]);
            return ret_si;
        }
        else
        {
            int mid = (low + high)/2;
            Subarray_info left_si = new Subarray_info();
            Subarray_info right_si = new Subarray_info();
            Subarray_info cross_si = new Subarray_info();
            left_si = find_max_subarray(low,mid);
            right_si = find_max_subarray(mid+1, high);
            cross_si = find_max_cross_subarray(low,mid,high);
            if(left_si.sum > right_si.sum 
                && left_si.sum > cross_si.sum)
                return left_si;
            else if( right_si.sum > left_si.sum 
                && right_si.sum > cross_si.sum )
                return right_si;
            else
                return cross_si;
        }
    }

    // given arr[low,...,high]
    // find the max subarray that crosses arr[mid]
    public Subarray_info 
        find_max_cross_subarray(int low,int mid,int high)
    {
        // get the index of the 
        // max sum in the left part 
        int left_bound_index = mid;
        int left_max_sum = NEG_INFINITY;
        int curr_sum = 0;
        for(int i = mid;i >= 0;--i)
        {
            curr_sum += arr[i];
            if(curr_sum > left_max_sum)
            {
                left_max_sum = curr_sum;
                left_bound_index = i;
            }
        }

        // get the index of the 
        // max sum in the right part 
        int right_bound_index = mid + 1;
        int right_max_sum = NEG_INFINITY;
        curr_sum = 0;
        for(int i = mid + 1;i < size;++i)
        {
            curr_sum += arr[i];
            if(curr_sum > right_max_sum)
            {
                right_max_sum = curr_sum;
                right_bound_index = i;
            }
        }

        // return the left bound and right bound
        // and the sum of the max cross subarray
        Subarray_info ret_si 
            = new Subarray_info(left_bound_index,
                right_bound_index,
                left_max_sum + right_max_sum);
        return ret_si;
    }

    public static void main(String args[])
    {
        Max_subarray ms_demo = new Max_subarray();
        Scanner scan = new Scanner(System.in);
        ms_demo.Input_array(scan);
        // get the info of max_subarray
        Subarray_info max_subarray_info = new Subarray_info();
        max_subarray_info = ms_demo.
            find_max_subarray(0, ms_demo.size - 1);
        // print the result
        System.out.println("------------------------------");
        System.out.println("max subarray is arr[" + 
            max_subarray_info.l_bound + " ... " 
            + max_subarray_info.r_bound + "]");
        System.out.println("and the sum is " + 
            max_subarray_info.sum);
        scan.close();
    }

}