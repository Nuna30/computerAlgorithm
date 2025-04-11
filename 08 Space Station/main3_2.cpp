// #include <iostream>
// #include <vector>
// #include <utility>
// #include <cmath>
// #include <limits>

// using namespace std;

// const double eps = 0.0001;

// struct point {
//     double x, y, z;
//     point(double x, double y, double z) : x(x), y(y), z(z) {}
// };

// // ###### coords ###############
// // 10,  -6,  30,    56, 21, 120
// // 300, 150, 350,  0,  0,  0
// // #############################

// vector<vector<int>> coords (2, vector<int>(6, 0));

// double get_coord(int st, int i, double t) {
//     double a = coords[st][i], b = coords[st][i + 3];
//     return a + (a - b) * t;
// }

// point get_point(int st, double t) {
//     return {get_coord(st, 0, t), get_coord(st, 1, t), get_coord(st, 2, t)};
// }

// double calc_distance(const point& p1, const point& p2) {
//     double dx = p2.x - p1.x, dy = p2.y - p1.y, dz = p2.z - p1.z;
//     return sqrt(dx * dx + dy * dy + dz * dz);
// }

// double find_nextS(point p1, int toStation, double s_left, double s_right) {
//     double s = (s_left + s_right) / 2;

//     if (abs(s_right - s_left) < eps) return s;

//     double sl_distance = calc_distance(p1, get_point(toStation, s - eps));
//     double s_distance = calc_distance(p1, get_point(toStation, s));
//     double sr_distance = calc_distance(p1, get_point(toStation, s + eps));

//     if (sl_distance < s_distance) return find_nextS(p1, toStation, s_left, s);
//     else if (sr_distance < s_distance) return find_nextS(p1, toStation, s, s_right);
//     else return s;
// }

// int find_minDistance() {
//     int station = 0;
//     double t = 0, s = 0, prev_t = -1, prev_s = -1, parameter = 0;

//     int count = 10000;
//     while (count--) {
//         point p = get_point(station, parameter);
//         station ^= 1;
//         parameter = find_nextS(p, station, -1, 0);

//         if (station == 0) prev_t = t, t = parameter;
//         else prev_s = s, s = parameter;

//         // printf("distance : %lf\n", calc_distance(get_point(0, t), get_point(1, s)));
//     }
//     return ceil(calc_distance(get_point(0, t), get_point(1, s)));
// }

// int main() {
//     for (auto& row : coords)
//         for (int& x : row) cin >> x;

//     cout << find_minDistance() << '\n';

//     return 0;
// }