class Solution {
public:
    long long minimumSteps(string s) {
        int n = s.size();
        long long m = 0; 
        int l = 0; 
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                m += (i - l);
                l++; 
            }
        }
        return m;
    }
};
