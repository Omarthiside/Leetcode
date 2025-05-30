struct IndexedQuery {
  int queryIndex;
  int a;  // Alice's index
  int b;  // Bob's index
};

class Solution {
 public:
  // Similar to 2736. Maximum Sum Queries
  vector<int> leftmostBuildingQueries(vector<int>& heights,
                                      vector<vector<int>>& queries) {
    vector<int> ans(queries.size(), -1);
    // Store indices (heightsIndex) of heights with heights[heightsIndex] in
    // descending order.
    vector<int> stack;

    // Iterate through queries and heights simultaneously.
    int heightsIndex = heights.size() - 1;
    for (const auto& [queryIndex, a, b] : getIndexedQueries(queries)) {
      if (a == b || heights[a] < heights[b]) {
        ans[queryIndex] = b;
      } else {
        while (heightsIndex > b) {
          while (!stack.empty() &&
                 heights[stack.back()] <= heights[heightsIndex])
            stack.pop_back();
          stack.push_back(heightsIndex--);
        }
        if (const auto it = upper_bound(
                stack.rbegin(), stack.rend(), a,
                [&](int a, int b) { return heights[a] < heights[b]; });
            it != stack.rend())
          ans[queryIndex] = *it;
      }
    }

    return ans;
  }

 private:
  vector<IndexedQuery> getIndexedQueries(const vector<vector<int>>& queries) {
    vector<IndexedQuery> indexedQueries;
    for (int i = 0; i < queries.size(); ++i) {
      const int a = min(queries[i][0], queries[i][1]);
      const int b = max(queries[i][0], queries[i][1]);
      indexedQueries.push_back({i, a, b});
    }
    ranges::sort(
        indexedQueries,
        [](const IndexedQuery& a, const IndexedQuery& b) { return a.b > b.b; });
    return indexedQueries;
  }
};