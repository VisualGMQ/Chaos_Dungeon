aux_source_directory(../src TEST_SRC)
include_directories(../include)
add_executable(TestMath tmath.cpp ${TEST_SRC})
