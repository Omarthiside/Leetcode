
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> seen;
        
        int maxSum = 0;
        int currentSum = 0;
        int left = 0; 

        for (int right = 0; right < n; ++right) {
            while (seen.count(nums[right])) {
                seen.erase(nums[left]);
                currentSum -= nums[left];
                left++;
            }
            
            currentSum += nums[right];
            seen.insert(nums[right]);
            
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
};