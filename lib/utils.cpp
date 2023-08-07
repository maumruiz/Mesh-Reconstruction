#include "utils.h"

using namespace std;

VertexContainer hash_vertices_to_indices(vector<vector<Point>> &triangles)
{
    VertexContainer container;
    int count = 0;
    for (auto &triangle : triangles)
    {
        vector<int> indices;
        for (auto &vertex : triangle)
        {
            if (container.vertexMap.count(vertex) == 0)
            {
                container.vertexMap[vertex] = count;
                count++;
            }
            indices.push_back(container.vertexMap[vertex]);
        }
        container.triangles.push_back(indices);
    }

    return container;
}

void write_to_ply(vector<vector<Point>> &triangles, const char *path)
{
    VertexContainer container = hash_vertices_to_indices(triangles);

    ofstream outputFile;
    outputFile.open(path);

    outputFile << "ply\n";
    outputFile << "format ascii 1.0\n";
    outputFile << "element vertex " << container.vertexMap.size() << "\n";
    outputFile << "property float32 x\n";
    outputFile << "property float32 y\n";
    outputFile << "property float32 z\n";
    outputFile << "element face " << container.triangles.size() << "\n";
    outputFile << "property list uint8 int32 vertex_indices\n";
    outputFile << "end_header\n";

    vector<Point> vertices(container.vertexMap.size());
    for (auto &vertex: container.vertexMap)
        vertices[vertex.second] = vertex.first;
    
    for (auto &vertex: vertices)
        outputFile << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    
    for (auto &triangle: container.triangles) {
        outputFile << 3 << " ";
        for(int index: triangle)
            outputFile << index << " ";
        outputFile << "\n";
    }
}

void write_triangles_to_file(vector<vector<Point>> triangles, const char *path)
{
    ofstream outputFile;
    outputFile.open(path);
    for (int i = 0; i < (int)triangles.size(); i++)
    {
        outputFile << i << ":\n";
        for (int j = 0; j < 3; j++)
            outputFile << triangles[i][j].x << ",\t" << triangles[i][j].y << ",\t" << triangles[i][j].z << "\n";
        outputFile << "\n";
    }
}