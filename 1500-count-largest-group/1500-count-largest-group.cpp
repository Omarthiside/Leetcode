class Solution {
public:
    int countLargestGroup(int n) {
        unordered_map<int,int>mp;
        for(int i=1;i<=n;i++){
            int digit = i;
            int sum=0;
            while(digit!=0){
                sum+=digit%10;
                digit = digit /10;
            }
            mp[sum]++;
        }
        int maxi=INT_MIN;
        for(auto it:mp){
            maxi=max(maxi,it.second);
        }
        int count = 0;
        for (auto it : mp) {
            if (it.second == maxi) {
                count++;
            }
        }

        return count;
    }
};