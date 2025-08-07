#pragma once
#include <vector>
#include "../include/Ship.h"

// Размер игрового поля
constexpr int BOARD_SIZE = 10;

// Константы для состояний ячеек - улучшенная читаемость
constexpr char CELL_EMPTY = '.';        // Пустая клетка
constexpr char CELL_SHIP = 'S';         // Корабль (виден только на своей доске)
constexpr char CELL_HIT = 'X';          // Попадание
constexpr char CELL_MISS = 'O';         // Промах
constexpr char CELL_SUNK = 'D';         // Потопленный корабль

// Константы для цветов (ANSI escape codes)
namespace Color {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD = "\033[1m";
}

class Board {
public:
    // Конструктор: инициализируем пустое поле
    Board();

    // Добавление корабля на поле
    bool placeShip(const Ship& ship);

    // Обработка выстрела по координатам
    bool fireAt(int x, int y);

    // Проверка: все ли корабли потоплены
    bool allShipsSunk() const;

    // Получение всех кораблей
    const std::vector<Ship>& getShips() const;

    // Метод для визуализации поля соперника (текстовый вариант)
    void printEnemyBoard() const;
    
    // Метод для визуализации своей доски (с видимыми кораблями)
    void printPlayerBoard() const;

private:
    // Массив ячеек: каждая может быть пустой, занята кораблём или отмечена как попадание/промах
    char grid[BOARD_SIZE][BOARD_SIZE];

    // Список всех кораблей на поле
    std::vector<Ship> ships;

    // Проверка: пересекается ли корабль с другими
    bool doesOverlap(const Ship& newShip) const;

    // Проверка: координаты в пределах поля
    bool isValidPosition(int x, int y) const;
    
    // Вспомогательный метод для цветного вывода ячейки
    void printColoredCell(char cell, bool isPlayerBoard = false) const;
};