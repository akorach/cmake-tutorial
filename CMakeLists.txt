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

# ----------------------------------------------------------------------------------------------------------------------
# options
# ----------------------------------------------------------------------------------------------------------------------

# How options work:
# When an option line is added, it will be visible to the cmake system, including the GUI, and also in QtCreator
# To make it visible in the source code, we need to add it to the config file by writing #cmakedefine USE_MYMATH
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# config file: needed for passing the version number and options to the source code; Q: How do we do it at NI?
configure_file(MinimalistConfig.h.in MinimalistConfig.h)

# ----------------------------------------------------------------------------------------------------------------------
# target setup
# ----------------------------------------------------------------------------------------------------------------------

if(USE_MYMATH)
    # add the MathFunctions library
    add_subdirectory(MathFunctions)
    list(APPEND EXTRA_LIBS MathFunctions)
endif()

add_executable(${PROJECT} main.cpp)

# link libraries - we have to define an executable earlier for this to work
target_link_libraries(${PROJECT} PUBLIC ${EXTRA_LIBS})

# add the binary dir to the search path for include files, so that we will find the project config file
# add the library dir to the search path for include files
# comes after add_executable
target_include_directories(${PROJECT} PUBLIC "${PROJECT_BINARY_DIR}") # Q: Why is bin dir in ""?

# ----------------------------------------------------------------------------------------------------------------------
# install rules
# ----------------------------------------------------------------------------------------------------------------------

# allows for installing the project in a set location
install(TARGETS ${PROJECT} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# ----------------------------------------------------------------------------------------------------------------------
# testing
# ----------------------------------------------------------------------------------------------------------------------

enable_testing()

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
