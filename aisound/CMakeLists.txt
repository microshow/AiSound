cmake_minimum_required(VERSION 3.4.1)

# 设置加载源文件路径 my_source
file(GLOB my_source src/main/cpp/*.cpp src/main/cpp/*.c src/main/cpp/*/*.cpp src/main/cpp/*/*.c)

# 设置变量
set(FFMPEG_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})

# 查找系统库 liblog.so
find_library( log-lib
              log)

# 添加库  动态导入
add_library( fmod
             SHARED
             IMPORTED)

# 设置库路径   ANDROID_ABI 自动赋予值
set_target_properties( fmod
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libfmod.so)

add_library( fmodL
             SHARED
             IMPORTED)

set_target_properties( fmodL
                       PROPERTIES IMPORTED_LOCATION
                       ${FFMPEG_LIB_DIR}/libfmodL.so)

# 引入cpp文件
add_library( aisound
             SHARED
             ${my_source})

# 引入头文件
include_directories(src/main/cpp/inc)

# 关联库
target_link_libraries( aisound
                       fmod
                       fmodL
                       ${log-lib})
