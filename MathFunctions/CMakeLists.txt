set(LIBNAME MathFunctions)
add_library(${LIBNAME} mysqrt.cpp)

# Usage requirements
# States that anybody linking to MathFunctions needs to include the current source directory (i.e. MathFunctions),
# while MathFunctions itself doesn’t. So this can become an INTERFACE usage requirement. The inclusion is automatic.
# INTERFACE means things that consumers require but the producer doesn’t
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# install rules
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES mysqrt.h DESTINATION include)
