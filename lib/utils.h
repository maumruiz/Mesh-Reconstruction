#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "types.h"

using namespace std;

void write_to_ply(vector<vector<Point>> &triangles, const char* path);
void write_triangles_to_file(vector<vector<Point>> triangles, const char* path);

#endif