cmake_minimum_required(VERSION 3.31)
project(snake_who_like_eat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(snake_who_like_eat)
include_directories(snake_who_like_eat/debug)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64/lib/cmake/")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(snake_who_like_eat
        snake_who_like_eat/commhelper.cpp
        snake_who_like_eat/commhelper.h
        snake_who_like_eat/constant.h
        snake_who_like_eat/food.cpp
        snake_who_like_eat/food.h
        snake_who_like_eat/gamecontrol.cpp
        snake_who_like_eat/gamecontrol.h
        snake_who_like_eat/gamewindow.cpp
        snake_who_like_eat/gamewindow.h
        snake_who_like_eat/main.cpp
        snake_who_like_eat/mainwindow.cpp
        snake_who_like_eat/mainwindow.h
        snake_who_like_eat/snake.cpp
        snake_who_like_eat/snake.h
        snake_who_like_eat/ui_gamewindow.h
        snake_who_like_eat/ui_mainwindow.h
        snake_who_like_eat/unit.cpp
        snake_who_like_eat/unit.h)

target_link_libraries(snake_who_like_eat
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)