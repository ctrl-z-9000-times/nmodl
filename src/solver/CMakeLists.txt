# =============================================================================
# Copy necessary files to build directory
# =============================================================================
# partial_piv_lu
file(GLOB NMODL_PARTIAL_PIV_LU_API_FILES "${CMAKE_CURRENT_SOURCE_DIR}/partial_piv_lu/*")
file(COPY ${NMODL_PARTIAL_PIV_LU_API_FILES} DESTINATION ${CMAKE_BINARY_DIR}/include/partial_piv_lu/)
# Eigen
file(COPY ${NMODL_PROJECT_SOURCE_DIR}/ext/eigen/Eigen DESTINATION ${CMAKE_BINARY_DIR}/include/)

# =============================================================================
# Install solver headers and eigen from include
# =============================================================================
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION ${NMODL_INSTALL_DIR_SUFFIX}include)
