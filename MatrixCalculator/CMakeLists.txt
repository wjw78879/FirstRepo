PROJECT( MatrixCalculator )

SET( CMAKE_BUILD_TYPE "Debug" )
SET( CMAKE_CXX_FLAGS_DEBUG 
    "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb" )
SET( MATRIX_VERSION_MAJOR 1 )
SET( MATRIX_VERSION_MINOR 0 )

configure_file( "${PROJECT_SOURCE_DIR}/MatrixConfig.h.in" 
                "${PROJECT_BINARY_DIR}/MatrixConfig.h" )

SUBDIRS( src test )