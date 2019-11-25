set(LIBNAME MathFunctions)
add_library(${LIBNAME} mysqrt.cpp)

# Usage requirements
# States that anybody linking to MathFunctions needs to include the current source directory (i.e. MathFunctions),
# while MathFunctions itself doesn’t. So this can become an INTERFACE usage requirement. The inclusion is automatic.
# INTERFACE means things that consumers require but the producer doesn’t
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# include a module & check for the existence of symbols in the system
include(CheckSymbolExists)
set(CMAKE_REQUIRED_LIBRARIES "m") # Q: Why is this set to "m"?
check_symbol_exists(log "math.h" HAS_LOG)
check_symbol_exists(exp "math.h" HAS_EXP)

if(HAS_LOG AND HAS_EXP)
    target_compile_definitions(${LIBNAME} PRIVATE "HAS_LOG" "HAS_EXP")
endif()

# install rules
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)
