
include_directories(${Boost_INCLUDE_DIRS})
add_executable( echo_server ./echo_server.cpp )
target_link_libraries( echo_server ${Boost_LIBRARIES})