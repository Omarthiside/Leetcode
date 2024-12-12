class Solution {
 public:
  long long pickGifts(vector<int>& gifts, int k) {
    while (k > 0) {
        auto maxIt = max_element(gifts.begin(), gifts.end());
        *maxIt = sqrt(*maxIt);
        k--;
    }
    return accumulate(gifts.begin(), gifts.end(), 0LL);
  }
};
