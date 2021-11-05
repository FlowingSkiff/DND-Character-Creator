cmake_minimum_required(VERSION 3.10.0)
project(MyDNDCreator VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)
enable_testing()

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)


find_package(wxWidgets REQUIRED COMPONENTS html core base net)
include(${wxWidgets_USE_FILE})

IF(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O3)
endif(CMAKE_BUILD_TYPE MATCHES Release)

add_subdirectory(thirdparty)
add_subdirectory(src)


add_subdirectory(tests)

add_executable(MyDNDCreator capp.cpp)
target_link_libraries(MyDNDCreator 
    PUBLIC 
        Creator 
        ThirdParty 
        UI
        project_options
        project_warnings
        ${wxWidgets_LIBRARIES}
)
target_include_directories(MyDNDCreator BEFORE
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/UI/Base
)

add_executable(XMLTags xmltagextractor.cpp)
target_link_libraries(XMLTags 
    PUBLIC 
        ThirdParty 
        Creator
        project_options
        project_warnings
)
target_include_directories(XMLTags BEFORE
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)

add_custom_command(TARGET MyDNDCreator PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/docs/ $<TARGET_FILE_DIR:MyDNDCreator>/docs
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
