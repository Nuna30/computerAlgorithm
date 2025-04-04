#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <cmath>
#include <limits>

using namespace std;

const float float_epsilon = numeric_limits<float>::epsilon();


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
float l(int a, int b, float t) {
    return a + b * t;
}

// 매개변수 t, s로 xyz 좌표 계산
tuple<float, float, float> calc_xyz(int station, float t) {
    float x, y, z;
    x = l(params[station][0].first, params[station][0].second, t);   
    y = l(params[station][1].first, params[station][1].second, t);
    z = l(params[station][2].first, params[station][2].second, t);
    return {x, y, z};
}

// 두 점 p1, p2 거리
float distance(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
}

// 점 p에서 매개변수가 t인 곳과의 거리 계산
float calc_distance(int x, int y, int z, int station, float t) {
    auto [x2, y2, z2] = calc_xyz(station, t);
    return distance(x, y, z, x2, y2, z2);
}

// p1의 최단지점인 p2의 s 찾기
// t_E1과 t_E2는 정거장의 양 끝점에 해당하는 매개변수
float find_nextS(int x, int y, int z, int theOtherStation) {
    auto [a, b] = params[theOtherStation][0];
    float x2 = coords[theOtherStation][4];

    float s_E1 = 0;
    float s_E2 = (x2 - a) / b;

    if (s_E2 < 0) {
        float temp = s_E1;
        s_E1 = s_E2;
        s_E2 = temp;
    }

    float s_left = s_E1;
    float s = (s_E1 + s_E2) / 2;
    float s_right = s_E2;
    
    while (true) { 
        if (s - float_epsilon <= s_E1) return s_E1;
        else if (s + float_epsilon >= s_E2) return s_E2;

        // 엡실론만큼만 검사하면 값이 안 변해서 10배 해줌
        float sl_distance = calc_distance(x, y, z, theOtherStation, s - 10 * float_epsilon);
        float s_distance = calc_distance(x, y, z, theOtherStation, s);
        float sr_distance = calc_distance(x, y, z, theOtherStation, s + 10 * float_epsilon);
        
        printf("sl, s, sr : %.20lf, %.20lf, %.20lf\n", sl_distance, s_distance, sr_distance);

        if (sl_distance < s_distance) s_right = s;
        else if (sr_distance < s_distance) s_left = s;
        else return s;

        s = (s_left + s_right) / 2;
    }
}

int find_minDistance() {
    int targetStation = 0;
    float parameter = 0;
    float prev_parameter = 0;

    while (true) {
        auto [x, y, z] = calc_xyz(targetStation, parameter);
        targetStation = (targetStation + 1) % 2;
        prev_parameter = parameter;
        parameter = find_nextS(x, y, z, targetStation);
        printf("p : (%lf, %lf) \n", parameter, prev_parameter);
        if (abs(parameter - prev_parameter) <= 0.1) {
            auto [x1, y1, z1] = calc_xyz(targetStation, parameter);
            targetStation = (targetStation + 1) % 2;
            auto [x2, y2, z2] = calc_xyz(targetStation, prev_parameter);
            printf("(%lf, %lf, %lf), (%lf, %lf, %lf)\n", x1, y1, z1, x2, y2, z2);
            float minDistance = distance(x1, y1, z1, x2, y2, z2);
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

    케이스 1, 5는 맞고 2, 3, 4는 틀림.
    어째서?
    좌표 위에 직접 점 찍어서 확인해볼 것
    -8 -9 -8
    -10 0 3 이 두 점이 최단거리로 보임 근데 계산하면 14.~인데 
    답은 9임 이 두 점이 왜 최단거리가 아닌지 알아내야 함

    return 0;
}