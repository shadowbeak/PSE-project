cmake_minimum_required(VERSION 3.26)
project(PSE_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(PSE_project
        src/main.cpp
        src/tinystr.cpp
        src/tinyxml.cpp
        src/tinyxmlerror.cpp
        src/tinyxmlparser.cpp
        src/PrintSystemUtils.cpp
        src/Device.cpp
        src/Job.cpp
        src/PrintSystem.cpp
        src/TEST.cpp
        src/vdsv.cpp
)
