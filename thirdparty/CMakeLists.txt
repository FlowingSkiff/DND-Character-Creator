include_directories(include)
file(GLOB_RECURSE thirdparty_sources *.hpp *.h *.cpp)
add_library(ThirdParty ${thirdparty_sources})
set_target_properties(ThirdParty PROPERTIES LINKER_LANGUAGE CXX)