class Solution {
 public:
  long long pickGifts(vector<int>& gifts, int k) {
    while (k > 0) {
        int maxIndex = 0;
        for (int i = 1; i < gifts.size(); i++) {
            if (gifts[i] > gifts[maxIndex]) {
                maxIndex = i;
            }
        }
        gifts[maxIndex] = sqrt(gifts[maxIndex]);
        k--;
    }
    long long totalSum = 0;
    for (int gift : gifts) {
        totalSum += gift;
    }
    return totalSum;
  }
};
