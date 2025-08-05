cmake_minimum_required(VERSION 3.31)
project(snake_who_like_eat)

set(CMAKE_CXX_STANDARD 20)

# 启用Qt自动处理。这将自动为带有Q_OBJECT宏的头文件运行moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 告诉CMake到哪里找Qt库，确保路径正确
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/msvc2022_64/lib/cmake/")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# 定义所有源文件和需要moc处理的头文件
set(PROJECT_SOURCES
        snake_who_like_eat/src/commhelper.cpp
        snake_who_like_eat/src/food.cpp
        snake_who_like_eat/src/gamecontrol.cpp
        snake_who_like_eat/src/gamewindow.cpp
        snake_who_like_eat/src/main.cpp
        snake_who_like_eat/src/mainwindow.cpp
        snake_who_like_eat/src/snake.cpp
        snake_who_like_eat/src/unit.cpp
)

# 明确列出UI文件和带有Q_OBJECT宏的头文件，让CMake知道需要处理它们
set(PROJECT_HEADERS
        snake_who_like_eat/include/commhelper.h
        snake_who_like_eat/include/food.h
        snake_who_like_eat/include/gamecontrol.h
        snake_who_like_eat/include/gamewindow.h
        snake_who_like_eat/include/mainwindow.h
        snake_who_like_eat/include/snake.h
        snake_who_like_eat/include/unit.h
)

set(PROJECT_UIS
        snake_who_like_eat/gamewindow.ui
        snake_who_like_eat/mainwindow.ui
)

# 创建可执行文件，包含所有源文件、头文件和UI文件
add_executable(snake_who_like_eat
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UIS}
)

# 设置头文件搜索路径
# 这里包含 snake_who_like_eat 目录，因为源文件都在这里
# 以及 include 目录，因为头文件都在这里
target_include_directories(snake_who_like_eat PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/snake_who_like_eat
        ${CMAKE_CURRENT_SOURCE_DIR}/snake_who_like_eat/include
)

# 链接Qt库
target_link_libraries(snake_who_like_eat
        Qt6::Widgets
)