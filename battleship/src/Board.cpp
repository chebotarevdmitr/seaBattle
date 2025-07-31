#include "../include/Board.h"
#include <iostream>

// Инициализация поля: все ячейки — пустые
Board::Board() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            grid[i][j] = '.';
}

// Проверка, можно ли разместить корабль
bool Board::placeShip(const Ship& ship) {
    if (doesOverlap(ship))
        return false;

    for (auto [x, y] : ship.getCoordinates()) {
        if (!isValidPosition(x, y))
            return false;
        grid[y][x] = 'S'; // Обозначим корабль буквой S
    }

    ships.push_back(ship);
    return true;
}

// Стреляем по координате (x, y)
bool Board::fireAt(int x, int y) {
    if (!isValidPosition(x, y))
        return false;

    for (auto& ship : ships) {
        if (ship.hit(x, y)) {
            grid[y][x] = 'X'; // Попадание
            return true;
        }
    }

    grid[y][x] = 'O'; // Промах
    return false;
}

// Проверяем, все ли корабли потоплены
bool Board::allShipsSunk() const {
    for (const auto& ship : ships)
        if (!ship.isSunk())
            return false;
    return true;
}

// Получаем список кораблей
const std::vector<Ship>& Board::getShips() const {
    return ships;
}

// Проверка на пересечение корабля с уже размещёнными
bool Board::doesOverlap(const Ship& newShip) const {
    for (const auto& coord : newShip.getCoordinates()) {
        if (!isValidPosition(coord.first, coord.second))
            return true;
        if (grid[coord.second][coord.first] == 'S')
            return true;
    }
    return false;
}

// Проверка, в пределах ли координаты
bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// Вывод поля на экран (отладочный)
void Board::printBoard() const {
    std::cout << "  ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << x << " ";
    std::cout << "\n";

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << y << " ";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << "\n";
    }
}
