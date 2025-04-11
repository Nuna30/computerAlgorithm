// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cmath>

// using namespace std;

// class vector3 {
//     private :
//         double x, y, z;
//     public :
//         vector3(double x, double y, double z) : x(x), y(y), z(z) {}
//         vector3() {}
//         vector3 operator + (const vector3& o) const { return vector3(x + o.x, y + o.y, z + o.z); }
//         vector3 operator - (const vector3& o) const { return vector3(x - o.x, y - o.y, z - o.z); }
//         double operator * (const vector3& o) const { return x * o.x + y * o.y + z * o.z; }
//         vector3 operator * (double s) const { return vector3(x * s, y * s, z * s); }
//         double N() { return sqrt(x*x + y*y + z*z); }
// };

// // 두 선분 AB와 CD 사이의 최단 거리
// double segmentToSegment(vector3 A, vector3 B, vector3 C, vector3 D) {
//     vector3 u = B - A;
//     vector3 v = D - C;
//     vector3 w = A - C;

//     double a = u * u;
//     double b = u * v;
//     double c = v * v;
//     double d = u * w;
//     double e = v * w;

//     double Deno = a*c - b*b;
//     double sc, tc;

//     if (Deno < 1e-8) {
//         sc = 0.0;
//         tc = (b>c ? d/b : e/c);
//     } else {
//         sc = (b*e - c*d) / Deno;
//         tc = (a*e - b*d) / Deno;
//     }

//     sc = max(0.0, min(1.0, sc));
//     tc = max(0.0, min(1.0, tc));

//     vector3 p1 = A + u * sc;
//     vector3 p2 = C + v * tc;
//     return (p1 - p2).N();
// }

// int main() {
//     vector3 coords[4];
//     for (int i = 0; i < 4; ++i) {
//         int x, y, z;
//         cin >> x >> y >> z;
//         coords[i] = vector3(x, y, z);
//     }

//     vector3 A = coords[0], B = coords[1], C = coords[2], D = coords[3];

//     double d = segmentToSegment(A, B, C, D);
//     cout << (int)ceil(d) << '\n';
//     return 0;
// }
