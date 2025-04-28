import math
import sys

def solve():
    input = sys.stdin.read().split()
    ptr = 0
    N = int(input[ptr])
    ptr += 1
    
    points = []
    # 시작점 추가
    S = (0, 500)
    points.append(S)
    
    for _ in range(N):
        x = int(input[ptr])
        y = int(input[ptr+1])
        points.append((x, y))
        ptr += 2
    
    # x좌표 기준으로 정렬
    points.sort()
    N = len(points)  # 시작점 포함
    
    # 거리 계산 함수
    def distance(a, b):
        dx = a[0] - b[0]
        dy = a[1] - b[1]
        return int(math.sqrt(dx*dx + dy*dy))
    
    # DP 테이블 초기화: dp[i][j]는 왼쪽 끝이 i, 오른쪽 끝이 j일 때 최소 거리
    dp = [[float('inf')] * N for _ in range(N)]
    dp[0][0] = 0  # 시작점에서 시작
    
    # 가장 오른쪽 점 (t)은 반드시 포함되어야 함
    t = N - 1
    
    for i in range(N):
        for j in range(N):
            if dp[i][j] == float('inf'):
                continue
            k = max(i, j) + 1
            if k >= N:
                continue
            if k != t:
                # 오른쪽으로 이동 (i -> k)
                dp[k][j] = min(dp[k][j], dp[i][j] + distance(points[i], points[k]))
                # 왼쪽으로 이동 (j -> k)
                dp[i][k] = min(dp[i][k], dp[i][j] + distance(points[j], points[k]))
            else:
                # t에 도달한 경우
                # 오른쪽에서 t로 이동
                dp[k][j] = min(dp[k][j], dp[i][j] + distance(points[i], points[k]))
                # 왼쪽에서 t로 이동
                dp[i][k] = min(dp[i][k], dp[i][j] + distance(points[j], points[k]))
    
    # 최종적으로 t에서 시작점으로 돌아오는 경로 계산
    min_dist = float('inf')
    for i in range(N):
        dist = dp[i][t] + distance(points[i], S)
        if dist < min_dist:
            min_dist = dist
    for j in range(N):
        dist = dp[t][j] + distance(points[j], S)
        if dist < min_dist:
            min_dist = dist
    
    print(min_dist)

solve()