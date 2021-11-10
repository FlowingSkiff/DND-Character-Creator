add_subdirectory(Base)
set(creator_sources
    DescriptionTools.cpp
    Character.cpp
    EntityList.cpp
)
add_library(Creator ${creator_sources})
target_link_libraries(Creator 
    PUBLIC 
        CreatorBase
        project_options
        project_warnings
)
target_include_directories(Creator BEFORE
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)