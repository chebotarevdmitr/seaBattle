# 🚢 SeaBattle — игра "Морской бой" на C++

Проект реализует классическую игру "Морской бой" с использованием C++, GLFW и OpenGL. Цель — создать обучающий проект с графическим интерфейсом, реалистичной логикой и возможной сетевой интеграцией.

## 📦 Структура проекта

┌──(dmitriy㉿kali)-[~/my_repoz/seaBattle]
└─$ ls -all
total 16
drwxrwxr-x  4 dmitriy dmitriy 4096 Jul 30 20:55 .
drwxrwxr-x 12 dmitriy dmitriy 4096 Jul 28 21:08 ..
drwxrwxr-x  8 dmitriy dmitriy 4096 Jul 30 20:35 .git
-rw-rw-r--  1 dmitriy dmitriy    0 Jul 30 20:55 .gitignore
-rw-rw-r--  1 dmitriy dmitriy    0 Jul 30 20:55 README.md
drwxrwxr-x  7 dmitriy dmitriy 4096 Jul 30 20:55 battleship

┌──(dmitriy㉿kali)-[~/my_repoz/seaBattle]
└─$ tree
.
├── README.md
└── battleship
    ├── CMakeLists.txt
    ├── assets
    ├── include
    │   ├── Board.h
    │   ├── Game.h
    │   └── Ship.h
    ├── src
    │   ├── Board.cpp
    │   ├── Game.cpp
    │   ├── Ship.cpp
    │   └── main.cpp
    ├── tests
    │   └── test_logic.cpp
    └── utils
        └── helpers.cpp

7 directories, 11 files

## 🛠️ Технологии

- C++
- GLFW (через vcpkg)
- OpenGL
- CMake
- Git & GitHub

## 🚀 Сборка проекта

```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE="$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .
./main

---

## 🧰 Установка зависимостей через vcpkg

Перед началом работы убедитесь, что установлен [vcpkg](https://github.com/microsoft/vcpkg):

```bash
# Клонирование и установка vcpkg
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh

# Добавление в PATH (опционально)
echo 'export PATH="$HOME/vcpkg:$PATH"' >> ~/.bashrc
source ~/.bashrc

📥 Установка зависимостей
Убедитесь, что установлен vcpkg, 

bash
vcpkg install glfw3 glm glew

✍️ Автор
Dmitriy — обучающийся системный разработчик, энтузиаст Linux, автоматизации и графического программирования

