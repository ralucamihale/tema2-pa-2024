#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <set>

using namespace std;

struct DijkstraResult {
    vector<long long> d;
    vector<long long> p;
};

vector<pair<long long, long long>> g[100005];
vector<pair<long long, long long>> reverse_g[100005];

DijkstraResult dijkstra(long long start, long long nr_nodes,
                        vector<pair<long long, long long>> g[100005]) {
    vector<long long> d(nr_nodes + 1, 1000000000009);
    vector<long long> p(nr_nodes + 1, 0);
    set<pair<long long, long long>> pq;

    d[start] = 0;
    pq.insert({d[start], start});

    while (!pq.empty()) {
        auto top = pq.begin();
        long long dist = top->first;
        long long node = top->second;
        pq.erase(top);

        for (pair<long long, long long>& neighbor : g[node]) {
            long long neigh = neighbor.first;
            long long w = neighbor.second;
            if (d[node] + w < d[neigh]) {
                pq.erase({d[neigh], neigh});
                d[neigh] = d[node] + w;
                p[neigh] = node;
                pq.insert({d[neigh], neigh});
            }
        }
    }

    for (long long i = 1; i <= nr_nodes; i++) {
        if (d[i] == 1000000000009) {
            d[i] = -1;
        }
    }
    DijkstraResult result = {d, p};
    return result;
}

long long compute_min_cost(long long n, long long x, long long y,
                            long long z) {
    vector<long long> distFromX, distFromY, distToZ;
    distToZ = dijkstra(z, n, reverse_g).d;
    distFromX = dijkstra(x, n, g).d;
    distFromY = dijkstra(y, n, g).d;

    long long minCost = 1000000000009;

    for (long long i = 1; i <= n; i++) {
        if (distFromX[i] != -1 && distFromY[i] != -1 && distToZ[i] != -1) {
            long long totalCost = distFromX[i] + distFromY[i] + distToZ[i];
            minCost = min(minCost, totalCost);
        }
    }

    if (minCost == 1000000000009) {
        return -1;
    }
    return minCost;
}

int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");

    long long n, m;
    long long x, y, z;

    fin >> n >> m;
    for (long long i = 1; i <= m; i++) {
        long long a, b, c;
        fin >> a >> b >> c;
        g[a].push_back({b, c});
        reverse_g[b].push_back({a, c});
    }
    fin >> x >> y >> z;

    long long res = compute_min_cost(n, x, y, z);
    fout << res;
    return 0;
}
