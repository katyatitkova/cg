project(cg-test)

cmake_minimum_required(VERSION 2.8)

find_package(CGAL)
include(${CGAL_USE_FILE})
include(CGAL_CreateSingleSourceCGALProgram)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIR})

find_package(Boost COMPONENTS random system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARYDIR})

set(SOURCES
   orientation.cpp
   has_intersection.cpp
   contains.cpp
   convex_hull.cpp
   convex.cpp
   intersection.cpp
   dynamic_convex_hull.cpp
   douglas_peucker.cpp
)

add_executable(cg-test ${SOURCES})
target_link_libraries(cg-test ${GTEST_BOTH_LIBRARIES} ${GMP_LIBRARIES})

file(GLOB_RECURSE HEADERS "*.h")
add_custom_target(cg_test_headers SOURCES ${HEADERS})
