cmake_minimum_required(VERSION 3.10)
project(Cryptopals-Challenges
		VERSION 0.1
		DESCRIPTION "My solutions to the cryptopals challenges"
		LANGUAGES CXX)

# Only supported build type is debug
if(NOT DEFINED ${CMAKE_BUILD_TYPE})
	set(CMAKE_BUILD_TYPE Debug)
endif()

if(NOT (${CMAKE_BUILD_TYPE} STREQUAL Debug))
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

# Target C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -g")

# Add library target
add_library(cryptopals SHARED src/Utils.cpp)
target_include_directories(cryptopals PUBLIC include)

# Add unit tests executable target
add_executable(unit-test tests/main.cpp)
target_link_libraries(unit-test PRIVATE cryptopals)
