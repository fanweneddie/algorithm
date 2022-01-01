import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;

class TestCase
{
    // the array to store input number in each group
    public int[] input_arr;
    public int input_size;  
    // the expected output array
    public int[] output_arr;
    TestCase()
    {
        input_size = 0;
    }
}

// the class of SORTING DEMO
// contrains the array,size
// methods: Input_int(),Input_data(),Output_data()
class Sort
{
    protected int size;
    protected int[] arr;
    protected final int INFINITY = 9999;
    protected Vector<TestCase> testcases;
    Sort()
    {
        size = 0;
    }

    public int get_size()
    {
        return size;
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

    // input test data from the file "testcase.txt"
    boolean Input_test_data() throws IOException
    {
        int line_num = 0;
        boolean has_error = false;
        // the string to store each line
        String str;
        // the vector to store the info of testcases
        testcases = new Vector<TestCase>();
        try
        {
            BufferedReader in = new BufferedReader
                    (new FileReader("testcase.txt"));
            // read the file
            while( (str = in.readLine()) != null && !has_error )
            {
                // record the line read for error report
                line_num++;
                // skip the annotation and blank space
                if( str.startsWith("//") || str.equals("") )
                {
                    continue;
                }   

                boolean read_group_finish = false;
                TestCase tc = new TestCase();
                // use state to receive input
                int state = 1;
                // parse the input of each group
                while( (str = in.readLine()) != null 
                    && !has_error && !read_group_finish )
                {  
                    switch(state)
                    {
                        // 1 -> 2: input size of that group
                        case 1:
                            tc.input_size = Integer.parseInt(str);
                            state = 2;
                            break;
                        // 2 -> 3: input origin data
                        case 2:
                            // use regular expression to split str
                            // "\\s" means multiple blankspace
                            String[] input_str;
                            input_str = str.split("\\s+");
                            // expected input size != actual input size
                            if(input_str.length != tc.input_size )
                            {
                                System.out. println("expected input size" + 
                                    " != actual input size: line " + line_num);
                                has_error = true;
                                break;
                            }
                            else
                            {
                                // input the data to input_arr
                                tc.input_arr = new int[tc.input_size];
                                for(int i = 0;i < tc.input_size;++i)
                                {
                                    tc.input_arr[i] = Integer.parseInt(input_str[i]);
                                }
                                state = 3;
                                break;
                            }
                        // 3 -> 1, get expected output data
                        case 3:
                            input_str = str.split("\\s+");
                            // input the data to input_arr
                            if(input_str.length != tc.input_size )
                            {
                                System.out. println("expected input size" + 
                                    " != actual input size: line " + line_num);
                                has_error = true;
                                break;
                            }
                            else
                            {
                                tc.output_arr = new int[tc.input_size];
                                for(int i = 0;i < tc.input_size;++i)
                                {
                                    tc.output_arr[i] = Integer.parseInt(input_str[i]);
                                }
                                // INPUT is complete
                                testcases.addElement(tc);
                                read_group_finish = true;
                                state = 1;
                            }
                            break;
                    }// switch
                }// while
            }// while
            in.close();
        }
        catch (IOException e) 
        { 
            e.printStackTrace();
        } 

        // if there is error, return false
        // else, return true
        return !has_error;
    }// auto_test()
}

// a specific Sort demo
// extends the method of abstract class Sort
// includes basic sorting method such as
// selection sort, insertion sort and merge sort
public class BasicSort extends Sort
{
    
    // use selection sort to make the array ascending
    // T(n) = O(n^2)
    public void Selection_sort()
    {
        if(size == 0)
            System.out.println("sorting failure due to no data.");
        else
        {
            int index_min = 0;
            int value_min = -INFINITY;
            // set the location of array 
            for(int i = 0;i < size - 1;++i)
            {
                index_min = i;
                value_min = arr[i];
                // find the minimal data in each round
                for(int j = i;j < size;++j)
                {
                    if(arr[j] < value_min)
                    {
                        value_min = arr[j];
                        index_min = j;
                    }
                }
                /*
                // this swap can make the sorting unstable
                // swap arr[i] with arr[index_min]
                arr[index_min] = arr[i];
                arr[i] = value_min;
                */
                // this movement makes the sorting stable
                // without alter T(n) 
                // (although increase constant coefficient)
                for(int j = index_min - 1;j >= i;--j)
                    arr[j+1] = arr[j];
                arr[i] = value_min;
            }
        }
    }


    // use insertion_sort to make the array descending
    // T(n) = O(n^2)
    public void Insertion_sort()
    {
        if(size == 0)
            System.out.println("sorting failure due to no data.");
        else
        {
            int key = 0;
            // let arr[0~i] to be sorted in a descending way
            for(int i = 1; i < size;++i)
            {
                key = arr[i];
                int j = i-1;
                // right shift the data that is bigger than _key_
                while( j >= 0 && arr[j] < key )
                // if we want to sort data in an ascending way, 
                // let '<' become '>''
                {
                    arr[j+1] = arr[j];
                    j--;
                }
                arr[j+1] = key;
            }
        }
    }


    // use merge-sort to make the array ascending
    // T(n) = O(nlogn)
    // note that Arr[end] is included to be sorted
    public void Merge_sort(int start,int end)
    {
        if( start < end)
        {
            int mid = (start + end)/2;
            // divide
            Merge_sort(start, mid);
            Merge_sort(mid + 1, end);
            // merge
            Merge(start,mid,end);
        }
    }

    // merge the sorted array of A[start,mid] 
    // and A[mid+1,end] to A[start,end]
    private void Merge(int start,int mid,int end)
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
            }
            // Left[i] <= Left[j]
            else
            {
                arr[k] = Left[i];
                i++;
            }
        }
    }

/*
    // another merge function without the sentinel
    // the code is ugly and its length is too long 
    private void Merge_new(int start, int mid,int end)
    {
        int i,j,k;
        int left_size = mid - start + 1;
        int right_size = end - mid;
        // Left and Right for array without senitel
        int[] Left = new int[left_size];
        int[] Right = new int[right_size];
        // copy A[start,mid](both inclusive) to Left
        for(i = 0;i < left_size;++i)
            Left[i] = arr[start + i];
        // copy A[mid+1,end](both inclusive) to Right
        for(j = 0;j < right_size;++j)
            Right[j] = arr[mid + 1 + j];
        // merging process without sentinel
        i = 0;
        j = 0;
        k = start;
        // compare and copy
        while(i < left_size && j < right_size)
        {
            if( Left[i] <= Right[j] )
            {
                arr[k] = Left[i];
                i++;
                k++;
            }
            else
            {
                arr[k] = Right[j];
                j++;
                k++;
            }
        }
        // Left is fully copied
        if(i == left_size)
        {
            while(j < right_size)
            {
                arr[k] = Right[j];
                j++;
                k++;
            }
        }
        // Right is fully copied
        else if( j== right_size)
        {
            while(i < left_size)
            {
                arr[k] = Left[i];
                i++;
                k++;
            }
        }
        if(i == left_size && j == right_size)
            return;
        // *
        for(int k = start;k <= end;++k)
        {
            // Left is fully copied 
            if( i >= left_size)
            {
                while(j < right_size)
                {
                    arr[k] = Right[j];
                    k++;
                    j++;
                }
            }
            // Right is fully copied
            else if( j >= right_size)
            {
                while(i < left_size)
                {
                    arr[k] = Left[i];
                    k++;
                    i++;
                }
            }
            // copy Left and Right to Array
            else
            {
               
            }
        }
    }
    */

    // implement sorting of sort_type on each testcase,
    // compare the expected result and actual result,
    // and give an answer to show whether the sorting
    // is correct or not.
    // @param sort_type: which method to sort
    // selection -- selection sort
    // insertion -- insertion sort
    // merge -- merge sort
    // else -- report the error and do not sort
    void auto_test_sort(String sort_type)
    {
        System.out.println("########################################################");
        for( TestCase tc : testcases)
        {
            size = tc.input_size;
            arr = new int[size + 0];
            for(int i = 0; i < size;++i)
                arr[i] = tc.input_arr[i];
            // choose to sort according to the sort_type
            if( sort_type.equals("selection") )
            {
                System.out.println("selection sort:");
                Selection_sort();
            }
            else if( sort_type.equals("insertion") )
            {
                System.out.println("insertion sort:");
                Insertion_sort();
            }
            else if( sort_type.equals("merge") )
            {
                System.out.println("merge sort:");
                Merge_sort(0,size - 1);
            }
            else
                System.out.println("invalid sorting type");
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
        BasicSort bs_demo = new BasicSort();
        Scanner scan = new Scanner(System.in);
        bs_demo.Input_test_data();
        bs_demo.auto_test_sort("selection");
        bs_demo.auto_test_sort("insertion");
        bs_demo.auto_test_sort("merge");
        scan.close();
    }
}
