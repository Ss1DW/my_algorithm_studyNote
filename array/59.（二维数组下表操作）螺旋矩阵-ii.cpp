// @before-stub-for-debug-begin
#include <vector>
#include <string>
#include "commoncppproblem59.h"

using namespace std;
// @before-stub-for-debug-end

/*

 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    { /*在进行草稿后 发现，这个旋转矩阵（n = 4）为例，按照 4 33 22 11
         的方式进行转向 即 走四格 转一次，走3 转一 走三 转一 走2 转1 走2转1 走1转1 走1，如果
         n=5 则是5 44 33 22 11，转向按照右下左上 的规律，由此得到此题解法
         */
        vector<vector<int>> nums(n, vector<int>(n, 0));
        int i = 0;
        int j = n - 1;
        int num = n + 1;
        int nn = n - 1;
        for (int i0 = 0; i0 < n; i0++)
        {
            nums[0][i0] = i0 + 1;
        }
        while (nn > 0)
        {
            for (int i1 = 0; i1 < nn; i1++)
            { // 横下
                nums[++i][j] = num;
                num++;
            }
            for (int m1 = 0; m1 < nn; m1++)
            { // 横左
                nums[i][--j] = num;
                num++;
            }
            nn--;
            for (int n1 = 0; n1 < nn; n1++)
            { // 横上
                nums[--i][j] = num;
                num++;
            }
            for (int b1 = 0; b1 < nn; b1++)
            { // 横右
                nums[i][++j] = num;
                num++;
            }
            nn--;
        }
        return nums;
    }
};
// @lc code=end
