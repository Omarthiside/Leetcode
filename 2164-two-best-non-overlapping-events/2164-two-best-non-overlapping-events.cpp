class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());

        int n = events.size();

        vector<int> future_max(n + 1);

        for (int i = n - 1; i >= 0; --i) {
            future_max[i] = max(future_max[i + 1], events[i][2]);
        }

        int ans = 0;

        for (auto& event : events) {
            int value = event[2];

            int left = 0, right = n;
            while (left < right) {
                int mid = (left + right) / 2;
                if (events[mid][0] > event[1]) { 
                    right = mid; 
                } else {
                    left = mid + 1; 
                }
            }

            if (left < n) {
                value += future_max[left]; 
            }

            ans = max(ans, value);
        }

        return ans;
    }
};
