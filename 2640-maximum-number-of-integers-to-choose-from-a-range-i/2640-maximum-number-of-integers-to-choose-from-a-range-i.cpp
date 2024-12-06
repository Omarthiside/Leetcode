class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        unordered_set<int> bannedSet(banned.begin(), banned.end());
        int sum = 0, count = 0;

        for (int i = 1; i <= n; ++i) {
            if (bannedSet.find(i) == bannedSet.end() && sum + i <= maxSum) {
                sum += i;
                ++count;
            }
        }
        
        return count;
    }
};
