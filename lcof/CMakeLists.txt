# 自动收集当前目录下所有 .cpp 文件，每个文件生成一个可执行文件。
# CONFIGURE_DEPENDS: 新增/删除源文件时，构建阶段会自动重新执行 glob。
file(GLOB LCOF_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 文件名可能包含空格/中文（如 "LCR 125.图书整理-ii.cpp"）：
# 1) CMake 目标名只允许字母、数字、下划线等字符；
# 2) 未加引号的变量展开中一旦含空格，会被拆成多个参数导致 add_executable 报错。
# 因此统一把非法字符规范化为下划线，并用序号兜底保证目标名唯一。
set(lcof_target_index 0)

foreach(source_file IN LISTS LCOF_SOURCES)
  math(EXPR lcof_target_index "${lcof_target_index} + 1")

  # 取第一个点之前的部分作为题号，例如 LCR165.解密数字.cpp -> LCR165
  get_filename_component(problem_id "${source_file}" NAME_WE)
  string(REGEX REPLACE "[^A-Za-z0-9_]" "_" safe_id "${problem_id}")

  # 规范化后无任何字母/数字（例如纯中文文件名）时用序号兜底
  string(REGEX MATCH "[A-Za-z0-9]" has_alnum "${safe_id}")
  if(NOT has_alnum)
    set(safe_id "problem_${lcof_target_index}")
  endif()

  set(target_name "lcof_${safe_id}")

  # 不同文件规范化后同名时追加序号，避免 add_executable 因重名失败
  if(TARGET "${target_name}")
    string(APPEND target_name "_${lcof_target_index}")
  endif()

  add_executable("${target_name}" "${source_file}")
  set_target_properties("${target_name}" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)
endforeach()
