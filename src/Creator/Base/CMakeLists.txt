find_package(Threads)
set(creator_base_sources
    CreatorFactory.cpp
    SQBaseObject.cpp
    SQObject.cpp
    StringTools.cpp
    XMLTools.cpp
)
add_library(CreatorBase ${creator_base_sources})
target_include_directories(CreatorBase BEFORE
        PUBLIC 
            ${CMAKE_SOURCE_DIR}/include 
            ${CMAKE_SOURCE_DIR}/thirdparty/include
)
target_compile_definitions(CreatorBase PUBLIC SPDLOG_FMT_EXTERNAL)
target_link_libraries(CreatorBase 
    PUBLIC 
        Threads::Threads 
        stdc++fs 
        tinyxml2 
        sqlite3 
        spdlog 
        fmt
        project_options
        project_warnings
)