#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES
    main.cpp
    Client.h
    Client.cpp
    ClientInfo.h
    ClientInfo.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
        myproto
)
