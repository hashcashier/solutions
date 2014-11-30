//ASC24E
#include <iostream>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

class graph {
    public:
    vector<int> adj;

    graph(int V) {
        adj.assign(V, 0);
    }

    void connect(int a, int b) {
        adj[a] = b;
    }

    vector<int> permutation() {
        vector<int> res = adj;
        for(int i = 0; i < adj.size(); i++)
            res[ adj[i] ] = i;
        return res;
    }
};

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    int n;
    while(cin >> n) {
//        int perm[n];
//        for(int i = 0; i < n; i++)
//            cin >> perm[i];//, cout << perm[i] << ' ';
//        cout << endl;
//
//        for(int i = 0; i < n; i++) {
//            for(int j = 0; j < n; j++)
//                if(perm[j] < i+1)
//                    cout << perm[j] << ' ';
//                else if(perm[j] > i+1)
//                    cout << perm[j]-1 << ' ';
//            cout << endl;
//        }
//        cout << endl;
//        continue;


        vector< vector<int> > subgraphs(n, vector<int>(n-1,0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n - 1; j++)
                cin >> subgraphs[i][j], subgraphs[i][j]--;
        sort(subgraphs.begin(), subgraphs.end());

        set<int> seen;
        for(int i = 0; i < n; i++)
            seen.insert(subgraphs[i][0]), seen.insert(subgraphs[i][0]+1);

        vector<int> trials = vector<int>(seen.begin(), seen.end());
//        assert(trials.size() && trials.size() < 4);

        bool found = false;
        for(int i = 0; !found && i < trials.size(); i++) {
            for(int j = 0; j < n; j++) {
                graph G(n);
                // reconstruct here..

                for(int k = 0; k < n-1; k++) {
//                    cout << subgraphs[j][k] << ' ';
                    if(subgraphs[j][k] < trials[i]) {
                        G.connect(subgraphs[j][k], k+1);
                    } else {// (subgraphs[j][k] >= trials[i]) {
                        G.connect(subgraphs[j][k]+1, k+1);
                    }
                }
                G.connect(trials[i], 0);

                vector<int> perm = G.permutation();
//                cout << "Try: ";
//                for(int i = 0; i < n; i++)
//                    cout << perm[i]+1 << ' ';
//                cout << endl;

                vector< vector<int> > induced(n, vector<int>(n-1,0));
                for(int k = 0; k < n; k++) {
                    int kj = 0;
                    for(int ki = 0; ki < n; ki++)
                        if(perm[ki] < k)
                            induced[k][kj++] = perm[ki];
                        else if(perm[ki] > k)
                            induced[k][kj++] = perm[ki] - 1;

//                    for(int iter = 0; iter < kj; iter++)
//                        cout << induced[k][iter]+1 << ' ';
//                    cout << endl;
                }
                sort(induced.begin(), induced.end());

                if(induced == subgraphs) {
                    found = true;
                    for(int k = 0; k < n; k++) {
                        if(k) cout << ' ';
                        cout << perm[k]+1;
                    }
//                    cout << endl;
                    break;
                }
            }
        }
        assert(found);
    }
    return 0;
}
