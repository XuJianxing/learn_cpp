# 自动收集当前目录下所有 .cpp 文件，每个文件生成一个可执行文件。
# CONFIGURE_DEPENDS: 新增/删除源文件时，构建阶段会自动重新执行 glob。
file(GLOB LEETCODE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(source_file IN LISTS LEETCODE_SOURCES)
  # 取第一个点之前的部分作为题号，例如 238.除了自身以外数组的乘积.cpp -> 238
  get_filename_component(problem_id "${source_file}" NAME_WE)
  set(target_name "leetcode_${problem_id}")

  add_executable(${target_name} "${source_file}")
  set_target_properties(${target_name} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
endforeach()
