#include "../include/Board.h"
#include <iostream>
#include <set>         // Для хранения координат потопленных кораблей
#include <algorithm>   // Для std::all_of

Board::Board() {
    // ⚙️ Инициализация: всё поле заполнено '.'
    for (int y = 0; y < BOARD_SIZE; ++y)
        for (int x = 0; x < BOARD_SIZE; ++x)
            grid[y][x] = '.';
}

bool Board::placeShip(const Ship& ship) {
    // Проверка пересечений перед установкой
    if (doesOverlap(ship))
        return false;

    for (const auto& [x, y] : ship.getCoordinates()) {
        if (!isValidPosition(x, y))
            return false;
        grid[y][x] = 'S'; // Внутренне сохраняем как 'S', но не отображаем сопернику
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
        if (grid[y][x] == 'S')
            return true;
    }
    return false;
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// 🎨 Отображение доски соперника с рамками и легендой
void Board::printBoardFramed() const {
    std::set<std::pair<int, int>> sunkCoords;
    for (const auto& ship : ships)
        if (ship.isSunk())
            for (const auto& coord : ship.getCoordinates())
                sunkCoords.insert(coord);

    // Верхняя координатная строка
    std::cout << "    ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << x << "   ";
    std::cout << "\n";

    // Верхняя рамка
    std::cout << "  ┌";
    for (int i = 0; i < BOARD_SIZE - 1; ++i)
        std::cout << "───┬";
    std::cout << "───┐\n";

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << " " << y << "│";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            std::pair<int, int> pos = {x, y};
            char cell = grid[y][x];
            char display = '.';

            // Выбираем, что показать игроку
            if (sunkCoords.count(pos)) display = 'D';
            else if (cell == 'X') display = 'X';
            else if (cell == 'O') display = 'O';

            std::cout << " " << display << " │";
        }
        std::cout << "\n";

        // Разделители строк
        if (y < BOARD_SIZE - 1) {
            std::cout << "  ├";
            for (int i = 0; i < BOARD_SIZE - 1; ++i)
                std::cout << "───┼";
            std::cout << "───┤\n";
        } else {
            // Нижняя рамка
            std::cout << "  └";
            for (int i = 0; i < BOARD_SIZE - 1; ++i)
                std::cout << "───┴";
            std::cout << "───┘\n";
        }
    }

    // Легенда символов
    std::cout << "\n🗺️ Легенда:\n";
    std::cout << "X — попадание\n";
    std::cout << "O — промах\n";
    std::cout << "D — потопленный корабль\n";
    std::cout << ". — неизвестная область\n";
}

// 🧭 Отображение собственной доски с кораблями
void Board::printOwnBoardFramed() const {
    std::set<std::pair<int, int>> sunkCoords;
    for (const auto& ship : ships)
        if (ship.isSunk())
            for (const auto& coord : ship.getCoordinates())
                sunkCoords.insert(coord);

    std::cout << "    ";
    for (int x = 0; x < BOARD_SIZE; ++x)
        std::cout << x << "   ";
    std::cout << "\n";

    std::cout << "  ┌";
    for (int i = 0; i < BOARD_SIZE - 1; ++i)
        std::cout << "───┬";
    std::cout << "───┐\n";

    for (int y = 0; y < BOARD_SIZE; ++y) {
        std::cout << " " << y << "│";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            std::pair<int, int> pos = {x, y};
            char cell = grid[y][x];
            char display = '.';

            // Показываем свои корабли, попадания и промахи
            if (sunkCoords.count(pos)) display = 'D';
            else if (cell == 'X') display = 'X';
            else if (cell == 'O') display = 'O';
            else if (cell == 'S') display = 'S';

            std::cout << " " << display << " │";
        }
        std::cout << "\n";

        if (y < BOARD_SIZE - 1) {
            std::cout << "  ├";
            for (int i = 0; i < BOARD_SIZE - 1; ++i)
                std::cout << "───┼";
            std::cout << "───┤\n";
        } else {
            std::cout << "  └";
            for (int i = 0; i < BOARD_SIZE - 1; ++i)
                std::cout << "───┴";
            std::cout << "───┘\n";
        }
    }

    // Легенда для своей доски
    std::cout << "\n🧭 Собственная доска — легенда:\n";
    std::cout << "S — корабль\n";
    std::cout << "X — попадание\n";
    std::cout << "D — потопленный\n";
    std::cout << "O — промах\n";
    std::cout << ". — пусто\n";
}

