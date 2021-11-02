file(GLOB creator_base_sources *.hpp *.h *.cpp)
add_library(CreatorBase ${creator_base_sources})
link_libraries(CreatorBase)