//10020 - Minimal coverage
#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, pair<int, string> > iis;
typedef pair<int, string> is;

int main() {
//    freopen("10020 - Minimal coverage.in", "r", stdin);
    int T;
    cin >> T;
    for(int cse = 0; cse < T; cse++) {
        if(cse) cout << endl << endl;

        vector<iis> segs, sol;
        int nextRight = -1;
        int a,b, maxRight = 0, M;
        string A, B, C;
        cin >> M;
//        while(cin >> a >> b && (fabs(a) > EPS || fabs(b) > EPS)) {
        while(cin >> A >> B && (A != "0" || B != "0")) {
            istringstream ass(A), bss(B);
            ass >> a;
            bss >> b;
//            if(b < a)
//                swap(A, B);
            C = A + " " + B;
            segs.push_back(iis(min(a,b), is(-abs(a-b), C)));
        }
        sort(segs.begin(), segs.end());

        for(int i = 0; i < segs.size(); i++)
            segs[i].second.first = -segs[i].second.first;

        for(int i = 0; i < segs.size() && maxRight < M; i++) {
//            cout << segs[i].first << ' ' << segs[i].first + segs[i].second.first << ' ' << maxRight << endl;
            if(segs[i].first > maxRight) {
                if(nextRight == -1)
                    break;
                sol.push_back(iis(segs[nextRight].first, is(segs[nextRight].first + segs[nextRight].second.first, segs[nextRight].second.second)));
                maxRight += segs[nextRight].second.first + segs[nextRight].first - maxRight ;
                nextRight = -1;
                i--;
            } else if((nextRight == -1 || segs[i].first + segs[i].second.first > segs[nextRight].first + segs[nextRight].second.first) && segs[i].first + segs[i].second.first > maxRight)
                nextRight = i;
//            cout << segs[i].first << ' ' << segs[i].first + segs[i].second << ' ' << maxRight << ' ' << nextRight << endl;
        }

        if(nextRight != -1 && maxRight < M) {
            sol.push_back(iis(segs[nextRight].first, is(segs[nextRight].first + segs[nextRight].second.first, segs[nextRight].second.second)));
            maxRight += segs[nextRight].second.first;
        }
        if(maxRight < M) {
            cout << 0;
        } else {
            vector<iis> soll;
            for(int i = 0; i < sol.size(); i++) {
                istringstream iss(sol[i].second.second);
                long double a,b;
                iss >> a >> b;
                soll.push_back(iis(a, is(b, sol[i].second.second)));
            }
            sort(soll.begin(), soll.end());
            cout << sol.size() << endl;
            for(int i = 0; i < sol.size(); i++) {
                if(i) cout << endl;
                cout << soll[i].second.second;
            }
        }
    }
    return 0;
}
