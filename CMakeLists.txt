# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (FITing_Tree)

# 指定生成目标
add_executable(main main.cc bptree.h db_impl.h shrinkingcone_segmentation.h)
add_executable(main2 main2.cc bptree.h db_impl.h shrinkingcone_segmentation.h)
