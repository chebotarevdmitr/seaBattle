#pragma once
#include <vector>
#include <utility> // std::pair
#include <string>

enum class Orientation { Horizontal, Vertical };

// Модель корабля в игре
class Ship {
public:
    // Конструктор принимает имя, размер, стартовые координаты и ориентацию
    Ship(std::string name, int length, std::pair<int, int> start, Orientation direction);

    // Метод "выстрела" по координатам — возвращает true при попадании
    bool hit(int x, int y);

    // Проверка, потоплен ли корабль
    bool isSunk() const;

    // Получение всех координат корабля
    const std::vector<std::pair<int, int>>& getCoordinates() const;

    // Получение имени корабля
    const std::string& getName() const;

private:
    std::string name;                          // Название корабля
    int length;                                // Длина (кол-во палуб)
    std::vector<std::pair<int, int>> position; // Координаты каждой палубы
    std::vector<bool> hits;                    // Попадания по каждой палубе
};
