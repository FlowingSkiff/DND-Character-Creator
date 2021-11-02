file(GLOB ui_base_sources *.h *.hpp *.cpp)
add_library(UI_BASE ${ui_base_sources})
set_target_properties(UI_BASE PROPERTIES LINKER_LANGUAGE CXX)
link_libraries(UI_BASE)