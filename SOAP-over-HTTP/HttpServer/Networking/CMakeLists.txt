# Set the source files in the current directory (folder with .h and .cpp files)
set(SOURCES
    HttpsServer.h
    HttpsServer.cpp
)

# Create a library or executable target for the source files
add_library(Networking ${SOURCES})
