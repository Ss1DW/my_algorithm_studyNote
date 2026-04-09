// @before-stub-for-debug-begin
#include <vector>
#include <string>

using namespace std;
// @before-stub-for-debug-end

/*

 *
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 *
 * 找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr]
 * ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

 * 示例 1：
 *
 *
 * 输入：target = 7, nums = [2,3,1,2,4,3]
 * 输出：2
 * 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

 *
 */

// @lc code=start
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    { /*思路：数组操作1 双指针
         以左右指针构成窗口的左指针作为主要遍历的点，对于每一个左起点，找到符合要求的右终点后
         左起点就向右进一，得到新的左起点。
         */
        int left, right;
        left = 0;
        right = 0;
        int length = nums.size();
        int numSize = nums.size();
        int sum = nums[left];
        int count = 0;
        while (left <= numSize && right < numSize)
        {
            if (sum < target)
            {
                if (right == numSize - 1)
                {
                    break;
                }
                sum += nums[++right];
            }
            else
            {
                length = length > right - left + 1 ? right - left + 1 : length;
                sum -= nums[left++];
                count++;
            }
        }
        return length == numSize && count == 0 ? 0 : length;
    }
};
// @lc code=end
