#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
using namespace std;

void topoSort(const string &x, unordered_map<string, vector<string>>& drumuri,
                unordered_map<string, bool>& visited, stack<string>& stack) {
    visited[x] = true;

    if (drumuri.find(x) != drumuri.end()) {
        for (string& i : drumuri.at(x)) {
            if (!visited[i])
                topoSort(i, drumuri, visited, stack);
        }
    }

    stack.push(x);
}

int longestPath(unordered_map<string, vector<string>>& drumuri, string start,
                    string end) {
    unordered_map<string, bool> visited;
    stack<string> Stack;

    for (pair<string, vector<string>> pair : drumuri) {
        if (!visited[pair.first])
            topoSort(pair.first, drumuri, visited, Stack);
    }

    unordered_map<string, int> dist;
    for (pair<string, vector<string>> pair : drumuri) {
        dist[pair.first] = -1;
    }

    dist[start] = 0;

    while (!Stack.empty()) {
        string x = Stack.top();
        Stack.pop();

        if (dist[x] != -1) {
            if (drumuri.find(x) != drumuri.end()) {
                for (string& i : drumuri.at(x)) {
                    if (dist[i] < dist[x] + 1) {
                        dist[i] = dist[x] + 1;
                    }
                }
            }
        }
    }

    return dist[end] + 1;
}

int main() {
    ifstream fin("trenuri.in");
    ofstream fout("trenuri.out");

    char start[256], end[256];
    fin >> start >> end;

    int M;
    fin >> M;

    unordered_map<string, vector<string>> drumuri;

    for (int i = 0; i < M; ++i) {
        char x[256], y[256];
        fin >> x >> y;
        drumuri[x].push_back(y);
    }

    int res = longestPath(drumuri, start, end);
    fout << res;

    return 0;
}
