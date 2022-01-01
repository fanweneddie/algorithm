import java.util.Scanner;

// the implementation of shell_sort
// and it extends the method of Sort
public class ShellSort extends Sort
{
    public void shell_sort()
    {
        // an array which stores the number of groups
        // and the distance between two adjacent numbers is gap
        // where gap = number of groups
        int[] Gaps = new int[]{1,2,4,8};
        // gap is gradually decremented
        for(int i = Gaps.length - 1;i >= 0; -- i)
        {
            int gap = Gaps[i];
            // in each group, use insertion sort
            for(int j = gap;j < size;++j)
            {
                if(arr[j] < arr[j-gap])
                {
                    int key = arr[j];
                    int k = j - gap;
                    while(k >= 0 && key < arr[k])
                    {
                        arr[k + gap] = arr[k];
                        k = k - gap;
                    }
                    arr[k + gap] = key;
                }
            } // for
        }
    }

    public static void main(String args[])
    {
        ShellSort ss_demo = new ShellSort();
        Scanner scan = new Scanner(System.in);
        ss_demo.Input_data(scan);
        ss_demo.shell_sort();
        ss_demo.Output_data();
        scan.close();
    }
}   