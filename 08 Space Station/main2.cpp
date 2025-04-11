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
//         vector3 operator + (const vector3& other) const {
//             return vector3(x + other.x, y + other.y, z + other.z);
//         }
//         vector3 operator - (const vector3& other) const {
//             return vector3(x - other.x, y - other.y, z - other.z);
//         }
//         double operator * (const vector3& other) const {
//             return (x * other.x + y * other.y + z * other.z);
//         }
//         vector3 operator * (double s) const {
//             return vector3(x * s, y * s, z * s);
//         }
//         vector3 operator ^ (const vector3& other) const {
//             return vector3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
//         }
//         double N() {
//             return sqrt(x * x + y * y + z * z);
//         }
//         bool operator == (const vector3& other) const {
//             return (x == other.x && y == other.y && z == other.z) || (x == -other.x && y == -other.y && z == -other.z);
//         }
//         double distance (const vector3& other) const {
//             double dx = x - other.x;
//             double dy = y - other.y;
//             double dz = z - other.z;
//             return sqrt(dx * dx + dy * dy + dz * dz);
//         }
// };

// int main() {
//     vector3 coords[4];

//     for (int i = 0; i < 4; i++) {
//         int x, y, z;
//         cin >> x >> y >> z;
//         coords[i] = vector3(x,y,z);
//     }

//     vector3 A = coords[0];
//     vector3 B = coords[1];
//     vector3 C = coords[2];
//     vector3 D = coords[3];

//     vector3 AB = B - A;
//     vector3 CD = D - C;
//     vector3 AC = C - A;

//     double d = min({
//         coords[0].distance(coords[2]),
//         coords[0].distance(coords[3]),
//         coords[1].distance(coords[2]),
//         coords[1].distance(coords[3])
//     });

//     if (AB == CD) cout << ceil(abs((AC ^ AB).N() / AB.N())) << '\n';
//     else {

//     }


//     cout << (int)ceil(d) << '\n';
//     return 0;
// }