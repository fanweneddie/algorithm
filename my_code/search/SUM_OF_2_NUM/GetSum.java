import java.util.HashMap;
import java.util.Scanner;

// given an array and a target_num
// to get index i and j such that
// arr[i] + arr[j] = target_num
public class GetSum 
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int size = 0;
        int i = 0,j = -1;
        int target = 0,search_num = 0;
        HashMap<Integer, Integer> map = new HashMap<>();
        // input size
        if( scanner.hasNext() )
        {
            try
            {
                size = Integer.parseInt( scanner.next() );
            } catch(NumberFormatException e)
            {
                e.printStackTrace();
            }
        }
        int[] arr = new int [size];
        // input array
        for(i = 0; i < size;++i)
        {
            if( scanner.hasNext() )
            {
                try
                {
                    arr[i] = Integer.parseInt( scanner.next() );
                } catch(NumberFormatException e)
                {
                    e.printStackTrace();
                }
            }
        }
        // input target
        if( scanner.hasNext() )
        {
            try
            {
                target = Integer.parseInt( scanner.next() );
            } catch(NumberFormatException e)
            {
                e.printStackTrace();
            }
        }

        for(i = 0;i < size;++i)
        {
            search_num = target - arr[i];
            if( map.containsKey(new Integer(search_num) ) )
            {
                j = map.get(new Integer(search_num) ).intValue();
                break;
            }
            else
            {
                map.put(new Integer(arr[i]),new Integer(i) );
            }
        }
        if(j != -1)
        {
            if( i < j)
                System.out.println(i + " " + j);
            else
                System.out.println(j + " " + i);
        }
        scanner.close();
    }
}