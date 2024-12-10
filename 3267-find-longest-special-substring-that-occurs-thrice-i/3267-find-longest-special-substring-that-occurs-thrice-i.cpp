class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();
        int maxLength = -1;

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            vector<int> indices; 
            
            for (int i = 0; i < n; ++i) {
                if (s[i] == ch) {
                    indices.push_back(i);
                }
            }

            int occurrences = indices.size();
            if (occurrences < 3) {
                continue;
            }

            for (int len = 1; len <= n; ++len) {
                int count = 0;
                for (int i = 0; i < occurrences - len + 1; ++i) {
                    if (indices[i + len - 1] - indices[i] + 1 <= len) {
                        count++;
                    }
                }
                if (count >= 3) {
                    maxLength = max(maxLength, len);
                }
            }
        }

        return maxLength == -1 ? -1 : maxLength;
    }
};