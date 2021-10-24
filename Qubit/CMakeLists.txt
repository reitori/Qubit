#All source files
set(SOURCE_FILES main.cpp

)

#Create our target and additional include directories/libraries
add_library("QBTDLL" SHARED ${SOURCE_FILES})

target_precompile_headers

target_include_directories(${PROJECT_NAME} PRIVATE "vendors")
target_link_libraries(${PROJECT_NAME} PRIVATE "")