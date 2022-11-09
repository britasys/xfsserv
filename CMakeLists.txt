cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

option(APP_BUILD_SAMPLES "build samples" OFF)
option(APP_BUILD_TESTS "build tests" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#project name
set(PROJECT_NAME xfs_serv)

# app directories
set(APP_TESTS_DIR ./tests)
set(APP_SAMPLES_DIR ./samples)
set(APP_SOURCE_DIR ./src)

# project include directories
set(APP_INCLUDE_DIRS ${APP_SOURCE_DIR}
                     ${APP_SOURCE_DIR}/common/
                     ${APP_SOURCE_DIR}/xfs/
                     ${APP_SOURCE_DIR}/xfs/common
                     ${APP_SOURCE_DIR}/xfs/common/xfs_headers)

# project source files
file(GLOB_RECURSE APP_SOURCE_FILES CONFIGURE_DEPENDS ${APP_SOURCE_DIR}/*.cpp ${APP_SOURCE_DIR}/*.hpp)

# project
project(${PROJECT_NAME} VERSION 1.0)

# build project
add_compile_options(
   $<$<CONFIG:>:/MT>
   $<$<CONFIG:Debug>:/MTd>
   $<$<CONFIG:Release>:/MT>)
   
add_executable(${PROJECT_NAME} ${APP_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${APP_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${APP_SOURCE_DIR}/xfs/lib)

# tests
if(APP_BUILD_TESTS)

    # googletest
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    set(TEST_PROJECTS gtests)
    foreach(TEST_PROJECT ${TEST_PROJECTS})
        project(${TEST_PROJECT} VERSION 1.0)
        add_compile_options(
            $<$<CONFIG:>:/MT>
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
        add_executable(${TEST_PROJECT} ${APP_TESTS_DIR}/${TEST_PROJECT}.cpp)
        target_link_directories(${PROJECT_NAME} PRIVATE ${APP_SOURCE_DIR}/xfs/lib)
        target_include_directories(${PROJECT_NAME} PRIVATE ${APP_INCLUDE_DIRS})
        target_link_libraries(${TEST_PROJECT} GTest::gtest_main)
        include(GoogleTest)
        gtest_discover_tests(${TEST_PROJECT})
    endforeach()
endif(APP_BUILD_TESTS)