class Solution {
public:
    // Binary search the index of the first element that is >= target
    // We make sure that tail is rigidly ascending and target <= maximum element in tail
    int findFirstGreaterOrEqual(int target, int len, vector<int> tail) {
        int left = 0;
        int right = len - 1;
        int mid;
        while (left <= right) {
            mid = (left + right + 1)/2;
            if (tail[mid] > target ) {
                right = mid - 1;
            } else if (tail[mid] < target) {
                left = mid + 1;
            } else {
                break;
            }
        }
        
        if (tail[mid] < target) {
            mid++;
        }
        return mid;
    }

    int lengthOfLIS(vector<int>& nums) {
        // dp[i] stores the max length of subsequence in nums[0,...,i]
        vector<int> dp;
        // tail[j] stores the max element in a subsequence whose length is j + 1
        vector<int> tail;

        // init
        int size = nums.size();
        dp.resize(size);
        tail.resize(size);

        // dynamic programming
        dp[0] = 1;
        tail[0] = nums[0];
        for (int i = 1; i < size; ++i) {
            int last_len = dp[i-1];
            if (nums[i] > tail[last_len-1]) {
                dp[i] = last_len + 1;
                tail[last_len] = nums[i]; 
            } else {
                int pos = findFirstGreaterOrEqual(nums[i], last_len, tail);
                dp[i] = last_len;
                tail[pos] = nums[i];
            }
        }
        return dp[size-1];
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> nums = {3,5,6,2,5,4,19,5,6,7,12};
        
        int ret = Solution().lengthOfLIS(nums);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
