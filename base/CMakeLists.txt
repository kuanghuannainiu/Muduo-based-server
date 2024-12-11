# 设置源文件目录和头文件目录
set(BASE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BASE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 获取源文件列表
file(GLOB BASE_SRC_LIST "${BASE_SRC_DIR}/*.cpp")

# 创建 base 库
add_library(base SHARED ${BASE_SRC_LIST})
target_include_directories(base PUBLIC ${BASE_INCLUDE_DIR})