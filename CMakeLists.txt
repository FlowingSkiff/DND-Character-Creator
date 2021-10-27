cmake_minimum_required(VERSION 3.0.0)
project(XMLTools VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()
link_libraries(stdc++fs tinyxml2 sqlite3 spdlog fmt)
include_directories(thirdparty/include $ENV{MSYS2INCLUDE} Creator Creator/Base Creator/Tools)

add_compile_definitions(SPDLOG_FMT_EXTERNAL)
add_compile_options(-DDOLOG -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wcast-align -Woverloaded-virtual -Wsign-conversion -Wconversion -Wpedantic -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
IF(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O3)
endif(CMAKE_BUILD_TYPE MATCHES Release)

add_subdirectory(Creator)
add_subdirectory(thirdparty)

link_libraries(CreatorBase CreatorTools ThirdParty)

add_executable(XMLTags xmltagextractor.cpp)
target_link_libraries(XMLTags CreatorBase CreatorTools ThirdParty)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
