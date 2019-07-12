cmake_minimum_required(VERSION 3.2)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_CMAKE_VAR $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(TRAVIS_BUILD_CMAKE_VAR 999)
endif()

project(MUH_PROJECT VERSION 0.0.${TRAVIS_BUILD_CMAKE_VAR})

message("Version ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}")

include(CMakeLists-GTest.cmake)

configure_file(version.h.in version.hpp @ONLY)

add_executable(MUH_PROJECT_cli "main.cpp")
add_library(MUH_PROJECT "lib.cpp")
add_executable(tests_default tests_default.cpp)

set_target_properties(MUH_PROJECT_cli MUH_PROJECT tests_default PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(MUH_PROJECT
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(MUH_PROJECT_cli PRIVATE
    MUH_PROJECT
)
target_link_libraries(tests_default 
    gtest_main
    MUH_PROJECT
)

if (MSVC)
    target_compile_options(MUH_PROJECT_cli PRIVATE
        /W4
    )
    target_compile_options(MUH_PROJECT PRIVATE
        /W4
    )
else ()
    target_compile_options(MUH_PROJECT_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(MUH_PROJECT PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS MUH_PROJECT_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "Felix Palta <my@email.com>")

include(CPack)

enable_testing()

add_test(tests_default tests_default)
