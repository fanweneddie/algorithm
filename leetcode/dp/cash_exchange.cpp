#include <iostream>
#include <vector>
using namespace std;

/*
 * Problem:
 * Given different values of coins and an amount of money,
 * find the minimum number of coins to exchange that amount of money
 *
 * Solution:
 * We set dp[i] as the minimum number of coins for i dollars
 * dp[0] = 0;
 * dp[i] = min{dp[i-coin]} + 1, where coin is in coins and i-coin >= 0
 * finally, return dp[amount];
 *
 * Complexity:
 * Time: O(n*m)
 * Space: O(m), where n is the size of coins and m is the amount of money
 * (As you can see, m is not a size, but a value. So it is pseudo-polynomial)
 */
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