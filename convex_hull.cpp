#include <bits/stdc++.h>

using namespace std;

using namespace std;

struct point2d {
    long long x, y;
};

struct vector2d {
    long long x, y;

    vector2d(point2d a, point2d b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    long long len(){
        return x * x + y * y;
    }
};

long long cross(vector2d a, vector2d b) {
    return a.x * b.y - b.x * a.y;
}

vector<point2d> get_convex_hull(vector<point2d> points) {
    /* First phase */

    for (int i = 1; i < points.size(); ++i) {
        if (points[i].x < points[0].x
            || (points[i].x == points[0].x && points[i].y < points[0].y))
        {
            swap(points[i], points[0]);
        }
    }

    sort(
            points.begin() + 1,
            points.end(),
            [&points](point2d a, point2d b) {
                auto v1 = vector2d(points[0], a);
                auto v2 = vector2d(points[0], b);
                return cross(v1, v2) > 0 || cross(v1, v2) == 0 && v1.len() < v2.len();
            }
    );

    /* Second phase */

    vector<point2d> ch = {points[0], points[1]};

    for (int i = 2; i < points.size(); ++i) {
        while (ch.size() >= 2
               && cross(
                vector2d(ch[ch.size() - 2], ch[ch.size() - 1]),
                vector2d(ch[ch.size() - 1], points[i])
        ) <= 0)
        {
            ch.pop_back();
        }

        ch.push_back(points[i]);
    }

    return ch;
}
long double PI = 3.1415926535;

long double dot(vector2d a, vector2d b){
    return a.x * b.x + a.y * b.y;
}

long double len(vector2d a){
    long double k = (long double)(a.x * a.x + a.y * a.y);
    return sqrt(k);
}

long double angle(point2d a, point2d b, point2d c){
    auto v1 = vector2d(b,  a);
    auto v2 =vector2d(b, c);
    //    cout.precision(9);
    long double dt = (long double)dot(v1, v2);
    long double al = (long double)(len(v1) * len(v2));
    long double f = acos( dt / al) * 180.0 / PI;
    //cout << cross(v1, v2) << endl;
    //cout << fixed << acos(dot(v1, v2) / (len(v1) * len(v2))) * 180 / PI << endl;
    return f;
}

long long sq (const vector<point2d> & fig)
{
    long long res = 0;
    for (unsigned i=0; i<fig.size(); i++)
    {
        point2d
            p1 = i ? fig[i-1] : fig.back(),
            p2 = fig[i];
        res += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return abs (res); // /2
}

int main() {

    //freopen("in", "r", stdin);
    int n;
    cin >> n;
    vector<point2d> points(n);

    for (auto& pt : points) {
        cin >> pt.x >> pt.y;
    }

    auto ch = get_convex_hull(points);

    return 0;
}
