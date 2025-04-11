// #include <iostream>
// #include <vector>
// #include <utility>
// #include <cmath>
// #include <limits>

// using namespace std;

// const double eps = numeric_limits<double>::epsilon();

// struct point {
//     double x, y, z;
//     point(double x, double y, double z) : x(x), y(y), z(z) {}
//     point(const vector<int>& vi) : x(vi[0]), y(vi[1]), z(vi[2]) {}
// };

// // ###### coords ###############
// // 10,  -6,  30,    56, 21, 120
// // 300, 150, 350,  0,  0,  0
// // #############################

// vector<vector<int>> coords (2, vector<int>(6, 0));

// double l(int a, int b, double t) {
//     return a + b * t;
// }

// point get_point(int station, double t) {
//     vector<int> vi (3, 0);
//     for (int i = 0; i < 3; i++) vi[i] = l(coords[station][i], coords[station][i] - coords[station][i + 3], t);
//     return vi;
// }

// double calc_distance(const point& p1, const point& p2) {
//     double dx = p2.x - p1.x;
//     double dy = p2.y - p1.y;
//     double dz = p2.z - p1.z;
//     return sqrt(dx * dx + dy * dy + dz * dz);
// }

// double find_nextS(point p1, int toStation, double s_left, double s_right) {
//     double s = (s_left + s_right) / 2;

//     if (abs(s - s_left) <= eps || abs(s - s_right) <= eps) return s;

//     double sl_distance = calc_distance(p1, get_point(toStation, s - eps));
//     double s_distance = calc_distance(p1, get_point(toStation, s));
//     double sr_distance = calc_distance(p1, get_point(toStation, s + eps));

//     if (sl_distance < s_distance) return find_nextS(p1, toStation, s_left, s);
//     else if (sr_distance < s_distance) return find_nextS(p1, toStation, s, s_right);
//     else return s;
// }

// vector<double> find_endpoints(int station) {
//     double a = coords[station][0];
//     double b = coords[station][0] - coords[station][3];
//     double x2 = coords[station][3];

//     double s_E1 = 0;
//     double s_E2 = (x2 - a) / b;

//     if (s_E2 < 0) {
//         double temp = s_E1;
//         s_E1 = s_E2;
//         s_E2 = temp;
//     }

//     return {s_E1, s_E2};
// }

// int find_minDistance() {
//     point p1 = get_point(0, 0);
//     vector<double> endpoints = find_endpoints(1);
//     double s = find_nextS(p1, 1, endpoints[0], endpoints[1]);

//     point p2 = get_point(1, s);
//     endpoints = find_endpoints(0);
//     double t = find_nextS(p2, 0, endpoints[0], endpoints[1]);

//     return ceil(calc_distance(get_point(0, t), p2));
// }

// int main() {
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 6; j++) cin >> coords[i][j];
//     }

//     cout << find_minDistance() << '\n';

//     return 0;
// }