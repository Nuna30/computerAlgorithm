#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <cmath>
#include <limits>

using namespace std;

const double double_epsilon = numeric_limits<double>::epsilon();
const double DOUBLE_MAX = numeric_limits<double>::max();


// ###### coords ###############
// 300, 150, 350,  0,  0,  0
// 10,  -6,  3,    56, 21, 120
// #############################

//                |
//                V

// ##### params #######################################
// {10, -46},        {-6, -27},        {30, -90}
// {350, -350},      {150, -150},      {350, -350}
// ####################################################
//                      ||
// (x = 10 - 46t),   (y = -6 -27t),    (z = 30 - 90t)
// (x = 350 - 350s), (y = 150 - 150s), (z = 350 - 350s)

vector<vector<int>> coords;
vector<vector<pair<int, int>>> params;

// y = a + bt 계산
double l(int a, int b, double t) {
    return a + b * t;
}

// 매개변수 t, s로 xyz 좌표 계산
tuple<double, double, double> calc_xyz(int station, double t) {
    double x, y, z;
    x = l(params[station][0].first, params[station][0].second, t);   
    y = l(params[station][1].first, params[station][1].second, t);
    z = l(params[station][2].first, params[station][2].second, t);
    return {x, y, z};
}

// 두 점 p1, p2 거리
double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
}

// 점 p에서 매개변수가 t인 곳과의 거리 계산
double calc_distance(double x, double y, double z, int station, double t) {
    auto [x2, y2, z2] = calc_xyz(station, t);
    return distance(x, y, z, x2, y2, z2);
}

// p1의 최단지점인 p2의 s 찾기
// t_E1과 t_E2는 정거장의 양 끝점에 해당하는 매개변수
double find_nextS(double x, double y, double z, int theOtherStation) {
    auto [a, b] = params[theOtherStation][0];
    double x2 = coords[theOtherStation][3];

    double s_E1 = 0;
    double s_E2 = (x2 - a) / b;

    if (s_E2 < 0) {
        double temp = s_E1;
        s_E1 = s_E2;
        s_E2 = temp;
    }

    double s_left = s_E1;
    double s = (s_E1 + s_E2) / 2;
    double s_right = s_E2;
    
    while (true) { 
        if (abs(s - s_E1) <= double_epsilon) return s_E1;
        else if (abs(s - s_E2) <= double_epsilon) return s_E2;

        double sl_distance = calc_distance(x, y, z, theOtherStation, s - double_epsilon);
        double s_distance = calc_distance(x, y, z, theOtherStation, s);
        double sr_distance = calc_distance(x, y, z, theOtherStation, s + double_epsilon);

        if (sl_distance < s_distance) s_right = s;
        else if (sr_distance < s_distance) s_left = s;
        else return s;

        s = (s_left + s_right) / 2;
    }
}

int find_minDistance() {
    int targetStation = 0;
    double t = 0;
    double s = 0;
    double prev_t = DOUBLE_MAX;
    double prev_s = DOUBLE_MAX;
    double parameter = t;

    while (true) {
        auto [x, y, z] = calc_xyz(targetStation, parameter);

        targetStation = ((targetStation == 0) ? 1 : 0);

        parameter = find_nextS(x, y, z, targetStation);

        if (targetStation == 0) {
            prev_t = t;
            t = parameter;
        }
        else {
            prev_s = s;
            s = parameter;
        }

        if (abs(prev_t - t) <= double_epsilon && abs(prev_s - s) <= double_epsilon) {
            auto [x1, y1, z1] = calc_xyz(0, t);
            auto [x2, y2, z2] = calc_xyz(1, s);
            double minDistance = distance(x1, y1, z1, x2, y2, z2);
            return ceil(minDistance);
        }
    }

}

int main() {
    coords.resize(2, vector<int>(6, 0));
    params.resize(2, vector<pair<int, int>>(3));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) cin >> coords[i][j];
    }

    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            params[i][j] = {coords[i][j], coords[i][j] - coords[i][j + 3]};
        }
    }

    cout << find_minDistance() << '\n';

    return 0;
}

토큰 800개를 300개로 줄이기???

그냥 수학식으로 풀자....