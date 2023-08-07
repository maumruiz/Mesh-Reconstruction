#include <iostream>
#include "marching_cubes.h"

using namespace std;

int MarchingCubes::calculate_cube_index(GridCell &cell, float isovalue)
{
    int cubeIndex = 0;
    for (int i = 0; i < 8; i++)
        if (cell.value[i] < isovalue)
            cubeIndex |= (1 << i);
    return cubeIndex;
}

vector<Point> MarchingCubes::get_intersection_coordinates(GridCell &cell, float isovalue)
{
    vector<Point> intersections(12);

    int cubeIndex = calculate_cube_index(cell, isovalue);
    int intersectionsKey = edgeTable[cubeIndex];

    int idx = 0;
    while (intersectionsKey)
    {
        if (intersectionsKey & 1)
        {
            int v1 = edge_to_vertices[idx].first;
            int v2 = edge_to_vertices[idx].second;
            Point intersectionPoint = interpolate(cell.vertex[v1], cell.value[v1], cell.vertex[v2], cell.value[v2], isovalue);
            intersections[idx] = intersectionPoint;
        }
        idx++;
        intersectionsKey >>= 1;
    }

    return intersections;
}

Point MarchingCubes::interpolate(Point &v1, float val1, Point &v2, float val2, float isovalue)
{
    Point interpolated;
    float mu = (isovalue - val1) / (val2 - val1);

    interpolated.x = mu * (v2.x - v1.x) + v1.x;
    interpolated.y = mu * (v2.y - v1.y) + v1.y;
    interpolated.z = mu * (v2.z - v1.z) + v1.z;

    return interpolated;
}

vector<vector<Point>> MarchingCubes::get_triangles(vector<Point> &intersections, int cubeIndex)
{
    vector<vector<Point>> triangles;

    for (int i = 0; triangleTable[cubeIndex][i] != -1; i += 3)
    {
        vector<Point> triangle(3);
        for (int j = 0; j < 3; j++)
            triangle[j] = intersections[triangleTable[cubeIndex][i + j]];
        triangles.push_back(triangle);
    }
    return triangles;
}

void MarchingCubes::print_triangles(vector<vector<Point>> triangles)
{
    for (int i = 0; i < (int)triangles.size(); i++)
    {
        for (int j = 0; j < 3; j++)
            cout << triangles[i][j].x << ",\t" << triangles[i][j].y << ",\t" << triangles[i][j].z << "\n";
        cout << "\n";
    }
}

vector<vector<Point>> MarchingCubes::triangulate_cell(GridCell &cell, float isovalue)
{
    int cubeIndex = calculate_cube_index(cell, isovalue);
    vector<Point> intersections = get_intersection_coordinates(cell, isovalue);
    vector<vector<Point>> triangles = get_triangles(intersections, cubeIndex);

    return triangles;
}

vector<vector<Point>> MarchingCubes::triangulate_field(vector<vector<vector<float>>> &scalarFunction, float isovalue)
{
    int max = scalarFunction.size();
    vector<vector<Point>> triangles;

    for (int i = 0; i + 1 < max; i++)
        for (int j = 0; j + 1 < max; j++)
            for (int k = 0; k + 1 < max; k++)
            {
                float x = i, y = j, z = k;
                GridCell cell =
                    {
                        {
                            {x, y, z}, {x + 1.0f, y, z}, 
                            {x + 1.0f, y, z + 1.0f}, {x, y, z + 1.0f}, 
                            {x, y + 1.0f, z}, {x + 1.0f, y + 1.0f, z}, 
                            {x + 1.0f, y + 1.0f, z + 1.0f}, {x, y + 1.0f, z + 1.0f}},
                        {
                            scalarFunction[i][j][k], scalarFunction[i + 1][j][k],
                            scalarFunction[i + 1][j][k + 1], scalarFunction[i][j][k + 1],
                            scalarFunction[i][j + 1][k], scalarFunction[i + 1][j + 1][k],
                            scalarFunction[i + 1][j + 1][k + 1], scalarFunction[i][j + 1][k + 1]
                        }
                    };
                vector<vector<Point>> cellTriangles = triangulate_cell(cell, isovalue);
                for (int i = 0; i < (int)cellTriangles.size(); i++)
                    triangles.push_back(cellTriangles[i]);
            }
    return triangles;
}