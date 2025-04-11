// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <limits>
// #include <utility>
// using namespace std;

// const double eps = numeric_limits<double>::epsilon();

// struct point {
//     double x, y, z;
//     point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
// };

// vector<vector<int>> coords(2, vector<int>(6));
// vector<vector<pair<int, int>>> params(2, vector<pair<int, int>>(3));

// point get_point(int station, double t) {
//     auto& p = params[station];
//     return {
//         p[0].first + p[0].second * t,
//         p[1].first + p[1].second * t,
//         p[2].first + p[2].second * t
//     };
// }

// double dist(const point& a, const point& b) {
//     double dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
//     return sqrt(dx * dx + dy * dy + dz * dz);
// }

// double binary_search(const point& fixed, int station, double l, double r) {
//     double m = (l + r) / 2;
//     if (abs(r - l) < eps) return m;

//     double d1 = dist(fixed, get_point(station, m - eps));
//     double d2 = dist(fixed, get_point(station, m));
//     double d3 = dist(fixed, get_point(station, m + eps));

//     if (d1 < d2) return binary_search(fixed, station, l, m);
//     if (d3 < d2) return binary_search(fixed, station, m, r);
//     return m;
// }

// vector<double> endpoints(int station) {
//     double s1 = 0;
//     double s2 = (coords[station][3] - params[station][0].first) / params[station][0].second;
//     if (s2 < s1) swap(s1, s2);
//     return {s1, s2};
// }

// int find_minDistance() {
//     point p1 = get_point(0, 0);
//     auto e1 = endpoints(1);
//     double s = binary_search(p1, 1, e1[0], e1[1]);

//     point p2 = get_point(1, s);
//     auto e0 = endpoints(0);
//     double t = binary_search(p2, 0, e0[0], e0[1]);

//     return ceil(dist(get_point(0, t), p2));
// }

// int main() {
//     for (auto& line : coords)
//         for (auto& c : line) cin >> c;

//     for (int i = 0; i < 2; i++)
//         for (int j = 0; j < 3; j++)
//             params[i][j] = {coords[i][j], coords[i][j] - coords[i][j + 3]};

//     cout << find_minDistance() << '\n';
//     return 0;
// }
