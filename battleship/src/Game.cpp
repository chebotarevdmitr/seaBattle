#include "../include/Game.h"
#include <iostream>

// 🔧 Конструктор инициализирует игроков и начальную фазу игры
Game::Game(const std::string& player1, const std::string& player2)
    : currentPlayerIndex(0), phase(GamePhase::Setup) {
    players[0].name = player1;
    players[1].name = player2;
}

// 🎮 Обработка хода игрока
void Game::playerTurn(int x, int y) {
    // 🧱 Если игра в фазе настройки — переход к игре
    if (phase == GamePhase::Setup) {
        std::cout << "Размещение завершено. Начинаем игру!\n";
        phase = GamePhase::InProgress;
    }

    if (phase != GamePhase::InProgress) return;

    Player& attacker = players[currentPlayerIndex];
    Player& defender = players[1 - currentPlayerIndex];

    // 🔫 Совершаем выстрел по координатам
    bool hit = defender.board.fireAt(x, y);

    std::cout << attacker.name << " стреляет по (" << x << ", " << y << "): ";
    if (hit)
        std::cout << "🎯 Попадание!\n";
    else
        std::cout << "💨 Промах.\n";

    // 🔍 Проверка потопленных кораблей
    if (defender.board.allShipsSunk()) {
        std::cout << attacker.name << " победил! 🏆\n";
        phase = GamePhase::Finished;
        return;
    }

    // 🔁 Смена игрока
    currentPlayerIndex = 1 - currentPlayerIndex;
}

// 🗂️ Получить фазу игры
GamePhase Game::getPhase() const {
    return phase;
}

// 📟 Отображение состояния игры
void Game::displayState() const {
    const Player& current = players[currentPlayerIndex];
    const Player& opponent = players[1 - currentPlayerIndex];

    std::cout << "\n📍 Игрок: " << current.name << "\n";

    std::cout << "🧭 Ваше поле:\n";
    current.board.printOwnBoardFramed();

    std::cout << "\n🎯 Поле соперника:\n";
    opponent.board.printBoardFramed();
}
