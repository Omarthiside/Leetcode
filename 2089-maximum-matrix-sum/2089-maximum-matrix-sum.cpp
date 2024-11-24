class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        const int n = matrix.size();
        
        long long totalSum = 0;       
        int negativeCount = 0;        
        int minAbsValue = INT_MAX;     
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int value = matrix[i][j];
                totalSum += abs(value);            
                if (value < 0) {
                    negativeCount++;                  
                }
                minAbsValue = min(minAbsValue, abs(value)); 
            }
        }
        
        
        if (negativeCount % 2 == 0) {
            return totalSum;
        } else {
            
            return totalSum - 2LL * minAbsValue;
        }
    }
};
        