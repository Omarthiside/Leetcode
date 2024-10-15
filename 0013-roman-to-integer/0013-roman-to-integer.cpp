class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        unordered_map<char,int> symbol = 
        {
            {'I',1}, {'V',5}, {'X',10}, {'L',50}, {'C',100}, {'D',500}, {'M',1000}
        };
        int ans = symbol[s[n - 1]];
        for (int i = n - 2; i >= 0; i--) {
            if (symbol[s[i]] < symbol[s[i + 1]]) {
                ans -= symbol[s[i]];
            } else {
                ans += symbol[s[i]];
            }
        }
        return ans;
    }
};
