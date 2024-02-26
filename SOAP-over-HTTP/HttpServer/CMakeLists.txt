cmake_minimum_required(VERSION 3.5)

project(HttpServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (XercesC REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(Networking)

add_executable(HttpServer main.cpp)

target_link_libraries(HttpServer PRIVATE Networking XercesC::XercesC OpenSSL::SSL)

install(TARGETS HttpServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
