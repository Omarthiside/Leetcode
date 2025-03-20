#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> parent;
    vector<int> rank;

    int findparent(int u) {
        if (u == parent[u]) {
            return u;
        }
        return parent[u] = findparent(parent[u]);
    }

    // Union by rank
    void unionbyrank(int u, int v) {
        int final_u = findparent(u);
        int final_v = findparent(v);
        if (final_u == final_v) return;

        if (rank[final_u] > rank[final_v]) {
            parent[final_v] = final_u;
        } else if (rank[final_v] > rank[final_u]) {
            parent[final_u] = final_v;
        } else {
            parent[final_u] = final_v;
            rank[final_v]++;
        }
    }

    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        parent.resize(n);
        rank.resize(n, 0);
        vector<unsigned int> componentCost(n, UINT_MAX);

        // Initialize parents
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        // Union nodes to create components
        for (auto it : edges) {
            unionbyrank(it[0], it[1]);
        }

        // Calculate component cost using bitwise AND
        for (auto it : edges) {
            int par = findparent(it[0]);
            componentCost[par] &= it[2];
        }

        vector<int> ans;
        for (auto it : queries) {
            if (findparent(it[0]) != findparent(it[1])) {
                ans.push_back(-1);
            } else {
                ans.push_back(componentCost[findparent(it[0])]);
            }
        }
        return ans;
    }
};