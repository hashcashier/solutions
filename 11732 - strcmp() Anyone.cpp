//11732 - strcmp() Anyone
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

vector<string> str;
int N;

LL F(int lo, int hi, int pos) {
    if(hi <= lo)
        return 0;
    LL a = 1, b, i = lo + 1, res;
    if(pos == str[lo].length()) {
        for(; i <= hi; i++)
            if(pos != str[i].length())
                break;
            else
                a++;
        b = hi - i + 1;
        res = (a*(a-1)) + a*b + F(i, hi, pos);
    } else {
        for(; i <= hi; i++)
            if(pos < str[i].length() && str[i][pos] == str[lo][pos])
                a++;
            else
                break;
        b = hi - i + 1;
        res = (a*(a-1)) + a*b + F(lo, i-1, pos+1) + F(i, hi, pos);
    }

//    cout << lo << ' ' << hi << ' ' << pos << endl;
//    cout << ">" << a << ' ' << b << ' ' << i << ' ' << res << endl;
    return res;
}

int main() {
//    freopen("11732 - strcmp() Anyone.in", "r", stdin);
    int N, cse = 1;
    while(cin >> N && N) {
        str = vector<string>(N);
        for(int i = 0; i < N; i++)
            cin >> str[i];
        sort(str.begin(), str.end());
        cout << "Case " << cse++ << ": " << F(0, N-1, 0) << endl;
        continue;
        int res = 0;
        for(int i = 0; i < N; i++)
            for(int j = i+1; j < N; j++)
                for(int k = 0; k <= max(str[i].length(), str[j].length()); k++) {
                    if(k == str[i].length() && k == str[j].length()) {
                        res += 2;
                        break;
                    } else
                    if(k >= str[i].length() || k >= str[j].length() || str[i][k] != str[j][k]) {
                        res++;
                        break;
                    } else
                        res+= 2;

                }
        for(int i = 0; i < N; i++)
            cout << str[i] << endl;
        cout << res << endl;
    }
    return 0;
}
