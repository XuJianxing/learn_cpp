# CMakeList.txt: leetcode 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("leetcode")

# 要在生成的项目中启用 C++17 标准。且要在生成执行文件的前面设置
set(CMAKE_CXX_STANDARD 17)

# 包含头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/src/include)

# 添加子目录
add_subdirectory(learn_cpp)
add_subdirectory(leetcode)

# 将源代码添加到此项目的可执行文件。
add_executable (leetcode "leetcode.cpp" "leetcode.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET leetcode PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
