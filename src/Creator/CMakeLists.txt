add_subdirectory(Base)
file(GLOB creator_sources *.cpp)
add_library(Creator ${creator_sources})
link_libraries(Creator)