#pragma once
#include <vector>
#include "../include/Ship.h"

constexpr int BOARD_SIZE = 10;

class Board {
private:
    char grid[BOARD_SIZE][BOARD_SIZE];
    std::vector<Ship> ships;

public:
    Board();

    bool placeShip(const Ship& ship);
    bool fireAt(int x, int y);
    bool allShipsSunk() const;
    const std::vector<Ship>& getShips() const;
    bool doesOverlap(const Ship& ship) const;
    bool isValidPosition(int x, int y) const;

    // 🔧 Методы отображения поля
    void printBoard() const;
    void printBoardFramed() const;      // доска соперника
    void printOwnBoardFramed() const;   // собственная доска
};
