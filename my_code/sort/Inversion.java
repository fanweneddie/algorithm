import java.util.Scanner;

// inversion pair: 
// in array A, if i < j but A[i] > A[j],
// then there is an inversion pair

// e.g. A = {3,1,4,2} has 3 inversion pairs
// and they are (3,1),(3,2),(4,2)

// revise merge_sort a little bit
// to get the number of inversion pairs
// in O(nlgn)
public class Inversion
{
    private int size;
    private int[] arr;
    private final int INFINITY = 9999;
    private int inversion_num = 0;
    Inversion()
    {
        size = 0;
        inversion_num = 0;
    }

    public int get_size()
    {
        return size;
    }

    public int get_inversion_num()
    {
        return inversion_num;
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
    
    public void Output_data()
    {
        // output the numbers in the array
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

    // use merge-sort to make the array ascending
    // T(n) = O(nlogn)
    // note that Arr[end] is included to be sorted
    public void Merge_sort_inversion(int start,int end)
    {
        if( start < end)
        {
            int mid = (start + end)/2;
            // divide
            Merge_sort_inversion(start, mid);
            Merge_sort_inversion(mid + 1, end);
            // merge
            Merge_inversion(start,mid,end);
        }
    }

    // merge the sorted array of A[start,mid] 
    // and A[mid+1,end] to A[start,end]
    // NOTE: INCREMENT INVERSION_NUM WHEN MERGING
    private void Merge_inversion(int start,int mid,int end)
    {
        int i,j;
        // size of Left and Right
        int left_size = mid - start + 1;
        int right_size = end - mid;
        // initialize array Left and Right
        int[] Left = new int[left_size + 1];
        int[] Right = new int[right_size + 1];
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
        }
    }

    public static void main(String args[])
    {
        Inversion ivs_demo = new Inversion();
        Scanner scan = new Scanner(System.in);
        ivs_demo.Input_data(scan);
        ivs_demo.Output_data();
        // use merge-sort to calculate inversion number
        ivs_demo.Merge_sort_inversion(0, ivs_demo.get_size() - 1 );
        System.out.println("the number of inversion pairs is " 
        + ivs_demo.get_inversion_num() );
    }
}
