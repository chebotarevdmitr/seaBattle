#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include "../include/Game.h"

Orientation randomOrientation() {
    return rand() % 2 == 0 ? Orientation::Horizontal : Orientation::Vertical;
}

// Получение случайных координат для размещения
std::pair<int, int> randomPosition(int maxX, int maxY) {
    int x = rand() % maxX;
    int y = rand() % maxY;
    return {x, y};
}

// Функция автоматической расстановки кораблей
void autoPlaceFleet(Board& board) {
    std::vector<std::pair<std::string, int>> fleet = {
        {"Battleship", 4},
        {"Cruiser1", 3}, {"Cruiser2", 3},
        {"Destroyer1", 2}, {"Destroyer2", 2}, {"Destroyer3", 2}
    };

    for (auto& [name, size] : fleet) {
        bool placed = false;
        while (!placed) {
            auto start = randomPosition(BOARD_SIZE, BOARD_SIZE);
            Orientation dir = randomOrientation();
            Ship ship(name, size, start, dir);
            placed = board.placeShip(ship);
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Game game("Player1", "Player2");

    // Автоматическое размещение для обоих игроков
    autoPlaceFleet(game.getBoard(0));  // board игрока 1
    autoPlaceFleet(game.getBoard(1));  // board игрока 2

    std::cout << "Флот размещён! Начинаем игру.\n";

    // Главный игровой цикл
    while (!game.isGameOver()) {
        std::cout << "\nХод игрока: " << game.getCurrentPlayerName() << "\n";
        game.printCurrentBoard();

        int x, y;
        std::cout << "Введите координаты выстрела (x y): ";
        std::cin >> x >> y;

        game.playerTurn(x, y);
    }

    std::cout << "\nИгра завершена!\n";
    return 0;
}

