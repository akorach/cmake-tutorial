# ----------------------------------------------------------------------------------------------------------------------
# options
# ----------------------------------------------------------------------------------------------------------------------

option(USE_MYMATH "Use tutorial provided math implementation" ON)

# ----------------------------------------------------------------------------------------------------------------------
# target setup: code generation
# ----------------------------------------------------------------------------------------------------------------------

if(USE_MYMATH)

# Add an executable for generating a table of precomputed values for use in mysqrt.cpp
add_executable(MakeTable makeTable.cpp)

# Defines a custom command:
# Run the program specified in COMMAND (MakeTable) to generate output files specified in OUTPUT.
## 1. If any of the files defined in the OUTPUT are specified as input to the COMMAND,
## the COMMAND target is given a rule to generate the file at BUILD time.
## 2. If DEPENDS specifies any target (created by the add_custom_target(), add_executable(), or add_library() command),
## a target-level dependency is created to make sure the target is built before any target using this custom command.
## 3. Additionally, if the target is an executable or library a file-level dependency is created
## to cause the custom command to re-run whenever the target is recompiled.
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

endif()

# ----------------------------------------------------------------------------------------------------------------------
# target setup: library
# ----------------------------------------------------------------------------------------------------------------------

# Add the main library - lists the required sources
set(LIBNAME MathFunctions)
add_library(${LIBNAME} MathFunctions.cpp)

# Usage requirements
## States that anybody linking to MathFunctions needs to include the current source directory (i.e. MathFunctions),
## while MathFunctions itself doesn’t. So this can become an INTERFACE usage requirement.
## The inclusion happens automatically when the lib is linked to a target..
## INTERFACE means things that consumers require but the producer doesn’t.
target_include_directories(${LIBNAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if(USE_MYMATH)
    # library that just does sqrt
    add_library(SqrtLibrary STATIC mysqrt.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        )

    # state that we depend on our binary dir to find Table.h
    target_include_directories(SqrtLibrary PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

    # state that SqrtLibrary needs PIC when the default is shared libraries
      set_target_properties(SqrtLibrary PROPERTIES
                            POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
                            )

    target_link_libraries(${LIBNAME} PRIVATE SqrtLibrary)
endif()

# compile definitions - defines preprocessor directives (same as #cmakedefine in config files)
# define the symbol stating we are using the declspec(dllexport) when building on windows
target_compile_definitions(${LIBNAME} PRIVATE "EXPORTING_MYMATH")

# ----------------------------------------------------------------------------------------------------------------------
# install rules
# ----------------------------------------------------------------------------------------------------------------------

install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)
