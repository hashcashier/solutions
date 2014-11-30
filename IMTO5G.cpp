#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int messageSize[2000], messageNum[2000], startByte[2000], endByte[2000], nxt[2000], order[2000];

int main() {
    int N, M, cse = 1;
    freopen("network.in", "r", stdin);
    while(cin >> N >> M && N) {
        int res = 64000*M;

        for(int i = 0; i < N; i++)
            cin >> messageSize[i];
        for(int i = 0; i < M; i++)
            cin >> messageNum[i] >> startByte[i] >> endByte[i], messageNum[i]--;

        for(int i = 0; i <= N; i++)
            order[i] = i;

        do {
//            cout << "------------------" << endl;
//            for(int i = 0; i < N; i++)
//                cout << order[i] << ' ';
//            cout << endl;
            for(int i = 0; i < N; i++)
                nxt[i] = 1;

            int tres = 0, cursize = 0, j = 0, target = order[j];
            priority_queue< pair<int, int> > test[N];
            for(int i = 0; i < M; i++) {
                int mnum = messageNum[i], psize = endByte[i] - startByte[i] + 1;

                if(mnum == target && nxt[ mnum ] == startByte[i]) {
                    nxt[mnum] = endByte[i]+1;
                } else {
                    test[ mnum ].push( pair<int,int>(-startByte[i], endByte[i]) );
                    cursize += psize;
                    tres = max(tres, cursize);
                }

//                if(target < N && test[target].size())
//                    cout << i << ' ' << target << ' ' << test[target].size() << ' ' << -test[target].top().first << endl;
//                else
//                    cout << i << ' ' << target << endl;

                while(target < N) {
                    if(!test[target].empty() && test[target].top().first == -nxt[target]) {
                        pair<int, int> top = test[target].top();
                        test[target].pop();

                        cursize -= top.second + top.first +1;
                        nxt[target] = top.second + 1;
                    } else if(nxt[target] >= messageSize[target])
                        target = order[++j];
                    else
                        break;
                }
            }
//            cout << target << endl;
//            for(int i = 0; i < N; i++)
//                cout << test[i].size() << ' ';
//            cout << endl;
            for(int i = 0; i < N; i++)
                assert(test[i].empty());
//                cout << test[i].empty() << ' ';

//            for(int k = 0; k < N; k++)
//                cout << order[k] << ' ' ;
//            cout << '/' << tres << endl;
            res = min(res, tres);
        } while (next_permutation(order, order+N));

        cout << "Case " << cse++ << ": "<< res << endl << endl;
    }
}
