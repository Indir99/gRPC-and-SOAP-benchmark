cmake_minimum_required(VERSION 3.5)

project(HttpClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (XercesC REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
# Add the include directories for libasio
#include_directories(/usr/include/xercesc)
#include_directories(/usr/local/include/boost)
#include_directories(/usr/local/include/asio)

add_subdirectory(Networking)

add_executable(HttpClient main.cpp)

target_link_libraries(HttpClient PRIVATE Networking XercesC::XercesC OpenSSL::SSL)


install(TARGETS HttpClient
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
