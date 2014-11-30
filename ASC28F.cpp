//ASC28F
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long LL;

struct bitree {
    vector<LL> tree;

    bitree(int n) {
        tree.assign(n+1, 0);
    }

    int lastOne(int num) {
        return num&(-num);
    }

    void adjust(int i, int v) {
        for(; i < tree.size(); i += lastOne(i))
            tree[i] += v;
    }

    LL rsq(int i) {
        LL sum = 0;
        for(; i; i -= lastOne(i))
            sum += tree[i];
        return sum;
    }
};

int main() {
    freopen("mtf.in", "r", stdin);
//    freopen("mtf.out", "w", stdout);
    int n;
    cin >> n;

    int a[n];
    set<int> rem;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        rem.insert(a[i]);
    }

    int numUnique = 0;
    map<int, int> mem;
    for(set<int>::iterator it = rem.begin(); it != rem.end(); it++)
        mem[*it] = ++numUnique;

    bitree L(numUnique);

    for(int i = 0; i < n; i++) {
        int idx = mem[ a[i] ], b = L.rsq(idx) + idx;
//        cout << i << ' ' << a[i] << ' ' << idx << ' ' << b << endl;
        if(b > 1)
            L.adjust(1, 1), L.adjust(idx, -b), L.adjust(idx+1, b-1);

        if(i) cout << ' ';
        cout << b + idx;
    }


    return 0;
}
