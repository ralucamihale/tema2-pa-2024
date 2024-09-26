#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, vector<int>> g1;
unordered_map<int, vector<int>> g2;
unordered_map<int, vector<int>> g;

int main() {
    ifstream fin("numarare.in");
    ofstream fout("numarare.out");

    int N, M;
    fin >> N >> M;

    int x, y;

    for (int i = 0; i < M; i++) {
        fin >> x >> y;
        g1[x].push_back(y);
    }

    for (int i = 0; i < M; i++) {
        fin >> x >> y;
        g2[x].push_back(y);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < g1[i].size(); j++) {
            for (int k = 0; k < g2[i].size(); k++) {
                if (g1[i][j] == g2[i][k]) {
                    g[i].push_back(g1[i][j]);
                }
            }
        }
    }

    long long drumuri[100000] = {0};
    drumuri[N] = 1;
    for (int i = N - 1; i >= 1; i--) {
        for (int j = 0; j < g[i].size(); j++) {
                drumuri[i] = (drumuri[i] + drumuri[g[i][j]]) % 1000000007;
        }
    }

    fout << drumuri[1];

    return 0;
}
