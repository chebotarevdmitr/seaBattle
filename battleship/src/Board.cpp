#include "../include/Board.h"
#include <iostream>
#include <set>         // Для хранения координат потопленных кораблей
#include <algorithm>   // Для std::all_of

Board::Board() {
    // ⚙️ Инициализируем поле пустыми ячейками '.'
    for (int y = 0; y < BOARD_SIZE; ++y)
        for (int x = 0; x < BOARD_SIZE; ++x)
            grid[y][x] = '.';
}

bool Board::placeShip(const Ship& ship) {
    if (doesOverlap(ship))
        return false;

    for (const auto& [x, y] : ship.getCoordinates()) {
        if (!isValidPosition(x, y))
            return false;
        grid[y][x] = 'S'; // Корабль помечается 'S', но скрыт при отображении
    }

    ships.push_back(ship);
    return true;
}

bool Board::fireAt(int x, int y) {
    if (!isValidPosition(x, y))
        return false;

    for (auto& ship : ships) {
        if (ship.hit(x, y)) {
            grid[y][x] = 'X'; // 🎯 Попадание
            return true;
        }
    }

    grid[y][x] = 'O'; // 💨 Промах
    return false;
}

bool Board::allShipsSunk() const {
    return std::all_of(ships.begin(), ships.end(), [](const Ship& ship) {
        return ship.isSunk();
    });
}

const std::vector<Ship>& Board::getShips() const {
    return ships;
}

bool Board::doesOverlap(const Ship& newShip) const {
    for (const auto& coord : newShip.getCoordinates()) {
        int x = coord.first;
        int y = coord.second;
        if (!isValidPosition(x, y))
            return true;
        if (grid[y][x] == 'S') // Проверка на пересечение
            return true;
    }
    return false;
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// 🖥️ Метод отображения поля соперника с символами X, O, D и . — скрытая логика
void Board::printBoard() const {
    std::cout << "  ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << x << " ";
    std::cout << "\n";

    // 🔍 Собираем координаты потопленных кораблей
    std::set<std::pair<int, int>> sunkCoords;
    for (const auto& ship : ships) {
        if (ship.isSunk()) {
            for (const auto& coord : ship.getCoordinates()) {
                sunkCoords.insert(coord);
            }
        }
    }

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << y << " ";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            std::pair<int, int> pos = {x, y};
            char cell = grid[y][x];

            // ✅ Отображение по приоритету
            if (sunkCoords.count(pos)) {
                std::cout << "D ";  // 🛑 Потопленный корабль
            } else if (cell == 'X') {
                std::cout << "X ";  // 🎯 Попадание
            } else if (cell == 'O') {
                std::cout << "O ";  // 💨 Промах
            } else {
                std::cout << ". ";  // 🫥 Неизвестная область
            }
        }
        std::cout << "\n";
    }
}
