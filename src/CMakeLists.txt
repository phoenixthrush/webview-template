cmake_minimum_required(VERSION 3.16)
project(example LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG master)
FetchContent_MakeAvailable(webview)

add_executable(example WIN32)
target_sources(example PRIVATE
    main.c
    ${CMAKE_BINARY_DIR}/index.modified.c
)
target_link_libraries(example PRIVATE webview::core_static)

if(APPLE)
  enable_language(OBJC)
  set_source_files_properties(main.c PROPERTIES LANGUAGE OBJC)
  find_library(COCOA_LIBRARY Cocoa)
  target_link_libraries(example PRIVATE ${COCOA_LIBRARY})
endif()
