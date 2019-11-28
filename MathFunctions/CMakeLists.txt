# Add an executable for generating a table of precomputed values for use in mysqrt.cpp
add_executable(MakeTable makeTable.cpp)

# Defines a custom command:
# Run the program specified in COMMAND (MakeTable) to generate output files specified in OUTPUT.
## 1. If any of the files defined in the OUTPUT are specified as input to the COMMAND,
## the COMMAND target is given a rule to generate the file at build time.
## 2. If DEPENDS specifies any target (created by the add_custom_target(), add_executable(), or add_library() command),
## a target-level dependency is created to make sure the target is built before any target using this custom command.
## 3. Additionally, if the target is an executable or library a file-level dependency is created
## to cause the custom command to re-run whenever the target is recompiled.
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

# Add the main library - lists the required sources
set(LIBNAME MathFunctions)
add_library(${LIBNAME} mysqrt.cpp
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
            )

# Usage requirements
## States that anybody linking to MathFunctions needs to include the current source directory (i.e. MathFunctions),
## while MathFunctions itself doesn’t. So this can become an INTERFACE usage requirement. The inclusion is automatic.
## INTERFACE means things that consumers require but the producer doesn’t
target_include_directories(${LIBNAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
    )

# install rules
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)
