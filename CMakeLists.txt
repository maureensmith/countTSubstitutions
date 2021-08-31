cmake_minimum_required(VERSION 3.0)
#project(countTSubstitutions)
# Project name and a few useful settings. Other commands can pick up the results
project(countTSubstitutions
        VERSION 1.0
        DESCRIPTION "For 4SU analysis: Count the modification per read at positions with wild type T"
        LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory

#if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_CXX_STANDARD 17)



    #SET(CMAKE_BUILD_TYPE Debug)


    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    #TODO include(CTest)


    # Docs only available if this is the main app
#TODO
#    find_package(Doxygen)
#    if(Doxygen_FOUND)
#        add_subdirectory(docs)
#    else()
#        message(STATUS "Doxygen not found, not building docs")
#    endif()
#endif()

# The compiled library code is here
add_subdirectory(src)

add_executable(countTSubstitutionsProg
        src/main.cpp
        # Was made to test if mapping paired end reads in one SAM file gives the same result
        #mime_io_oneSAM.cpp
        #mime_io_oneSAM.hpp
        )

target_link_libraries(countTSubstitutionsProg countTSubstitutions)

# The executable code is here
#add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
#if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
#TODO    add_subdirectory(tests)
#endif()



