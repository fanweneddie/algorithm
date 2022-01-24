/*
Problem: https://leetcode-cn.com/problems/product-of-the-last-k-numbers/

Solution: Use an array to calculate prefix production.
If a newly added element = 0, then clear the array
When getting products, if k > size of array, return 0.
Else, return prod[size-1]/prod[size-1-k].

Complexity:
Time: O(1)
Space: O(n), where n is the number of overall elements.
*/
class ProductOfNumbers {
public:
    // product of prefix
    vector<int> prod;

    ProductOfNumbers() {
    }
    
    void add(int num) {
        // clear prefix product when encountering 0
        if (num == 0) {
            prod.clear();
        } else {
            if (prod.empty()) {
                prod.push_back(num);
            } else {
                int size = prod.size();
                prod.push_back(prod[size-1] * num);
            }
        }
    }
    
    int getProduct(int k) {
        int size = prod.size();
        if (size < k) {
            return 0;
        } else if (size > k) {
            return prod[size-1]/prod[size-1-k];
        } else {
            return prod[size-1];
        }
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
