#include <iostream>
#include <string>

#include "scalar_field.h"
#include "marching_cubes.h"
#include "utils.h"

using namespace std;

int main()
{
    // string file_in = <data_path>;
    string file_out = ""; // out model path
    float isovalue = 0.0;

    MarchingCubes marchingCubes = MarchingCubes();
    int max = 400;

    // Generate or read the scalar field
    ScalarField sf = ScalarField(max);
    cout << "Getting scalar field..." << flush;
    auto field = sf.sphere(32, 32, 32, 30);
    // auto field = sf.read_grid_from_file(file_in.c_str());
    cout << "Done. \n"
         << flush;

    // Reconstruct mesh
    cout << "Triangulating using marching cubes..." << flush;
    auto triangles = marchingCubes.triangulate_field(field, isovalue);
    cout << "Done. \n"
         << flush;

    cout << "Number of triangles: " << triangles.size() << "\n";
    write_to_ply(triangles, file_out.c_str());

    return 0;
}