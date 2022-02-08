/*
Problem: https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/

Solution: using a stack

Complexity:
	Time: O(n)
	Space: O(n), where n is the size of input tokens of reverse polish expression.
*/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        // the stack to store uncalculated operands
        stack<int> operands;
        int size = tokens.size();
        for (int i = 0; i < size; ++i) {
            string token = tokens[i];
            // 1. token is an operand
            if (!isOperator(token)) {
                operands.push(stoi(token));
            }
            // 2. token is an operator
            else {
                int oprd2 = operands.top();
                operands.pop();
                int oprd1 = operands.top();
                operands.pop();
                int result = calculate(oprd1, oprd2, token);
                operands.push(result);
            }
        }
        return operands.top();
    }

private:
    // we make sure that op is a valid operator
    int calculate(int a, int b, string op) {
        switch (op[0]) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return -1;
        }
    }

    bool isOperator(string op) {
        if (op.size() == 1 && (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/')) {
            return true;
        } else {
            return false;
        }
    }
};
