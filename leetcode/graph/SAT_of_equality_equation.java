/*
Problem: https://leetcode-cn.com/problems/satisfiability-of-equality-equations/

Solution: Union set (since == has transivity).
We build the union set to try to satisfy the constraint in the first traversal.
Then, we check the validity of constraint in the second traversal.

Complexity:
	Time: O(n + clgc)
	Space: O(c), where n is the number of equations and c is the number of variables(<=26)
*/

class Solution {
    public boolean equationsPossible(String[] equations) {
        // Init the union set, whose number of node is the maximum number of variable.
        UnionSet us = new UnionSet(26);
        // Doing union in the first traversal
        for (String equation : equations) {
            char lhs = equation.charAt(0);
            char rhs = equation.charAt(3);
            if (isEqual(equation)) {
                us.union(lhs - 'a', rhs - 'a');
            }
        }
        // Checking correctness in the second traversal
        for (String equation : equations) {
            char lhs = equation.charAt(0);
            char rhs = equation.charAt(3);
            if (isEqual(equation)) {
                if (!us.isConnective(lhs - 'a', rhs - 'a')) {
                    return false;
                }
            } else {
                if (us.isConnective(lhs - 'a', rhs - 'a')) {
                    return false;
                }
            }
        }
        return true;
    }

    // Check whether the operator is ==
    public boolean isEqual(String s) {
        return s.charAt(1) == '=';
    }
}

class UnionSet {
    // The representative node of each node
    private int[] roots;
    
    public UnionSet(int size) {
        roots = new int [size];
        for (int i = 0; i < size; ++i) {
            roots[i] = i;
        }
    }

    // Find the final root of node i
    private int findRoot(int i) {
        if (roots[i] == i) {
            return i;
        } else {
            return findRoot(roots[i]);
        }
    }

    // Union node i and node j
    // Let j's representative node link to i's
    public void union(int i, int j) {
        roots[findRoot(j)] = findRoot(i);
    }

    // Check whether node i and node j are in the same connective component
    public boolean isConnective(int i, int j) {
        return findRoot(i) == findRoot(j);
    }
}
