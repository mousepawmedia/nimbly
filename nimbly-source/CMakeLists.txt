# CMake Config (MousePaw Media Build System)
# Version: 3.2.0

# CHANGE: Name your project here
project("Nimbly")

# Specify the version being used.
cmake_minimum_required(VERSION 3.8)

# Import user-specified library path configuration
message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# CHANGE: Specify output binary name
set(TARGET_NAME "nimbly")

# SELECT: Project artifact type
set(ARTIFACT_TYPE "library")
#set(ARTIFACT_TYPE "executable")

# CHANGE: Find dynamic library dependencies.

# CHANGE: Include headers of dependencies.
set(INCLUDE_LIBS
    ${GOLDILOCKS_DIR}/include
    ${IOSQUEAK_DIR}/include
    ${ARCTICTERN_DIR}/include
    ${EVENTPP_DIR}/include
)

# CHANGE: Include files to compile.
set(FILES
    include/nimbly/core/constants.hpp
    include/nimbly/core/flex.hpp

    include/nimbly/tests/flexarray_tests.hpp
    include/nimbly/tests/flexqueue_tests.hpp
    include/nimbly/tests/flexstack_tests.hpp
    include/nimbly/tests/pool_tests.hpp

    include/nimbly/flexarray.hpp
    include/nimbly/flexqueue.hpp
    include/nimbly/flexstack.hpp
    include/nimbly/pool.hpp

    src/tests/flexarray_tests.cpp
    src/tests/flexqueue_tests.cpp
    src/tests/flexstack_tests.cpp
    src/tests/pool_tests.cpp

    # EXPERIMENTAL

    #include/nimbly/experimental/flexbit.hpp
    #include/nimbly/experimental/rigid_stack.hpp

    #include/nimbly/experimental/tests/flexbit_tests.hpp

    #src/experimental/tests/flexbit_tests.cpp
)

# CHANGE: Link against dependencies.
set(LINK_LIBS
    ${GOLDILOCKS_DIR}/lib/libgoldilocks.a
    ${IOSQUEAK_DIR}/lib/libiosqueak.a
)

# Imports build script. (Change if necessary to point to build.cmake)
include(${CMAKE_HOME_DIRECTORY}/../build_system/build.cmake)
