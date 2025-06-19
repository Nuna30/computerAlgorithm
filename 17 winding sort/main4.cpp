#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <limits> 
#include <algorithm> 


const double PI = acos(-1.0);
const double EPS = 1e-9; 

struct point {
    int idx; 
    int x;  
    int y; 

    bool operator<(const point& other) const {
        return idx < other.idx;
    }
};

long long distSq(const point& p1, const point& p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

long long cross_product(point p1, point p2, point p3) {
    return (long long)(p2.x - p1.x) * (p3.y - p1.y) - (long long)(p2.y - p1.y) * (p3.x - p1.x);
}

bool is_support_line(const point& p, const point& q, const std::set<point>& S) {
    int common_sign = 0;

    for (const point& s : S) {
        if (s.idx == p.idx || s.idx == q.idx) {
            continue;
        }

        long long cp = cross_product(p, q, s);

        if (cp == 0) {
            continue;
        }

        int current_sign = (cp > 0) ? 1 : -1; 

        if (common_sign == 0) {
            common_sign = current_sign;
        } else if (common_sign != current_sign) {
            return false;
        }
    }
    return true;
}

int main() {
    int N;
    std::cin >> N;

    std::set<point> remaining_points;
    for (int i = 0; i < N; i++) {
        int idx, x, y;
        std::cin >> idx >> x >> y;
        remaining_points.insert({idx, x, y});
    }

    point current_pivot = {0, 0, 0}; 
    double current_angle = 0.0;     

    for (int k = 0; k < N; ++k) {
        point next_selected_point = {-1, -1, -1};
        double best_angle_diff = std::numeric_limits<double>::max(); 
        long long best_dist_sq = std::numeric_limits<long long>::max(); 

        for (const point& candidate_q : remaining_points) {
            if (!is_support_line(current_pivot, candidate_q, remaining_points)) {
                continue; 
            }
            double angle_to_candidate = atan2(candidate_q.y - current_pivot.y, candidate_q.x - current_pivot.x);
            if (angle_to_candidate < 0) {
                angle_to_candidate += 2 * PI;
            }
            double angle_diff = angle_to_candidate - current_angle;

            if (angle_diff < -EPS) { 
                angle_diff += 2 * PI;
            }
            if (angle_diff >= 2 * PI - EPS) {
                angle_diff = 0.0;
            }

            if (next_selected_point.idx == -1 || angle_diff < best_angle_diff - EPS) {
                next_selected_point = candidate_q;
                best_angle_diff = angle_diff;
                best_dist_sq = distSq(current_pivot, candidate_q);
            } else if (std::abs(angle_diff - best_angle_diff) < EPS) {
                long long current_d_sq = distSq(current_pivot, candidate_q);
                if (current_d_sq < best_dist_sq) {
                    next_selected_point = candidate_q;
                    best_dist_sq = current_d_sq;
                }
            }
        }

        std::cout << next_selected_point.idx << std::endl;
        point prev_pivot_for_angle_calc = current_pivot; 
        current_pivot = next_selected_point;            

        current_angle = atan2(current_pivot.y - prev_pivot_for_angle_calc.y, 
                              current_pivot.x - prev_pivot_for_angle_calc.x);
        
        if (current_angle < 0) {
            current_angle += 2 * PI;
        }

        remaining_points.erase(current_pivot);
    }

    return 0;
}