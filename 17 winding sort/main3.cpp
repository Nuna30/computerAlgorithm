#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <limits> // std::numeric_limits
#include <algorithm> // std::abs, std::min (though not explicitly used for min, good to include)

// pi 값 정의
const double PI = acos(-1.0);
// 부동 소수점 비교를 위한 작은 오차 범위 (epsilon)
const double EPS = 1e-9; 

// 점을 나타내는 구조체
struct point {
    int idx; // 점의 고유 인덱스
    int x;   // x 좌표
    int y;   // y 좌표

    // std::set에 사용될 비교 연산자
    // 문제의 조건상 idx가 고유 식별자이므로, idx 기준으로만 비교하여 set의 원소 고유성을 보장합니다.
    bool operator<(const point& other) const {
        return idx < other.idx;
    }
};

// 두 점 사이의 유클리드 거리의 제곱을 계산합니다.
// sqrt를 사용하지 않아 부동 소수점 오류를 피하고 연산을 빠르게 합니다.
long long distSq(const point& p1, const point& p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// 세 점 p1, p2, p3에 대한 교차곱(cross product)을 계산합니다.
// 결과의 부호는 p1에서 p2로 가는 벡터와 p1에서 p3로 가는 벡터의 상대적 방향을 나타냅니다.
// > 0: p1 -> p2 -> p3가 반시계 방향
// < 0: p1 -> p2 -> p3가 시계 방향
// = 0: 세 점이 일직선상에 있음 (collinear)
long long cross_product(point p1, point p2, point p3) {
    return (long long)(p2.x - p1.x) * (p3.y - p1.y) - (long long)(p2.y - p1.y) * (p3.x - p1.x);
}

// (p, q)가 "support line"을 형성하는지 확인합니다.
// 즉, 집합 S의 p와 q를 제외한 모든 점들이 직선 pq의 한쪽(같은 부호)에 있는지 확인합니다.
bool is_support_line(const point& p, const point& q, const std::set<point>& S) {
    int common_sign = 0; // 모든 점의 공통 부호를 저장

    for (const point& s : S) {
        // 현재 기준점 p 또는 후보점 q는 비교에서 제외
        if (s.idx == p.idx || s.idx == q.idx) {
            continue;
        }

        long long cp = cross_product(p, q, s);

        if (cp == 0) {
            // 점 s가 p와 q와 일직선상에 있는 경우
            // "support line" 조건에서는 일직선상에 있는 점은 한쪽에 있는 것으로 간주합니다.
            // 거리는 나중에 다음 점을 선택할 때 처리됩니다.
            continue;
        }

        int current_sign = (cp > 0) ? 1 : -1; // 현재 점 s의 부호

        if (common_sign == 0) {
            // 첫 번째로 발견된 비-일직선상 점의 부호를 공통 부호로 설정
            common_sign = current_sign;
        } else if (common_sign != current_sign) {
            // 다른 쪽에 있는 점이 발견되면 support line이 아님
            return false;
        }
    }
    return true; // 모든 점이 한쪽에 있음 (또는 일직선상에 있음)
}

int main() {
    // 입출력 속도 향상
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;

    // 아직 선택되지 않은 점들을 저장할 set
    std::set<point> remaining_points;
    for (int i = 0; i < N; i++) {
        int idx, x, y;
        std::cin >> idx >> x >> y;
        remaining_points.insert({idx, x, y});
    }

    // 시작점 (0,0) 정의
    point current_pivot = {0, 0, 0}; 
    // 현재 회전선의 각도 (라디안), 초기값은 양의 x축 방향 (0도)
    double current_angle = 0.0;     

    // N개의 점을 모두 선택할 때까지 반복
    for (int k = 0; k < N; ++k) {
        point next_selected_point = {-1, -1, -1}; // 다음에 선택될 점 (초기화)
        double best_angle_diff = std::numeric_limits<double>::max(); // 가장 작은 각도 차이
        long long best_dist_sq = std::numeric_limits<long long>::max(); // 가장 짧은 거리의 제곱

        // `remaining_points` 내의 모든 점들을 순회하며 다음 선택될 점을 찾음
        for (const point& candidate_q : remaining_points) {
            // 현재 pivot에서 candidate_q로의 선분이 support line인지 확인
            if (!is_support_line(current_pivot, candidate_q, remaining_points)) {
                continue; // support line이 아니면 건너김
            }

            // current_pivot에서 candidate_q로의 각도를 계산 (라디안, -PI ~ PI 범위)
            double angle_to_candidate = atan2(candidate_q.y - current_pivot.y, candidate_q.x - current_pivot.x);

            // 각도를 [0, 2*PI) 범위로 정규화 (필요하다면)
            if (angle_to_candidate < 0) {
                angle_to_candidate += 2 * PI;
            }

            // 현재 `current_angle` (이전 선분의 각도)로부터 `candidate_q`까지의 각도 차이 계산
            double angle_diff = angle_to_candidate - current_angle;

            // angle_diff를 [0, 2*PI) 범위로 조정 (반시계 방향 회전을 시뮬레이션)
            if (angle_diff < -EPS) { // 각도 차이가 음수라면 (시계 방향이라면) 2*PI를 더해 반시계 방향으로 만나는 각도로 변환
                angle_diff += 2 * PI;
            }
            // 거의 2*PI라면 0으로 간주 (한바퀴 돈 것)
            if (angle_diff >= 2 * PI - EPS) {
                angle_diff = 0.0;
            }

            // 다음 점 선택 로직:
            // 1. 가장 작은 양의 `angle_diff`를 가진 점 선택
            // 2. `angle_diff`가 같으면 (오차 범위 내에서) `current_pivot`으로부터 거리가 가장 짧은 점 선택
            if (next_selected_point.idx == -1 || angle_diff < best_angle_diff - EPS) {
                // 더 작은 각도 차이를 가진 점을 찾았을 경우
                next_selected_point = candidate_q;
                best_angle_diff = angle_diff;
                best_dist_sq = distSq(current_pivot, candidate_q);
            } else if (std::abs(angle_diff - best_angle_diff) < EPS) {
                // 각도 차이가 사실상 같은 경우, 거리를 비교
                long long current_d_sq = distSq(current_pivot, candidate_q);
                if (current_d_sq < best_dist_sq) {
                    // 더 가까운 점을 선택
                    next_selected_point = candidate_q;
                    best_dist_sq = current_d_sq;
                }
            }
        }

        // 선택된 점의 인덱스 출력
        std::cout << next_selected_point.idx << std::endl;

        // 다음 반복을 위해 현재 pivot과 각도 업데이트
        point prev_pivot_for_angle_calc = current_pivot; // 현재 pivot을 백업 (각도 계산용)
        current_pivot = next_selected_point;             // 선택된 점이 다음 pivot이 됨

        // 다음 회전의 기준 각도는 현재 pivot으로 이동하여, 이전 pivot에서 현재 pivot으로 이어진 선분의 각도
        // (즉, 방금 선택된 점을 향한 각도)가 됩니다.
        current_angle = atan2(current_pivot.y - prev_pivot_for_angle_calc.y, 
                              current_pivot.x - prev_pivot_for_angle_calc.x);
        
        // 각도를 [0, 2*PI) 범위로 정규화
        if (current_angle < 0) {
            current_angle += 2 * PI;
        }

        // 선택된 점은 `remaining_points`에서 제거
        remaining_points.erase(current_pivot);
    }

    return 0;
}