//ASC14J
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;

int N, f[100100], M;
vector< vector<int> > adjList;
map< vector<ii>, int > mem;

int F(int u) {
    if(f[u]) return f[u];
    map<int, int> signature;
    for(int j = 0; j < adjList[u].size(); j++) {
        int v = adjList[u][j];
        signature[F(v)]++;
    }
    vector<ii> sign = vector<ii>(signature.begin(), signature.end());
//    map< vector<ii>, int >::iterator it = mem.find(sign);
//    int num;
//    if(it == mem.end()) {
//        mem[sign] = mem.size();
//        num = ++M;
//    } else {
//        num = it->second;
//    }
    int num = mem[sign];
    if(!num) {
        num = (++M);
        mem[sign] = num;
    }
    return f[u] = num;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> N;
    adjList.assign(N, vector<int>());
    for(int i = 0; i < N-1; i++) {
        int x;
        cin >> x;
        x--;
        adjList[x].push_back(i+1);
    }
    for(int i = N-1; i >= 0; i--)
        F(i);

    for(int i = 0; i < N; i++) {
        if(i) cout << ' ';
        cout << f[i];
    }
    return 0;
}
