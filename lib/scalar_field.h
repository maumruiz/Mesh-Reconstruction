#ifndef SCALARFIELD_H
#define SCALARFIELD_H

#include "types.h"
#include <vector>

using namespace std;

class ScalarField {
    public:
        int GRID_MAX;
        ScalarField(int max);

        float get_random_number();
        vector<vector<vector<float>>> random_grid();
        vector<vector<vector<float>>> sphere(float centerX, float centerY, float centerZ, float radius);
        vector<vector<vector<float>>> nested_spheres();
        vector<vector<vector<float>>> read_grid_from_file(const char* path);
};

#endif