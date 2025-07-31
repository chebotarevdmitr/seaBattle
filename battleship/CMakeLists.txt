cmake_minimum_required(VERSION 3.10)
project(SeaBattle)

# Включаем поддержку C++17 (или выше)
set(CMAKE_CXX_STANDARD 17)

# Подключаем vcpkg toolchain, если используется отдельно
# Можно оставить пустым — CMake получит путь через аргумент при запуске

# Добавляем include директорию
include_directories(include)

# Собираем все исходники
file(GLOB SOURCES src/*.cpp)

# Создаём исполняемый файл
add_executable(main ${SOURCES})

# Если подключаешь внешние библиотеки через vcpkg:
# find_package(glfw3 CONFIG REQUIRED)
# target_link_libraries(main PRIVATE glfw)
