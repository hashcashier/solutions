//ASC25H
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#define EPS 1e-9

using namespace std;

vector< vector<long double> > tutte;
vector< vector<bool> > adj;

bool nonZeroDet(vector< vector<long double> > mat) {
    // Gaussian elimination like a boss
    int n = mat.size();
    for(int j = 0; j < n; j++) {
        int row = j;

        for(int i = j+1; i < n; i++)
            if(abs(mat[i][j]) > abs(mat[row][j]))
                row = i;

        swap(mat[j], mat[row]);

        if(fabs(mat[j][j]) < EPS)
            return false;

        for(int i = j+1; i < n; i++)
            for(int k = n-1; k >= j; k--)
                mat[i][k] -= mat[j][k] * mat[i][j] / mat[j][j];
    }

    return true;
}

int main() {
    freopen("perfect.in", "r", stdin);
    freopen("perfect.out", "w", stdout);
    int n;
//    while(cin >> n) {
        cin >> n;
        tutte.assign(n, vector<long double>(n, 0));
        adj.assign(n, vector<bool>(n, false));

        for(int i = 0; i < n; i++) {
            int num;
            cin >> num;
            for(int j = 0; j < num; j++) {
                int k;
                cin >> k;
                adj[i][k-1] = true;
            }
        }

        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(adj[i][j] && adj[j][i])
                    tutte[j][i] = -(tutte[i][j] = max(1, rand()));

        cout << (nonZeroDet(tutte) ? "YES" : "NO") << endl;
//    }

    return 0;
}
