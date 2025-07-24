cmake_minimum_required(VERSION 3.15)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическое добавление заголовков в IDE (Visual Studio, CLion и др.)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Исходные файлы (лучше явно указать, чем использовать GLOB)
file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*/*/*.cpp"
)

# Заголовочные файлы (для IDE)
file(GLOB_RECURSE HEADER_FILES 
    "${CMAKE_SOURCE_DIR}/include/*.h"
    "${CMAKE_SOURCE_DIR}/include/*/*.h"
    "${CMAKE_SOURCE_DIR}/include/*/*/*.h"
)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/Release)

add_executable(Snake ${SRC_FILES} ${HEADER_FILES})

# Подключаем заголовки
target_include_directories(Snake PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Загрузка SFML через FetchContent
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1 
)

FetchContent_MakeAvailable(SFML)

# Линкуем SFML
target_link_libraries(Snake PRIVATE 
    sfml-main
    sfml-graphics 
    sfml-window 
    sfml-system
    sfml-audio
)

if(WIN32)
    set_target_properties(Snake PROPERTIES
        WIN32_EXECUTABLE "$<CONFIG:Release>"
    )
endif()

# Для Windows: статическая линковка Runtime библиотек
if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()