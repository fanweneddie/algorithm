import java.util.Scanner;

// the indexes of i and j to be returned
class Indexes
{
    public int i,j;
    Indexes()
    {
        i = -1;
        j = -1;
    }
}

// given an array and a target_num
// to get a binary answer
// yes: there exists i and j such that 
// arr[i] + arr[j] = target_num
// no: there doesn't exist ...
public class Search_sum
{
    public int size;
    private int[] arr;

    Search_sum()
    {
        size = 0;
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

    // output the numbers in the array
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

    // the definition of Merge and Merge_sort
    public void Merge(int start,int mid,int end)
    {
        int i,j,k;
        final int INFINITY = 999;
        int left_size = mid - start + 1;
        int right_size = end - mid;
        int[] Left_arr = new int[left_size + 1];
        int[] Right_arr = new int[right_size + 1];
        for(i = 0; i < left_size;++i)
            Left_arr[i] = arr[start + i];
        for(j = 0;j < right_size;++j)
            Right_arr[j] = arr[mid + 1 + j];
        Left_arr[left_size] = INFINITY;
        Right_arr[right_size] = INFINITY;
        i = 0;
        j = 0;
        for(k = start; k <= end;++k)
        {
            if(Left_arr[i] < Right_arr[j])
            {
                arr[k] = Left_arr[i];
                i++;
            }
            else
            {
                arr[k] = Right_arr[j];
                j++;
            }
        }
    }   

    public void Merge_sort(int start,int end)
    {
        if(start < end)
        {
            int mid = (start + end)/2;
            Merge_sort(start, mid);
            Merge_sort(mid + 1, end);
            Merge(start,mid,end); 
        }
    }

    // binary search the num in arr[start,end](inclusive)
    public int Binary_Search(int start,int end,int num)
    {
        if(start == end)
        {
            if(arr[start] == num)
                return start;
            else
                return -1;
        }
        else
        {
            int mid = (start + end)/2;        
            if(arr[mid] >= num)
                return Binary_Search(start, mid, num);
            else
                return Binary_Search(mid + 1, end, num);
        }
    }

    // given num, search index i and j 
    // s.t. arr[i] + arr[j] = num
    // @param num: the target sum number
    // @param len: the length of arr
    public Indexes Search_ij(int num,int len)
    {
        Indexes i_j = new Indexes();
        for(int i = 0;i < len;++i)
        {
            int j = Binary_Search(0, len-1, num-arr[i]);
            if(j != -1)
            {
                i_j.i = i;
                i_j.j = j;
                return i_j; 
            } 
        }
        return i_j;
    }



    public static void main(String args[])
    {
        Search_sum search_demo = new Search_sum();
        Scanner scan = new Scanner(System.in);
        search_demo.Input_data(scan);
        System.out.println("please input the target sum number.");
        int target = search_demo.Input_int(scan);
        Indexes i_j = new Indexes();
        search_demo.Merge_sort(0, search_demo.size - 1);
        i_j = search_demo.Search_ij(target, search_demo.size);
        if(i_j.j != -1)
            System.out.println("found.");
        else
            System.out.println("unfound.");
        scan.close();
    }
}