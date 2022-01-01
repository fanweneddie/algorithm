#include <iostream>
#include <vector>
#include <string>
using namespace std;

// implement KMP algorithm
class KMP
{
    private:
    int num;
    vector<string> patterns;
    vector<string> texts;
    vector<int> ans;
    
    public:
    KMP()
    {
        num = 0;
    }
    
    // input the data for sorting
    void Input_data()
    {
        cin >> num;
        texts.resize(num);
        patterns.resize(num);
        ans.resize(num);

        string start = "s";
        string temp;
        // input texts and patterns
        for(int i = 0; i < num;++i)
        {   
            cin >> temp;
            temp = start + temp;
            patterns[i] = temp;
            cin >> temp;
            temp = start + temp;
            texts[i] = temp;
        }
    }
    
    // output the answer
    void Output_data()
    {
        for(int i = 0;i < num;++i)
        {
           cout << ans[i] << endl;
        }
    }

    // do the pattern match by implementing KMP
    void Matcher()
    {
        for(int i = 0;i < num;++i)
        {
            string text = texts[i];
            string pattern = patterns[i];
            int t_len = text.size();
            int p_len = pattern.size();
            // total number of matches in each case
            int total = 0;
            // get prefix function
            vector<int> prefix = prefix_func(i);
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
            ans[i] = total;
        }
    }

    // get the prefix function for a pattern
    vector<int> prefix_func(int index)
    {
        string pattern = patterns[index];
        int len = pattern.size();
        // the prefix to be returned
        vector<int> prefix;
        prefix.resize(len);
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
};

int main()
{
    KMP kmp_demo = KMP();
    kmp_demo.Input_data();
    kmp_demo.Matcher();
    kmp_demo.Output_data();
    return 0;
}

/*
1
cad
cacadcab

1
ababaca
abababaca
*/
