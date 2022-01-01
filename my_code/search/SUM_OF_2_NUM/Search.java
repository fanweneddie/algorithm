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

public class Search 
{
    public int size;
    private int[] arr;

    Search()
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
            if(arr[mid] > num)
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
        Search search_demo = new Search();
        Scanner scan = new Scanner(System.in);
        search_demo.Input_data(scan);
        System.out.println("please input the target sum number.");
        int target = search_demo.Input_int(scan);
        Indexes i_j = new Indexes();
        i_j = search_demo.Search_ij(target, search_demo.size);
        if(i_j.j != -1)
            System.out.println(i_j.i + " " + i_j.j);
        else
            System.out.println("unfound.");
    }
}