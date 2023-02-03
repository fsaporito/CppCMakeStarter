include_guard()

function(create_optimization_flags USE_LTO OPTIMIZATION_SETTINGS)
    if(NOT CMAKE_BUILD_TYPE)
        message("-- WARNING: Build type not defined. Using 'Debug' as Default")
        set(CMAKE_BUILD_TYPE Debug) # set in this scope
        set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} PARENT_SCOPE) # set in the parent scope
    endif(NOT CMAKE_BUILD_TYPE)

    if(USE_LTO)
        set(LTO_FLAG -flto)
        message(STATUS "LTO Enabled")
    else()
        set(LTO_FLAG "")
        message(STATUS "LTO NOT enabled")
    endif(USE_LTO)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(OPTIMIZATION_SETTINGS -O3 ${FLAG_LTO} PARENT_SCOPE)
        add_definitions(-DNDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(OPTIMIZATION_SETTINGS -Og -g PARENT_SCOPE)
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        set(OPTIMIZATION_SETTINGS -Os ${LTO_FLAG} PARENT_SCOPE)
        add_definitions(-DNDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(OPTIMIZATION_SETTINGS -O2 -g ${LTO_FLAG} PARENT_SCOPE)
        add_definitions(-DNDEBUG)
    else()
        message(FATAL_ERROR "Invalid build type specified: " ${CMAKE_BUILD_TYPE})
    endif()
endfunction()