cmake_minimum_required(VERSION 3.5)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_CMAKE_VAR $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(TRAVIS_BUILD_CMAKE_VAR 999)
endif()

project(ip_filter VERSION 0.0.${TRAVIS_BUILD_CMAKE_VAR})

message("Version ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}")

include(CMakeLists-GTest.cmake)

configure_file(version.h.in version.hpp @ONLY)

add_executable(ip_filter "main.cpp")
add_library(ip_filter_lib "lib.cpp")
add_executable(tests_default tests_default.cpp)

set_target_properties(ip_filter ip_filter_lib tests_default PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)
target_link_libraries(tests_default 
    gtest_main
    ip_filter_lib
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "Felix Palta <my@email.com>")

include(CPack)

enable_testing()

add_test(tests_default tests_default)
