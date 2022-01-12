#include <iostream>
#include <vector>
using namespace std;

const int INF = 99999;

int main() {
    // different values of coin.
    vector<int> coins;
    // size of coins
    int coins_num;
    // the amount of cash to be exchanged
    int amount;
    // dp[i] means the minimum amount of coins needed to exchange for i dollars
    vector<int> dp;

    // input
    cin >> coins_num;
    coins.resize(coins_num);
    for (int i = 0; i < coins_num; ++i) {
        cin >> coins[i];
    }
    cin >> amount;
    dp.resize(amount + 1);

    // dynamic programming
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        dp[i] = INF;
        for (int j = 0; j < coins_num; ++j) {
            if (i - coins[j] >= 0) {
                dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
            }
        }
    }

    int result;
    if (dp[amount] == INF) {
        result = -1;
    } else {
        result = dp[amount];
    }

    cout << result << endl;
    return 0;
}