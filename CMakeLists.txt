# ----------------------------------------------------------------------------------------------------------------------
# prelude
# ----------------------------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)

# set the project name and version
set (PROJECT "Minimalist")
project(${PROJECT} VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# ----------------------------------------------------------------------------------------------------------------------
# options
# ----------------------------------------------------------------------------------------------------------------------

# How options work:
# When an option line is added, it will be visible to the cmake system, including the GUI, and also in QtCreator
# To make it visible in the source code, we need to add it to the config file by writing #cmakedefine OPT_NAME

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# config file: needed for passing the version number and options to the source code
configure_file(MinimalistConfig.h.in MinimalistConfig.h)

# ----------------------------------------------------------------------------------------------------------------------
# target setup
# ----------------------------------------------------------------------------------------------------------------------

# Add the MathFunctions library.
# Includes the text of the lower-level CMakeList.
add_subdirectory(MathFunctions)

add_executable(${PROJECT} main.cpp)

# Link libraries to a target.
# Tells cmake where to look for source files of linked libs and fulfills usage reqirements of these libs.
# The used target must have been created before
target_link_libraries(${PROJECT} PUBLIC MathFunctions)

# Add the binary dir to the search path for include files, so that we will find the project config file.
# The used target must have been created before
target_include_directories(${PROJECT} PUBLIC "${PROJECT_BINARY_DIR}") # Q: Why is bin dir in ""?

# ----------------------------------------------------------------------------------------------------------------------
# install rules
# ----------------------------------------------------------------------------------------------------------------------

# allows for installing the project in a set location
install(TARGETS ${PROJECT} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/MinimalistConfig.h" DESTINATION include)

# use CPack to build an installer
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Minimalist_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Minimalist_VERSION_MINOR}")
include(CPack)

# ----------------------------------------------------------------------------------------------------------------------
# testing
# ----------------------------------------------------------------------------------------------------------------------

include(CTest)

# Does the application run?
# NAME - test name
# COMMAND - specify command line; here: project exec with arguments
add_test(NAME ApplicationRuns COMMAND ${PROJECT} 25)

# Does the usage message work?
add_test(NAME Usage COMMAND ${PROJECT})
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# define a function to simplify adding tests
function(test_run target arg expected)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${expected})
endfunction(test_run)

# run a bunch of result based tests
test_run(${PROJECT} 4 "4 is 2")
test_run(${PROJECT} 9 "9 is 3")
test_run(${PROJECT} 5 "5 is 2.236")
test_run(${PROJECT} 7 "7 is 2.645")
test_run(${PROJECT} 25 "25 is 5")
test_run(${PROJECT} -25 "-25 is [-nan|nan|0]")
test_run(${PROJECT} 0.0001 "0.0001 is 0.01")
