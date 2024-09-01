class Solution {
public:
    int potionCount(vector<int> &potions, long long spell, long long success)
    {
        long long start=0;
        long long end=potions.size()-1;
        long long mid=start+(end-start)/2;
        long long ans=-1;

        while(start<=end)
        {
            mid=start+(end-start)/2;
            if(spell*potions[mid]>=success)
            {
                ans=mid;
                end=mid-1;
            }
            else if(spell*potions[mid]<success)start=mid+1;
        }

        if(ans==-1)return 0;

        return potions.size()-ans;

    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> pairs;
        sort(potions.begin(),potions.end());

        for(auto i:spells)
        {
            int ans=potionCount(potions,i,success);
            pairs.push_back(ans);
        }
        return pairs;
    }
};