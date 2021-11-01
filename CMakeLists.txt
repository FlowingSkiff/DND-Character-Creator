cmake_minimum_required(VERSION 3.0.0)
project(MyDNDCreator VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()
link_libraries(stdc++fs tinyxml2 sqlite3 spdlog fmt)
include_directories(thirdparty/include $ENV{MSYS2INCLUDE} Creator Creator/Base Creator/Tools UI UI/Base)
find_package(wxWidgets REQUIRED COMPONENTS net core base html)
add_compile_definitions(SPDLOG_FMT_EXTERNAL)
add_compile_options(-DDOLOG -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wunused -Wcast-align -Woverloaded-virtual -Wsign-conversion -Wconversion -Wpedantic -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
include(${wxWidgets_USE_FILE})

IF(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O3)
endif(CMAKE_BUILD_TYPE MATCHES Release)

add_subdirectory(Creator)
add_subdirectory(thirdparty)
add_subdirectory(UI)

link_libraries(CreatorBase ThirdParty UI UI_BASE ${wxWidgets_LIBRARIES})

add_subdirectory(tests)

add_executable(XMLTags xmltagextractor.cpp)
add_executable(MyDNDCreator capp.cpp)
target_link_libraries(MyDNDCreator CreatorBase ThirdParty UI UI_BASE ${wxWidgets_LIBRARIES})
target_link_libraries(XMLTags CreatorBase ThirdParty)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
