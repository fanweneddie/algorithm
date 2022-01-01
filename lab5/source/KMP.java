import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Vector;

// implement KMP algorithm
public class KMP
{
    private int num;
    private Vector<char[]> patterns;
    private Vector<char[]> texts;
    private Vector<Integer> ans;
    
    KMP()
    {
        num = 0;
    }
    
    // input the data for sorting
    public void Input_data() throws IOException
    {
        // input num, init texts and patterns
        BufferedReader buffer = new BufferedReader(
            new InputStreamReader(System.in));
        num = Integer.parseInt(buffer.readLine());
        texts = new Vector<char[]>(num);
        patterns = new Vector<char[]>(num);
        ans = new Vector<Integer>(num);

        String start = "s";
        char[] temp;
        // input texts and patterns
        for(int i = 0; i < num;++i)
        {   
            temp = (start + buffer.readLine()).toCharArray();
            patterns.add(i,temp);
            temp = (start + buffer.readLine()).toCharArray();
            texts.add(i,temp);
        }
    }
    
    // output the answer
    public void Output_data()
    {
        for(int i = 0;i < num;++i)
        {
            System.out.println(ans.get(i));
        }
    }

    // do the pattern match by implementing KMP
    public void Matcher()
    {
        for(int i = 0;i < num;++i)
        {
            char [] text = texts.get(i);
            char [] pattern = patterns.get(i);
            int t_len = text.length;
            int p_len = pattern.length;
            // total number of matches in each case
            int total = 0;
            // get prefix function
            int [] prefix = prefix_func(i);
            // ptr in pattern
            int q = 0;
            // check in text
            for(int j = 1; j < t_len;++j)
            {
                while( q > 0 && pattern[q+1] != text[j] )
                    q = prefix[q];
                if( pattern[q+1] == text[j] )
                    q++;
                if(q == p_len - 1)
                {
                    total++;
                    q = prefix[q];
                }
            }
            ans.add(i,total);
        }
    }

    // get the prefix function for a pattern
    public int[] prefix_func(int index)
    {
        char [] pattern = patterns.get(index);
        int len = pattern.length;
        int [] prefix = new int[len];
        prefix[1] = 0;
        // ptr in pattern
        int k = 0;
        // get prefix[q] for each position
        for(int q = 2; q < len;++q)
        {
            while( k > 0 && pattern[k+1] != pattern[q] )
                k = prefix[k];
            if( pattern[k+1] == pattern[q] )
                k++;
            prefix[q] = k;
        }
        return prefix;
    }

    public static void main(String args[]) throws IOException
    {
        KMP kmp_demo = new KMP();
        kmp_demo.Input_data();
        kmp_demo.Matcher();
        kmp_demo.Output_data();
    }
}

/*
1
cad
cacadcab

1
ababaca
abababaca
*/
