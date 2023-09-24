cmake_minimum_required(VERSION 3.10)

# Arbitrary name
project(marching-cubes)


# LIBRARIES
LIST(APPEND LIB_FILES "lib/scalar_field.h" "lib/scalar_field.cpp" "lib/marching_cubes.h" "lib/marching_cubes.cpp" "lib/utils.h" "lib/utils.cpp")
add_library(lib STATIC ${LIB_FILES})



# EXECUTABLES
LIST(APPEND HEADER_FILES "lib/data_structures.h")
LIST(APPEND SOURCE_FILES "main.cpp")

# Define an executable with a name and the files
add_executable(marching-cubes ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(marching-cubes PUBLIC "lib")  # Make the lib folder an include directory
target_link_libraries(marching-cubes PUBLIC lib)  # Link this library to our executable

# Redirect standard output
execute_process(
    COMMAND ./marching-cubes ${SOURCE_FILES} ${HEADER_FILES}
)