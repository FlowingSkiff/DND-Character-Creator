add_subdirectory(Base)
file(GLOB ui_sources *.h *.hpp *.cpp) 
add_library(UI ${ui_sources})
set_target_properties(UI PROPERTIES LINKER_LANGUAGE CXX)