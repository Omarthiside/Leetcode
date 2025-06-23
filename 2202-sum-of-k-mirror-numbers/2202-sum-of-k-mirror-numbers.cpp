class Solution {
    long getPalindrome(int half, bool odd) {
        long pal = half;
        if (odd) half /= 10;
        for (; half; half /= 10) pal = pal * 10 + half % 10;
        return pal;
    }
    bool isPalindromeBaseK(long n, int k) {
        long mul = 1;
        while (mul * k <= n) mul *= k;
        for (; n; mul /= k * k) {
            if (n / mul != n % k) return false;
            n = (n - (n / mul) * mul - n % k) / k;
        }
        return true;
    }
public:
    long long kMirror(int k, int n) {
        long long ans = 0;
        for (int len = 1; true; ++len) {
            int begin = pow(10, (len - 1) / 2), end = pow(10, (len + 1) / 2);
            for (int half = begin; half < end; ++half) {
                long pal = getPalindrome(half, len % 2);
                if (isPalindromeBaseK(pal, k)) {
                    ans += pal;
                    if (--n == 0) return ans;
                }
            }
        }
    }
};