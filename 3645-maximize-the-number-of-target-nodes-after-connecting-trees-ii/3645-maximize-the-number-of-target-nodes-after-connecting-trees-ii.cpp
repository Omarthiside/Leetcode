class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n1 = edges1.size() + 1;
        int n2 = edges2.size() + 1;

        vector<vector<int>> adj1(n1 + 1);
        vector<vector<int>> adj2(n2 + 1);

        for (const auto& edge : edges1) {
            int u = edge[0], v = edge[1];
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }

        for (const auto& edge : edges2) {
            int u = edge[0], v = edge[1];
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }

        // Step-1: Count of even-level nodes in tree 2
        int even_count2 = bfs(0, adj2);
        int odd_count2 = n2 - even_count2;
        int best2 = max(even_count2, odd_count2);

        // Step-2: Run BFS on tree-1, record even-level nodes
        vector<bool> included(n1, false);
        int even_count1 = bfs(0, adj1, &included);

        // Step-3: Construct result
        vector<int> ans(n1);
        for (int i = 0; i < n1; ++i) {
            if (included[i]) {
                ans[i] = even_count1 + best2;
            } else {
                ans[i] = (n1 - even_count1) + best2;
            }
        }

        return ans;
    }

private:
    // BFS helper function
    int bfs(int start, const vector<vector<int>>& adj, vector<bool>* included = nullptr) {
        queue<pair<int, int>> q;
        q.push({start, -1});
        int count = 0;
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            if (level % 2 == 0) {
                count += size;
            }

            for (int i = 0; i < size; ++i) {
                auto [curr, parent] = q.front();
                q.pop();

                if (included && level % 2 == 0) {
                    (*included)[curr] = true;
                }

                for (int v : adj[curr]) {
                    if (v == parent) continue;
                    q.push({v, curr});
                }
            }
            ++level;
        }

        return count;
    }
};