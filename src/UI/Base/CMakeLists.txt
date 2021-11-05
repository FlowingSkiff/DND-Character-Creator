set(ui_base_sources
    baseProject.cpp
)
add_library(UI_BASE ${ui_base_sources})
target_include_directories(UI_BASE BEFORE
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)
set_target_properties(UI_BASE PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(UI_BASE 
    PUBLIC 
        ${wxWidgets_LIBRARIES}
        project_options
        project_warnings
)