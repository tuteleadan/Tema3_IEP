cmake_minimum_required(VERSION 3.2)
project(Tema3)

if(CMAKE_VERSION GREATER "3.1.2")
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	
else()
	
	if(CMAKE_COMPILER_IS_GNUCXX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
	endif()
endif()

add_executable(Tema3 Tema3.cpp)