#include <iostream>
#include <cstdlib>      // rand, srand
#include <ctime>        // time
#include <sstream>      // std::istringstream
#include "../include/Game.h"

Orientation randomOrientation() {
    return rand() % 2 == 0 ? Orientation::Horizontal : Orientation::Vertical;
}

std::pair<int, int> randomPosition(int maxX, int maxY) {
    int x = rand() % maxX;
    int y = rand() % maxY;
    return {x, y};
}

// 🚢 Автоматическая расстановка кораблей
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

    autoPlaceFleet(game.getBoard(0));  // Игрок 1
    autoPlaceFleet(game.getBoard(1));  // Игрок 2

    std::cout << "⚓ Флот размещён! Начинаем игру.\n";

    // 🔁 Главный игровой цикл
    while (!game.isGameOver()) {
        std::cout << "\nХод игрока: " << game.getCurrentPlayerName() << "\n";
        game.printCurrentBoard();

        int x, y;

        // 🔒 Безопасный ввод координат
        while (true) {
            std::cout << "Введите координаты выстрела (x y): ";

            std::string input;
            std::getline(std::cin, input);

            std::istringstream iss(input);
            if (!(iss >> x >> y)) {
                std::cout << "Error: недопустимая клавиша. Введите два числа через пробел.\n";
                continue;
            }

            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
                std::cout << "Error: координаты вне поля. Диапазон — от 0 до 9.\n";
                continue;
            }

            break; // ✅ Корректный ввод
        }

        game.playerTurn(x, y);
    }

    std::cout << "\n🏁 Игра завершена!\n";
    return 0;
}
