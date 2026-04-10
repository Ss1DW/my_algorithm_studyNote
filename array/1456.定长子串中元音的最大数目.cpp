/*
 * @lc app=leetcode.cn id=1456 lang=cpp
 *
 * [1456] 定长子串中元音的最大数目

 * 给你字符串 s 和整数 k 。
 *
 * 请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。
 *
 * 英文中的 元音字母 为（a, e, i, o, u）。

 * 示例 1：
 * 输入：s = "abciiidef", k = 3
 * 输出：3
 * 解释：子字符串 "iii" 包含 3 个元音字母。
 *
 *
 * 示例 2：
 *
 * 输入：s = "aeiou", k = 2
 * 输出：2
 * 解释：任意长度为 2 的子字符串都包含 2 个元音字母。

 */

// @lc code=start
#include <string>
class Solution
{
public:
    int maxVowels(std::string s, int k)
    {
        std::string alphO = std::string("aeiou");
        int left = 0;
        int right = k - 1; // 为了结构简单 选择第一遍遍历单独拿出来进行
        int sum = 0;
        int ans = 0;
        if (s.length() == 1) // 特殊情况，s只有一个字符
        {
            if (alphO.find(s[0]) != std::string::npos)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        for (int i = 0; i < k; i++)
        {
            if (alphO.find(s[i]) != std::string::npos)
            {
                sum++;
                ans = ans > sum ? ans : sum;
            }
        }
        while (right < s.length())
        {
            sum -= alphO.find(s[left++]) != std::string::npos ? 1 : 0;
            sum += alphO.find(s[++right]) != std::string::npos ? 1 : 0; // 操作数组简便写法
            ans = ans > sum ? ans : sum;
        }
        return ans;
    }
};
// @lc code=end
