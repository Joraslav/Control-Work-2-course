cmake_minimum_required(VERSION 3.26.0)
project(Study VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(${PROJECT_NAME} main.cpp)

# Настраиваем Google Test
include(CTest)
enable_testing()

# Ищем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем тесты
add_executable(TestSmartPointer tests/Test_SmartPointer.cpp)
target_link_libraries(TestSmartPointer ${GTEST_LIBRARIES} pthread)

# Добавляем тесты в CTest
add_test(NAME TestSmartPointer COMMAND TestSmartPointer)
