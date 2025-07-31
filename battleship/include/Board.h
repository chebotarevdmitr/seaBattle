#pragma once
#include <vector>
#include "../include/Ship.h"

// Размер игрового поля
constexpr int BOARD_SIZE = 10;

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

    // Метод для визуализации поля (текстовый вариант)
    void printBoard() const;

private:
    // Массив ячеек: каждая может быть пустой, занята кораблём или отмечена как попадание/промах
    char grid[BOARD_SIZE][BOARD_SIZE];

    // Список всех кораблей на поле
    std::vector<Ship> ships;

    // Проверка: пересекается ли корабль с другими
    bool doesOverlap(const Ship& newShip) const;

    // Проверка: координаты в пределах поля
    bool isValidPosition(int x, int y) const;
};
