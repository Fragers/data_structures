#include <bits/stdc++.h>
using namespace std;
// #define COMMIT
#define ll long long
const ll MAXN = 2e6+5;
const ll INF = 1e9+7;


template <typename T>
class Point{
public:
    T x, y;
    Point(T x, T y, T z = 0){
        this->x = x;
        this->y = y;
    }

    Point(const Point& p){
        x = p.x;
        y = p.y;
    }

    Point(){
        x = 0;
        y = 0;
    }
    // Point operator+(Point & a){
    //     return Point(x + a.x, a.y + y);
    // }
    Point operator+(Point &a);
    Point operator-(Point & a);
    Point operator+=(Point& a);
    Point operator-=(Point& a);
    Point operator*(T c);


    friend istream& operator>>(istream& st, Point& p){
        st >> p.x >> p.y;
        return st;
    }
    friend ostream& operator<<(ostream & st, const Point& p){
        st << p.x << ' ' << p.y;
        return st;
    }

};

template <typename T>
class Vector{
public:
    Point<T> start;
    Point<T> end;
    T x, y, z;

    Vector(){
        start = Point<T>();
        end = Point<T>();
        x = 0;
        y = 0;
        z = 0;
    }

    Vector(Point<T> st, Point<T>en) : start(st), end(en) {
        x = en.x - st.x;
        y = en.y - st.y;
        z = 0;
    }
    Vector(T x, T y, T z) : x(x), y(y), z(z) {};
    Vector(T x, T y) : x(x), y(y), z(0) {};
    
    Vector crossVector(Vector& v2){
        T i = y * v2.z - v2.y * z;
        T j = -(x * v2.z - v2.x * z);
        T k = x * v2.y - v2.x * y;
        return Vector(i, j, k);
    }

    T crossValueSquare(Vector& v2){
        T i = y * v2.z - v2.y * z;
        T j = -(x * v2.z - v2.x * z);
        T k = x * v2.y - v2.x * y;
        return k;
    }

    T dot(Vector& v1){
        return v1.x * this->x + v1.y * this->y;
    }
    friend istream& operator>>(istream& st, Vector& p){
        st >> p.x >> p.y;
        return st;
    }
    friend ostream& operator<<(ostream & st, const Vector& p){
        st << p.x << ' ' << p.y;
        return st;
    }

    Point<T> relPoint(double n, double k){
        return Point((start.x * k + end.x * n) / (n + k), (start.y * k + end.y * n) / (n + k));
    }
    T len(){
        return x * x + y * y;
    }

};

template <typename T>
class Line{
public:
    T a, b, c;
    Line(T a, T b, T c) : a(a), b(b), c(c) {}
    Line() : a(0), b(0), c(0) {}
    Line(Point<T>& st, Point<T>& en){
        T p_a = en.y - st.y;
        T p_b = en.x - st.x;
        a = p_a;
        b = -p_b;
        c = -(a * st.x + b * st.y);
    }
    Vector<T> norm(){
        return Vector<T>(a, b);
    }
    Vector<T> guide(){
        return Vector<T>(-b, a);
    }
    friend istream& operator>>(istream& st, Line& p){
        st >> p.a >> p.b >> p.c;
        return st;
    }
    Point<T> getAnyPoint(){
        T x0, y0, g;
        find_any_solution(a, b, -c, x0, y0, g);
        // cout << a << ' ' << b << ' ' << c << ' ' << x0 << ' ' << y0 << ' ';
        return Point<T>(x0, y0);
    }

    T gcd (T a, T b, T & x, T & y) {
        if (a == 0) {
            x = 0; y = 1;
            return b;
        }
        T x1, y1;
        T d = gcd (b%a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }
 
    bool find_any_solution (T a, T b, T c, T & x0, T & y0, T & g) {
        g = gcd (abs(a), abs(b), x0, y0);
        if (c % g != 0)
            return false;
        x0 *= c / g;
        y0 *= c / g;
        if (a < 0)   x0 *= -1;
        if (b < 0)   y0 *= -1;
        return true;
    }

    double lenToPoint(Point<T> p){
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }

};

template <typename T>
T cross(Vector<T> a, Vector<T> b) {
    return a.x * b.y - b.x * a.y;
}

template <typename T>
vector<Point<T>> get_convex_hull(vector<Point<T>> points) {
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
            [&points](Point<T> a, Point<T> b) {
                auto v1 = Vector<T>(points[0], a);
                auto v2 = Vector<T>(points[0], b);
                return v1.crossValueSquare(v2) > 0 || v1.crossValueSquare(v2) == 0 && v1.len() < v2.len();
            }
    );

    /* Second phase */

    vector<Point<T>> ch = {points[0], points[1]};

    for (int i = 2; i < points.size(); ++i) {
        while (ch.size() >= 2
               && cross<T>(
                Vector<T>(ch[ch.size() - 2], ch[ch.size() - 1]),
                Vector<T>(ch[ch.size() - 1], points[i])) <= 0)
        {
            ch.pop_back();
        }

        ch.push_back(points[i]);
    }

    return ch;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef DEBUG
        freopen("in", "r", stdin);
    #endif

    #ifdef COMMIT
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        
    #endif
    // Vector<ll>a, b;
    // auto v = Vector<double>(Point<double>)
    int n;
    cin >> n;
    std::vector<Point<ll>> points(n);
    for(auto &p : points)
        cin >> p;
    auto ch = get_convex_hull(points);
    // cout << a.x << ' ' << a.y;
    return 0;
}

template<typename T>
Point<T> Point<T>::operator+(Point & a){
        return Point(x + a.x, a.y + y);
}

template<typename T>
Point<T> Point<T>::operator-(Point & a){
    Point p = Point(x - a.x, y - a.y);
    return p;
}


template<typename T>
Point<T> Point<T>::operator+=(Point& a){
    Point b;
    x += a.x;
    y += a.y;
    return *this;
}


template<typename T>
Point<T> Point<T>::operator-=(Point& a){
    Point b;
    x -= a.x;
    y -= a.y;
    return *this;
}


template<typename T>
Point<T> Point<T>::operator*(T c){
    Point p(*this);
    p.x *= c;
    p.y *= c;
    return p;
}
