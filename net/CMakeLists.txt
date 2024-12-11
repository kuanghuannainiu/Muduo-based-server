# 设置源文件目录和头文件目录
set(NET_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(NET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 获取源文件列表
file(GLOB NET_SRC_LIST "${NET_SRC_DIR}/*.cpp")

# 创建 net 库
add_library(net SHARED ${NET_SRC_LIST})
target_include_directories(net PUBLIC ${NET_INCLUDE_DIR})