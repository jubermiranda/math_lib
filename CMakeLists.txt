cmake_minimum_required(VERSION 3.15)
project(math_lib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(math_lib
    src/rational.cxx
)

add_library(MathLib::math_lib ALIAS math_lib)

set_property(TARGET math_lib PROPERTY CXX_STANDARD 20)
set_property(TARGET math_lib PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(math_lib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

option(BUILD_TESTS "Build project tests (with gtest)" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# --- INSTALL AND EXPORT ---
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS math_lib
  EXPORT math_lib-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT math_lib-targets
  FILE        math_lib-targets.cmake
  NAMESPACE   MathLib::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/math_lib
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/math_lib-config-version.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)
