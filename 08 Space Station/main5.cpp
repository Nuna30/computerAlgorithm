// #include <iostream>
// #include <vector>
// #include <cmath>
// using namespace std;

// struct point {
//     double x, y, z;
//     point(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
// };

// vector<vector<int>> c(2, vector<int>(6));
// pair<int, int> p[2][3];

// point get(int s, double t) {
//     auto& q = p[s];
//     return {q[0].first + q[0].second * t,
//             q[1].first + q[1].second * t,
//             q[2].first + q[2].second * t};
// }

// double dist(const point& a, const point& b) {
//     return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
// }

// double search(const point& a, int s, double l, double r) {
//     while (r - l > 1e-9) {
//         double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
//         double d1 = dist(a, get(s, m1)), d2 = dist(a, get(s, m2));
//         (d1 < d2 ? r : l) = (d1 < d2 ? m2 : m1);
//     }
//     return (l + r) / 2;
// }

// int main() {
//     for (auto& v : c) for (int& x : v) cin >> x;
//     for (int i = 0; i < 2; i++)
//         for (int j = 0; j < 3; j++)
//             p[i][j] = {c[i][j], c[i][j] - c[i][j+3]};

//     auto e = [&](int s) {
//         double a = p[s][0].first, b = p[s][0].second;
//         double t1 = 0, t2 = (c[s][3] - a) / b;
//         return make_pair(min(t1, t2), max(t1, t2));
//     };

//     point a = get(0, 0);
//     auto [s1, s2] = e(1);
//     double s = search(a, 1, s1, s2);
//     point b = get(1, s);
//     auto [t1, t2] = e(0);
//     double t = search(b, 0, t1, t2);

//     cout << ceil(dist(get(0, t), get(1, s))) << '\n';
// }
