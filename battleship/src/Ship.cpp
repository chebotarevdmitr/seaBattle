#include "../include/Ship.h"
#include <algorithm> // std::all_of

// Конструктор создаёт координаты корабля в зависимости от ориентации
Ship::Ship(std::string name, int length, std::pair<int, int> start, Orientation direction)
    : name(name), length(length), hits(length, false) {
    int x = start.first;
    int y = start.second;

    for (int i = 0; i < length; ++i) {
        if (direction == Orientation::Horizontal)
            position.push_back({x + i, y});
        else
            position.push_back({x, y + i});
    }
}

// Проверка попадания и отметка "попал"
bool Ship::hit(int x, int y) {
    for (size_t i = 0; i < position.size(); ++i) {
        if (position[i].first == x && position[i].second == y) {
            hits[i] = true;
            return true;
        }
    }
    return false;
}

// Возвращает true, если все палубы уничтожены
bool Ship::isSunk() const {
    return std::all_of(hits.begin(), hits.end(), [](bool h) { return h; });
}

// Возврат координат корабля
const std::vector<std::pair<int, int>>& Ship::getCoordinates() const {
    return position;
}

// Возврат имени
const std::string& Ship::getName() const {
    return name;
}
