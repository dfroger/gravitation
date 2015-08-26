cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(GRAVITATION)
set(version 0.1.0)

# Use absolute rpath at install.
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# We depend on the m library.
find_library(M_LIBRARY m HINT /lib/x86_64-linux-gnu)

# Create library.
set(GRAVITATION_LIBRARY gravitation)
add_library(gravitation SHARED force.cxx)
target_link_libraries(gravitation ${M_LIBRARY})

# Install library.
install(
    TARGETS ${GRAVITATION_LIBRARY} 
    DESTINATION lib
    EXPORT GRAVITATION_LIBRARY
)

# Install header.
install(
    DIRECTORY gravitation
    DESTINATION include
)

# Place of gravitation ITK config files.
set(GRAVITATION_CONFIGDIR_FROM_PREFIX share/gravitation)
set(GRAVITATION_PREFIX_FROM_CONFIGDIR ../../)

# Install exports.
install(
    EXPORT GRAVITATION_LIBRARY
    DESTINATION ${GRAVITATION_CONFIGDIR_FROM_PREFIX}
)

# Make config file available in develop mode (build but no install)
export(
    TARGETS ${GRAVITATION_LIBRARY}
    FILE ${GRAVITATION_BINARY_DIR}/GRAVITATION_LIBRARY.cmake
)

# Generate configuration files.
configure_file(
    ${GRAVITATION_SOURCE_DIR}/itk_package_config/gravitation-config.cmake.in
    ${GRAVITATION_BINARY_DIR}/itk_package_config/gravitation-config.cmake @ONLY
)

# Generate configuration files version.
configure_file(
    ${GRAVITATION_SOURCE_DIR}/itk_package_config/gravitation-config-version.cmake.in
    ${GRAVITATION_BINARY_DIR}/gravitation-config-version.cmake @ONLY
)

# Generate configuration files version for develop mode.
configure_file(
    ${GRAVITATION_SOURCE_DIR}/itk_package_config/gravitation-config-develop.cmake.in
    ${GRAVITATION_BINARY_DIR}/gravitation-config.cmake @ONLY
)

# Install configuration files.
install(
    FILES ${GRAVITATION_BINARY_DIR}/itk_package_config/gravitation-config.cmake
    ${GRAVITATION_BINARY_DIR}/gravitation-config-version.cmake
    DESTINATION ${GRAVITATION_CONFIGDIR_FROM_PREFIX}
)
