#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "data_structures.h"

using namespace std;

void write_to_ply(vector<vector<Point>> &triangles, const char* path);
void write_to_obj(Mesh const& mesh, string const& file);