#pragma once

#include <map>
#include <vector>

using namespace std;

using Triangle = array<int, 3>;

struct Vec3
{
    double x, y, z;

    Vec3 operator+(Vec3 const &other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(Vec3 const &other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(double num) const
    {
        return {x * num, y * num, z * num};
    }

    bool operator<(Vec3 const &other) const
    {
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        return z < other.z;
    }

    double Norm() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    Vec3 Normalize() const
    {
        auto n = Norm();
        return {x / n, y / n, z / n};
    }
};

struct Rect3
{
    Vec3 min;
    Vec3 size;
};

struct Point
{
    float x;
    float y;
    float z;

    bool operator<(const Point &p) const
    {
        if (x != p.x)
            return x < p.x;
        if (y != p.y)
            return y < p.y;
        return z < p.z;
    }
};

struct GridCell
{
    Point vertex[8];
    float value[8];
};

struct VertexContainer
{
    map<Point, int> vertexMap;
    vector<vector<int>> triangles;
};

struct Mesh {
    vector<Vec3> vertices;
    vector<Triangle> triangles;
    vector<Vec3> vertexNormals;
};