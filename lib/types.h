#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <vector>

using namespace std;

struct Point {
    float x;
    float y;
    float z;

    bool operator<(const Point& p) const {
        if (x != p.x)
            return x < p.x;
        if (y != p.y)
            return y < p.y;
        return z < p.z;
    }
};

struct GridCell {
    Point vertex[8];
    float value[8];
};

struct VertexContainer {
    map<Point,int> vertexMap;
    vector<vector<int>> triangles;
};

#endif