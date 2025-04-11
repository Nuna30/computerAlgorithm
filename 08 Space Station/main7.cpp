#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// const float eps = numeric_limits<float>::epsilon();
float eps = 0.00001;

struct point {
    float x, y, z;
    point(float x, float y, float z) : x(x), y(y), z(z) {}
};

// ###### coords ###############
// 10,  -6,  30,    56, 21, 120
// 300, 150, 350,  0,  0,  0
// #############################

vector<vector<int>> coords (2, vector<int>(6, 0));

float get_coord(int station, int i, float t) {
    return coords[station][i] + (coords[station][i] - coords[station][i + 3]) * t;
}

point get_point(int st, float t) {
    return {get_coord(st, 0, t), get_coord(st, 1, t), get_coord(st, 2, t)};
}

float calc_distance(point p1, point p2) {
    float dx = p2.x - p1.x, dy = p2.y - p1.y, dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float find_nextS(point p1, int toStation, float s_left, float s_right) {
    float s = (s_left + s_right) / 2;

    if (s >= -eps) return 0;
    else if (s + 1 <= eps) return -1;

    float sl_distance = calc_distance(p1, get_point(toStation, s - eps));
    float s_distance = calc_distance(p1, get_point(toStation, s));
    float sr_distance = calc_distance(p1, get_point(toStation, s + eps));

    if (sl_distance - s_distance < 0) return find_nextS(p1, toStation, s_left, s);
    else if (sr_distance - s_distance < 0) return find_nextS(p1, toStation, s, s_right);
    else return s;
}

int main() {
    for (auto& row : coords)
        for (int& x : row) cin >> x;

        int station = 0;
        float t = 0, s = 0, prev_t = -1, prev_s = -1, parameter = 0;
    
        while (true) {
            point p = get_point(station, parameter);
            station ^= 1;
            parameter = find_nextS(p, station, -1, 0);
    
            if (station == 0) prev_t = t, t = parameter;
            else prev_s = s, s = parameter;
    
            if (abs(prev_t - t) <= eps && abs(prev_s - s) <= eps) break;
        }
        float result = calc_distance(get_point(0, t), get_point(1, s));
        if (result <= 0.1) result = 0;
        cout << ceil(result);

    return 0;
}