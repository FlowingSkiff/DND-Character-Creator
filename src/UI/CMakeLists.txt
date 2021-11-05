add_subdirectory(Base)
file(GLOB ui_sources 
    primativeDesign.cpp
) 
add_library(UI ${ui_sources})
set_target_properties(UI PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(UI BEFORE 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include 
        Base
)
target_link_libraries(UI 
    PUBLIC 
        UI_BASE
        ${wxWidgets_LIBRARIES}
        project_options
        project_warnings 
        Creator 
)