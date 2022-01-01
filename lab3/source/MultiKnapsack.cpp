#include <iostream>
#include <vector>
using namespace std;

/*
input:
3 3
1 1 1
2 3 1
3 2 1
output:
4
*/

int max(int a,int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int main()
{
    int item_num,capacity;
    int weight,value,num;
    vector<int> weights;
    vector<int> values;
    vector<int> sum;

    cin >> item_num >> capacity;
    for(int i = 0;i < item_num;++i)
    {
        cin >> weight >> value >> num;
        int temp_num = 1;
        while(temp_num <= num)
        {
            weights.push_back(temp_num*weight);
            values.push_back(temp_num*value);
            num -= temp_num;
            temp_num *= 2; 
        }
        if(num != 0)
        {
            weights.push_back(num*weight);
            values.push_back(num*value);
        }
    }
    /*
    cout << "weights:\n";
    for(int i = 0; i < weights.size();++i)
        cout << weights[i] << " ";
    cout << "\nvalues:\n";
    for(int i = 0; i < values.size();++i)
        cout << values[i] << " ";
    cout << "\n";
    */
    // init sum[j] as 0
    for(int i = 0;i <= capacity;++i)
        sum.push_back(0);

    int new_item_num = weights.size();
    for(int i = 0;i < new_item_num;++i)
    {
        for(int j = capacity;j >= 0;--j)
        {
            if(j >= weights[i])
            {
                sum[j] = max(sum[j],
                    sum[ j - weights[i] ] + values[i] );
            }
        }
    }

    cout << sum[capacity] << endl;  
    return 0;
}
