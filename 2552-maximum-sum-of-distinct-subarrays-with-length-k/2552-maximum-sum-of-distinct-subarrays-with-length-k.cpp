class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        const int n = nums.size();
        long long result = 0;
        long long currWindow = 0;
        unordered_set<int> st;
        int i=0;
        int j=0;
        while(j<n){
            while(st.count(nums[j])){
                currWindow-=nums[i];
                st.erase(nums[i]);
                i++;
            }
            currWindow+=nums[j];
            st.insert(nums[j]);
            
            if(j-i+1 == k){
                result = max(result, currWindow);
                currWindow-=nums[i];
                st.erase(nums[i]);
                i++;
            }
            j++;
        }
        return result;
    }
};
