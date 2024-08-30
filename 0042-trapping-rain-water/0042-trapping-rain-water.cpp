#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int w = 0; // total water trapped

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left]; 
                } else {
                    w += left_max - height[left]; 
                }
                left++;
            } else {
                if (height[right] >= right_max) {
                    right_max = height[right]; 
                } else {
                    w += right_max - height[right]; 
                }
                right--;
            }
        }

        return w;
    }
};
