#include <iostream>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

map<string, map<string, set<string> > > f, g;

string name(int msk) {
    string res = "";
    if((msk&3) == 3)
        res = "AB";
    else if((msk&1))
        res = "A";
    else if(msk&2)
        res = "B";
    else if(msk&4)
        res = "O";
//    else
//        cout << "lame blood" << endl;

    if(msk&8)
        res += "+";
    else if(msk&(16))
        res += "-";
//    else
//        cout << "lame rh" << endl;
    return res;
}
set<string> test;

string dbg(int msk) {
    string res = "";
    for(int i = 0; i < 5; i++)
        if((1<<i)&msk)
            res = "1" + res;
        else
            res = "0" + res;
    return res;
}

void precomp() {
    for(int r1 = 1; r1 < 4; r1++)
        for(int a1 = 1; a1 < 7; a1++) {
            int P1 = (r1<<3) | a1;
            string name1 = name(P1);
            for(int r2 = 1; r2 < 4; r2++)
                for(int a2 = 1; a2 < 7; a2++) {
                    int P2 = (r2<<3) | a2;
                    string name2 = name(P2);
                    for(int i1 = 1; i1 < 3; i1 <<= 1) {
                        if((i1&r1) == 0) continue;
                        for(int j1 = 1; j1 < 6; j1 <<= 1) {
                            if((j1&a1) == 0) continue;
                            for(int i2 = 1; i2 < 3; i2 <<= 1) {
                                if((i2&r2) == 0) continue;
                                for(int j2 = 1; j2 < 6; j2 <<= 1) {
                                    if((j2&a2) == 0) continue;
                                    int P3 = ((i1|i2)<<3) | (j1|j2);
                                    string name3 = name(P3);
//                                    cout << dbg(P1) << ' ' << dbg(P2) << ' ' << dbg(P3) << ' ' << name1 << ' ' << name2 << ' ' << name3 << endl;
//                                    test.insert(name1 + " " + name2 + " " + name3);
//                                    test.insert(name2 + " " + name1 + " " + name3);
                                    f[ name1 ][ name2 ].insert(name3);
                                    f[ name2 ][ name1 ].insert(name3);

                                    g[ name1 ][ name3 ].insert(name2);
                                    g[ name2 ][ name3 ].insert(name1);
                                }
                            }
                        }
                    }
                }
        }
//        cout << test.size() << endl;
//        for(set<string>::iterator it = test.begin(); it != test.end(); it++)
//            cout << *it << endl;
}

void printset(set<string> &st) {
    if(st.empty())
        cout << "IMPOSSIBLE";
    else if(st.size() == 1)
        cout << *(st.begin());
    else {
        cout << '{';
        for(set<string>::iterator it = st.begin(); it != st.end(); it++)
            if(it != st.begin())
                cout << ", " << *it;
            else
                cout << *it;
        cout << '}';
    }
}

int main() {
    freopen("blood.in", "r", stdin);
//    freopen("blood3.out", "w", stdout);
    precomp();
    string A, B, C;
    int cse = 1;
    while(cin >> A >> B >> C) {
        if(A == "E")
            break;
        cout << "Case " << cse++ << ": ";
        if(A == "?") {
            printset(g[B][C]);
            cout << ' ' << B << ' ' << C << endl;
        } else if(B == "?") {
            cout << A << ' ';
            printset(g[A][C]);
            cout << ' ' << C << endl;
        } else if(C == "?") {
            cout << A << ' ' << B << ' ';
            printset(f[A][B]);
            cout << endl;
        } else {
            cout << A << ' ' << B << ' ' << C << endl;
        }
    }

    return 0;
}
