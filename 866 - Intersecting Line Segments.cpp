//866 - Intersecting Line Segments
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int N, res, z;
double sweepX, sweepY;

double eps = 1e-9;

struct seg;

struct point {
    double x,y;
    bool operator<(const point o) const {
        return (o.x-x) > eps || ( fabs(x-o.x) < eps && (o.y-y) > eps );
    }
};

struct event;
set<event> events;
map<int, vector<seg*> > evstor;
int eventIDS;

struct event {
    point p;
    int U, L, C;

    event() {
    }

    event(point position) {
        p = position;
        U = eventIDS++;
        L = eventIDS++;
        C = eventIDS++;
    }

    void addU(seg* s) const {
        evstor[U].push_back(s);
    }

    void addL(seg* s) const {
        evstor[L].push_back(s);
    }

    void addC(seg* s) const {
        evstor[C].push_back(s);
    }

    bool operator<(const event o) const {
        return p < o.p;
    }
};

event currentEvent;

struct seg {
    point a,b;
    int s, ins;

    double f(const double x) const {
        if(vertical()) {
            return a.y;//currentEvent.p.y;
        } else {
            double A = a.y-b.y;
            double B = b.x-a.x;
            double C = A*a.x + B*a.y;

            return (C-A*x)/B;
        }
    }

    bool vertical() const {
        return fabs(a.x-b.x) < eps;
    }

    bool intersect(const seg &o, point &target) const {
        double A1 = a.y-b.y;
        double B1 = b.x-a.x;
        double C1 = A1*b.x + B1*b.y;

        double A2 = o.a.y-o.b.y;
        double B2 = o.b.x-o.a.x;
        double C2 = A2*o.b.x + B2*o.b.y;

        double det = A1*B2 - A2*B1;

        if(det == 0)
            return false;
        else
            target.x = (B2*C1 - B1*C2)/det,
            target.y = (A1*C2 - A2*C1)/det;
        return true;
    }

    bool operator<(const seg &o) const {
        double a = f(currentEvent.p.x), b = o.f(currentEvent.p.x);
        return (b-a) > eps;
    }
};

void addU(seg *s) {
    event ev(s->a);
    set<event>::iterator it = events.find(ev);
    if(it == events.end())
        it = events.insert(ev).first;
    it->addU(s);
}

void addL(seg *s) {
    event ev(s->a);
    set<event>::iterator it = events.find(ev);
    if(it == events.end())
        it = events.insert(ev).first;
    it->addL(s);
}

event getNextEvent(bool er = true) {
    set<event>::iterator it = events.begin();
    event result = *it;
    if(er)
        events.erase(it);
    return result;
}

set<point> xpoints;

void addx(double x) {
    point p;
    p.x = x;
    p.y = 0;
    xpoints.insert(p);
}

double xhigher(double x) {
    point p;
    p.x = x;
    p.y = 0;
    return xpoints.upper_bound(p)->x;
}

double xlower(double x) {
    point p;
    p.x = x;
    p.y = 0;
    return ((xpoints.lower_bound(p))--)->x;
}

seg *segs;
int main() {
    int T;
    cin >> T;
    while(T--) {
        evstor.clear();
        events.clear();
        xpoints.clear();

        cin >> N;
        int res = 0;

        segs = new seg[N];
        for(int i = 0; i < N; i++) {
            point a, b;
            cin >> a.x >> a.y >> b.x >> b.y;

            addx(a.x);
            addx(b.x);

            if(a < b)
                segs[i].a = a, segs[i].b = b;
            else
                segs[i].a = b, segs[i].b = a;

            segs[i].s = i;

            addU(&segs[i]);
            addL(&segs[i]);
        }

        set<seg> normalSegs;
        seg *verticalSeg = NULL;
        int insertid = 0;
        while(!events.empty()) {
            currentEvent = getNextEvent();
            double current = currentEvent.p.x, lower = xlower(current), higher = xhigher(current);

            // get U, L, C
            vector<seg*> &U = evstor[currentEvent.U], &L = evstor[currentEvent.L], &C = evstor[currentEvent.C];

            // Remove L
            currentEvent.p.x = lower;
            for(int i = 0; i < L.size(); i++)
                if(L[i]->vertical())
                    verticalSeg = NULL;
                else
                    normalSegs.erase(*L[i]);

            // Remove C
            if(C.size()) {
                res += C.size() + (verticalSeg != NULL);
                for(int i = 0; i < C.size(); i++)
                    normalSegs.erase(*C[i]);
            }

            // Add U
            currentEvent.p.x = current;
            for(int i = 0; i < U.size(); i++)
                if(U[i]->vertical())
                    verticalSeg = U[i];
                else
                    normalSegs.insert(*U[i]);

            // Add C
            currentEvent.p.x = higher;
            for(int i = 0; i < C.size(); i++)
                if(!C[i]->vertical())
                    normalSegs.insert(*C[i]);

            // Compute new events
            if(U.size() + C.size() == 0) {
                // Just deletions
            } else {
                //
            }
        }

        cout << N + res << endl;
        if(T) cout << endl;
    }
    return 0;
}
