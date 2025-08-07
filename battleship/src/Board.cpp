#include "../include/Board.h"
#include <iostream>
#include <set>         // Для хранения координат потопленных кораблей
#include <algorithm>   // Для std::all_of

// Конструктор: инициализируем пустое поле
Board::Board() {
    // ⚙️ Инициализируем поле пустыми ячейками '.'
    for (int y = 0; y < BOARD_SIZE; ++y)
        for (int x = 0; x < BOARD_SIZE; ++x)
            grid[y][x] = CELL_EMPTY;
}

// Размещение корабля на поле
bool Board::placeShip(const Ship& ship) {
    // Проверяем, не пересекается ли корабль с другими
    if (doesOverlap(ship))
        return false;

    // Проверяем каждую координату корабля
    for (const auto& [x, y] : ship.getCoordinates()) {
        if (!isValidPosition(x, y))
            return false;
        grid[y][x] = CELL_SHIP; // Корабль помечается 'S'
    }

    ships.push_back(ship);
    return true;
}

// Обработка выстрела по координатам
bool Board::fireAt(int x, int y) {
    // Проверяем корректность координат
    if (!isValidPosition(x, y))
        return false;

    // Проверяем попадание по кораблям
    for (auto& ship : ships) {
        if (ship.hit(x, y)) {
            grid[y][x] = CELL_HIT; // 🎯 Попадание
            return true;
        }
    }

    grid[y][x] = CELL_MISS; // 💨 Промах
    return false;
}

// Проверка: все ли корабли потоплены
bool Board::allShipsSunk() const {
    return std::all_of(ships.begin(), ships.end(), [](const Ship& ship) {
        return ship.isSunk();
    });
}

// Получение всех кораблей
const std::vector<Ship>& Board::getShips() const {
    return ships;
}

// Проверка пересечения кораблей
bool Board::doesOverlap(const Ship& newShip) const {
    for (const auto& coord : newShip.getCoordinates()) {
        int x = coord.first;
        int y = coord.second;
        if (!isValidPosition(x, y))
            return true;
        if (grid[y][x] == CELL_SHIP) // Проверка на пересечение
            return true;
    }
    return false;
}

// Проверка корректности позиции
bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// 🎨 Цветной вывод ячейки
void Board::printColoredCell(char cell, bool isPlayerBoard) const {
    switch(cell) {
        case CELL_SHIP: // Корабль
            if (isPlayerBoard) {
                std::cout << Color::GREEN << " S " << Color::RESET;
            } else {
                std::cout << Color::BLUE << " . " << Color::RESET; // Скрыто для врага
            }
            break;
        case CELL_HIT: // Попадание
            std::cout << Color::RED << " X " << Color::RESET;
            break;
        case CELL_MISS: // Промах
            std::cout << Color::CYAN << " O " << Color::RESET;
            break;
        case CELL_SUNK: // Потоплен
            std::cout << Color::MAGENTA << " D " << Color::RESET;
            break;
        default: // Пустая клетка
            std::cout << Color::BLUE << " . " << Color::RESET;
    }
}

// 🖥️ Метод отображения доски соперника
void Board::printEnemyBoard() const {
    // Выводим заголовки столбцов
    std::cout << "    ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << Color::WHITE << x << " " << Color::RESET;
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

    // Выводим доску с рамками
    std::cout << "  ┌";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << "───";
    std::cout << "─┐\n";

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << Color::WHITE << y << Color::RESET << " │";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            std::pair<int, int> pos = {x, y};
            char cell = grid[y][x];

            // ✅ Отображение по приоритету
            if (sunkCoords.count(pos)) {
                printColoredCell(CELL_SUNK);  // 🛑 Потопленный корабль
            } else if (cell == CELL_HIT) {
                printColoredCell(CELL_HIT);   // 🎯 Попадание
            } else if (cell == CELL_MISS) {
                printColoredCell(CELL_MISS);  // 💨 Промах
            } else {
                printColoredCell(CELL_EMPTY); // 🫥 Неизвестная область
            }
        }
        std::cout << "│\n";
    }
    
    std::cout << "  └";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << "───";
    std::cout << "─┘\n";
}

// 🎨 Метод отображения своей доски (с видимыми кораблями)
void Board::printPlayerBoard() const {
    // Выводим заголовки столбцов
    std::cout << "    ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << Color::WHITE << x << " " << Color::RESET;
    std::cout << "\n";

    // Выводим доску с рамками
    std::cout << "  ┌";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << "───";
    std::cout << "─┐\n";

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << Color::WHITE << y << Color::RESET << " │";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            char cell = grid[y][x];
            printColoredCell(cell, true); // true = своя доска
        }
        std::cout << "│\n";
    }
    
    std::cout << "  └";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << "───";
    std::cout << "─┘\n";
}