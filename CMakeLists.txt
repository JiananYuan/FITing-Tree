# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (FITing_Tree)

set(CMAKE_CXX_STANDARD 14)

option(NDEBUG_SWITCH "disable assertion" OFF)

# 编译指导
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (NDEBUG_SWITCH)
    add_definitions(-DNDEBUG)
    list(APPEND CMAKE_REQUIRED_FLAGS -Werror -Wthread-safety -O3)
else (NDEBUG_SWITCH)
    list(APPEND CMAKE_REQUIRED_FLAGS -Werror -Wthread-safety)
endif(NDEBUG_SWITCH)

set(CMAKE_CXX_FLAGS_RELEASE -Ofast)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

# 指定生成目标
add_executable(test_latency test/test_latency.cc ATree/bptree.h ATree/db_impl.h ATree/shrinkingcone_segmentation.h)
add_executable(test_throughput test/test_throughput.cc ATree/bptree.h ATree/db_impl.h ATree/shrinkingcone_segmentation.h)
add_executable(test_workload test/test_workload.cc ATree/bptree.h ATree/db_impl.h ATree/shrinkingcone_segmentation.h)
