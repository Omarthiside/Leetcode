struct SegmentTree {
 public:
  explicit SegmentTree(int n)
      : n(n), treeIntervalCounts(4 * n), treeIntervalLengths(4 * n) {}

  void add(int i, int val) {
    add(0, 0, n - 1, i, val);
  }

  int queryIntervalCounts(int i) const {
    return query(treeIntervalCounts, 0, 0, n - 1, i, n - 1);
  }

  int queryIntervalLengths(int i) const {
    return query(treeIntervalLengths, 0, 0, n - 1, i, n - 1);
  }

 private:
  const int n;
  vector<int> treeIntervalCounts;
  vector<int> treeIntervalLengths;

  void add(int treeIndex, int lo, int hi, int i, int val) {
    if (lo == hi) {
      treeIntervalCounts[treeIndex] += val;
      treeIntervalLengths[treeIndex] = treeIntervalCounts[treeIndex] * i;
      return;
    }
    const int mid = (lo + hi) / 2;
    if (i <= mid)
      add(2 * treeIndex + 1, lo, mid, i, val);
    else
      add(2 * treeIndex + 2, mid + 1, hi, i, val);
    treeIntervalCounts[treeIndex] =
        merge(treeIntervalCounts[2 * treeIndex + 1],
              treeIntervalCounts[2 * treeIndex + 2]);
    treeIntervalLengths[treeIndex] =
        merge(treeIntervalLengths[2 * treeIndex + 1],
              treeIntervalLengths[2 * treeIndex + 2]);
  }

  int query(const vector<int>& tree, int treeIndex, int lo, int hi, int i,
            int j) const {
    if (i <= lo && hi <= j)  
      return tree[treeIndex];
    if (j < lo || hi < i) 
      return 0;
    const int mid = (lo + hi) / 2;
    return merge(query(tree, treeIndex * 2 + 1, lo, mid, i, j),
                 query(tree, treeIndex * 2 + 2, mid + 1, hi, i, j));
  }

  int merge(int left, int right) const {
    return left + right;
  }
};

class Solution {
 public:
  vector<int> numberOfAlternatingGroups(vector<int>& colors,
                                        vector<vector<int>>& queries) {
    const int n = colors.size();
    vector<int> ans;
    vector<int> arr{colors};
    SegmentTree tree(2 * n - 1);
    set<pair<int, int>> intervals;

    arr.insert(arr.end(), colors.begin(), colors.end());

    int start = 0;
    for (int i = 1; i < 2 * n - 1; ++i)
      if (arr[i] == arr[i - 1]) {
        insert(intervals, {start, i - 1}, tree, n);
        start = i;
      }
    insert(intervals, {start, 2 * n - 2}, tree, n);

    for (const vector<int>& query : queries)
      if (query[0] == 1) {
        const int sz = query[1];
        const pair<int, int>& intervalWithN = findInterval(intervals, n);
        const int numAlternatingGroups =
            getNumAlternatingGroups(sz, intervalWithN, tree, n);
        ans.push_back(numAlternatingGroups);
      } else {
        const int index = query[1];
        const int color = query[2];
        if (arr[index] == color)
          continue;
        update(intervals, index, color, arr, tree, n);
        if (index < n - 1)
          update(intervals, index + n, color, arr, tree, n);
      }

    return ans;
  }

 private:
  int getNumAlternatingGroups(int sz, const pair<int, int>& intervalWithN,
                              const SegmentTree& tree, int n) {
    const int numIntervals = tree.queryIntervalCounts(sz);
    const int sumIntervals = tree.queryIntervalLengths(sz);
    const int numAlternatingGroups =
        sumIntervals - numIntervals * sz + numIntervals;
    const auto& [l, r] = intervalWithN;
    if (l >= n || r - l + 1 < sz)
      return numAlternatingGroups;
    if (r >= n) {  
      const int nonDuplicateGroups = n - l;
      const int numGroups = (r - l + 1) - sz + 1;
      return numAlternatingGroups - max(0, numGroups - nonDuplicateGroups);
    }
    return numAlternatingGroups;
  }

  void insert(set<pair<int, int>>& intervals, const pair<int, int>& interval,
              SegmentTree& tree, int n) {
    intervals.insert(interval);
    if (interval.first < n)
      tree.add(interval.second - interval.first + 1, 1);
  }

  void remove(set<pair<int, int>>& intervals, const pair<int, int>& interval,
              SegmentTree& tree, int n) {
    intervals.erase(interval);
    if (interval.first < n)
      tree.add(interval.second - interval.first + 1, -1);
  }

  pair<int, int> findInterval(const set<pair<int, int>>& intervals,
                              int target) {
    auto it = intervals.upper_bound({target, INT_MAX});
    return (*--it);
  }

  void update(set<pair<int, int>>& intervals, int index, int color,
              vector<int>& arr, SegmentTree& tree, int n) {
    arr[index] = color;

    const pair<int, int> intervalWithIndex = findInterval(intervals, index);
    remove(intervals, intervalWithIndex, tree, n);
    auto [start, end] = intervalWithIndex;

    if (start < index && index < end) {
      insert(intervals, {start, index - 1}, tree, n);
      insert(intervals, {index, index}, tree, n);
      insert(intervals, {index + 1, end}, tree, n);
      return;
    }

    if (start == index && index < end)
      insert(intervals, {start + 1, end}, tree, n);

    if (start < index && index == end)
      insert(intervals, {start, end - 1}, tree, n);

    start = index;
    end = index;
    vector<pair<int, int>> intervalsToRemove;

    auto it = intervals.upper_bound({index, INT_MAX});

    for (auto lit = it; lit != intervals.begin();) {
      --lit;
      if (arr[lit->second] == arr[start]) 
        break;
      intervalsToRemove.push_back(*lit);
      start = lit->first;
    }

    for (auto rit = it; rit != intervals.end(); ++rit) {
      if (arr[rit->first] == arr[end])  
        break;
      intervalsToRemove.push_back(*rit);
      end = rit->second;
    }

    for (const pair<int, int>& interval : intervalsToRemove)
      remove(intervals, interval, tree, n);

    insert(intervals, {start, end}, tree, n);
  }
};