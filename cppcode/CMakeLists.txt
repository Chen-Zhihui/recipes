
cmake_minimum_required(VERSION 3.8)
project(cppcode)

set(BOOST_ROOT E:/local/boost.install.lib) # install prefix for boost
if(MSVC)
    add_compile_options(/W0)
    find_package(Boost)
    add_definitions( -D_WIN32_WINNT=0x0601 )
    #add_definitions( -DBOOST_ALL_DYN_LINK  ) # for shared boost libs
    link_directories(${Boost_LIBRARY_DIRS})
else()
    add_compile_options(-w)    
    find_package(Boost REQUIRED  
        filesystem
        system
        date_time
        regex
        # others
    )
endif()

add_subdirectory(stdcpp)
add_subdirectory(boost)