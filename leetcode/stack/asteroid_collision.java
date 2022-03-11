/*
Problem: https://leetcode-cn.com/problems/asteroid-collision/
*/

class Solution {
    public int[] asteroidCollision(int[] asteroids) {
        int size = asteroids.length;
        // we use a stack to deal with collision
        Stack<Integer> s = new Stack<Integer>();
        s.push(asteroids[0]);
        for (int i = 1; i < size; ++i) {
            int new_ast = asteroids[i];
            s.push(new_ast);
            // checks whether we need to check the collision
            boolean maybe_collision = true;
            while(maybe_collision && s.size() > 1) {
                new_ast = s.pop();
                int cur_ast = s.pop();
                maybe_collision = false;
                // 1. collision
                if (cur_ast > 0 && new_ast < 0) {
                    // 1.1 cur_ast is smaller, so we disgard it and push new_ast
                    // we will keep checking collision later
                    if (cur_ast + new_ast < 0) {
                        s.push(new_ast);
                        maybe_collision = true;
                    } 
                    // 1.2 cur_ast is bigger, so we disgard new_ast
                    // and we don't need to check collision again
                    else if (cur_ast + new_ast > 0) {
                        s.push(cur_ast);
                    }
                    // 1.3 cur_ast is as big as new_ast, so we disgard them both
                }
                // 2. no collision
                else {
                    s.push(cur_ast);
                    s.push(new_ast);
                }
            }
        }
        // get the result remaining in stack
        int remain_size = s.size();
        Integer[] temp = new Integer[remain_size];
        int[] ans = new int[remain_size];
        temp = s.toArray(temp);
        for (int i = 0; i < remain_size;++i) {
            ans[i] = temp[i];
        }
        return ans;
    }
}
