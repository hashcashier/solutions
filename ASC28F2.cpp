//ASC28F
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long LL;

struct bitree {
    vector<LL> tree;

    bitree(){}
    bitree(int n) {
        tree.assign(n+10, 0);
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

LL n, a[200020], prev[200020], f[200020];

int main() {
    freopen("mtf.in", "r", stdin);
    freopen("mtf.out", "w", stdout);

    set<LL> unq;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i], unq.insert(a[i]);
    unq.insert(1);

    for(int i = n + unq.size() - 1; i >= unq.size(); i--)
        a[i] = a[ i - unq.size() ];
    int idx = unq.size()-1;
    for(set<LL>::iterator it = unq.begin(); it != unq.end(); it++)
        a[idx--] = *it;
    n += unq.size();

    memset(prev, -1, sizeof prev);
    map<LL, int> mem;
    for(int i = 0; i < n; i++) {
        if(mem.count(a[i]))
            prev[i] = mem[ a[i] ];
        mem[ a[i] ] = i;
    }

    bitree tree(n);
    for(int i = 0; i < n; i++) {
        if(i && prev[i] == -1)
            tree.adjust(i+1, a[i-1]-a[i]),
            f[i] = tree.rsq(i+1);
        else if(prev[i] != -1)
            tree.adjust( prev[i]+1 , -1),
            tree.adjust( i+1, 1),
            f[i] = tree.rsq(i+1) - tree.rsq(prev[i]+1);
//        cout << i << ' ' << tree.rsq(i+1) << endl;
    }


    for(int i = unq.size(); i < n; i++) {
        if(i > unq.size()) cout << ' ';
        cout << f[i];
    }
    cout << endl;
    return 0;
}
