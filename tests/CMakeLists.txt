file(GLOB test_sources RELATIVE ${CMAKE_SOURCE_DIR}/tests *.cpp)
foreach(test ${test_sources})
    string(REPLACE ".cpp" "" testname ${test})
    add_executable(${testname} ${test})
    target_link_libraries(${testname} 
        PUBLIC 
            CreatorBase 
            ThirdParty
            project_options
            project_warnings
    )
    target_include_directories(${testname} BEFORE
        PUBLIC 
            ${CMAKE_SOURCE_DIR}/thirdparty/include 
            ${CMAKE_SOURCE_DIR}/include
    )
endforeach(test ${test_sources})
