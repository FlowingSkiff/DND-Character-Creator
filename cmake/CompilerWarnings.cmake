function(set_project_warnings project_name)
    set (GCC_WARNINGS
        -DDOLOG 
        -Wall 
        -Wextra 
        -Wshadow 
        -Wnon-virtual-dtor 
        -pedantic 
        -Wold-style-cast 
        -Wunused 
        -Wcast-align 
        -Woverloaded-virtual 
        -Wsign-conversion 
        -Wconversion 
        -Wpedantic 
        -Wmisleading-indentation 
        -Wduplicated-cond 
        -Wduplicated-branches 
        -Wlogical-op 
        -Wnull-dereference 
        -Wuseless-cast 
        -Wdouble-promotion 
        -Wformat=2
    )

    set(PROJECT_WARNINGS ${GCC_WARNINGS})

    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
endfunction()