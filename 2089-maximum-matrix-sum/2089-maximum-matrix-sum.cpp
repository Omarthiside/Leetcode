class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        const int n = matrix.size();
        
        long long Sum = 0;       
        int Count = 0;        
        int minv = INT_MAX;     
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int value = matrix[i][j];
                Sum += abs(value);            
                if (value < 0) {
                    Count++;                  
                }
                minv = min(minv, abs(value)); 
            }
        }
        
        
        if (Count % 2 == 0) {
            return Sum;
        } else {
            
            return Sum - 2LL * minv;
        }
    }
};
        