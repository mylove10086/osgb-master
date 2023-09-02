include(CMakeFindDependencyMacro)
find_dependency(Threads)
find_dependency(glad)
include("${CMAKE_CURRENT_LIST_DIR}/glfw3Targets.cmake")
