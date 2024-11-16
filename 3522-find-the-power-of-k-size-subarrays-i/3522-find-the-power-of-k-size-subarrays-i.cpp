class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int>res;
        deque<int>dq;
        for(int i=0;i<n;++i){
            if(!dq.empty() and dq.front()<=i-k){
                dq.pop_front();
            }
            while(!dq.empty() and nums[dq.back()] != nums[i]-1){
                dq.pop_back();
            }
            dq.push_back(i);
            if(i>=k-1){
                if(dq.size()==k){
                    res.push_back(nums[dq.back()]);
                } else {
                    res.push_back(-1);
                }
            }


        }
        return res;
        
    }
};