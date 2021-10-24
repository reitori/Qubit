#Compatible versions of CMake 3.7-3.21
cmake_minimum_required(VERSION 3.7)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSOIN ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
	cmake_policy(VERSION 3.21)
endif()

project(Qubit VERSION 1.0 DESCRIPTION "A Physics Simulator" LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} )

add_subdirectory(Qubit)
target_link_libraries(${PROJECT_NAME} PRIVATE "QBTDLL")