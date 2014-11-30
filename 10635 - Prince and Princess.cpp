//10635 - Prince and Princess
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef pair<int, int> ii;

int LIS(vector<int> &seq) {
    multiset<int> lis;
    for(int i = 0; i < seq.size(); i++) {
        multiset<int>::iterator it = lis.upper_bound(seq[i]);
        if(it != lis.end())
            lis.erase(it--);
        lis.insert(it, seq[i]);
    }
    return lis.size();
}

int main() {
    int T;
    cin >> T;
    for(int cse = 1; cse <= T; cse++) {
        cout << "Case " << cse << ": ";
        int n, p, q;
        cin >> n >> p >> q;
        int A[p];
        set<int> AS;
        map<int, int> pos;
        for(int i = 0; i <= p; i++)
            cin >> A[i], pos[ A[i] ] = i;

        vector< int > seq;
        for(int i = 0; i <= q; i++) {
            int b;
            cin >> b;
            if(pos.count(b))
                seq.push_back( pos[b] );
        }

        cout << LIS(seq) << endl;
    }

    return 0;
}
