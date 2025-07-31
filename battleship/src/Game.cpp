#include "../include/Game.h"
#include <iostream>

Game::Game(const std::string& player1, const std::string& player2)
    : currentPlayerIndex(0), phase(GamePhase::Setup) {
    players[0].name = player1;
    players[1].name = player2;
}

void Game::playerTurn(int x, int y) {
    if (phase == GamePhase::Setup) {
        std::cout << "Размещение завершено. Начинаем игру!\n";
        phase = GamePhase::InProgress;
    }

    if (phase != GamePhase::InProgress)
        return;

    Player& current = players[currentPlayerIndex];
    Player& opponent = players[(currentPlayerIndex + 1) % 2];

    bool hit = opponent.board.fireAt(x, y);
    std::cout << current.name << " стреляет по (" << x << ", " << y << ") — "
              << (hit ? "попадание!" : "мимо...") << "\n";

    if (opponent.board.allShipsSunk()) {
        std::cout << current.name << " победил!\n";
        phase = GamePhase::Finished;
    } else {
        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    }
}

bool Game::isGameOver() const {
    return phase == GamePhase::Finished;
}

GamePhase Game::getPhase() const {
    return phase;
}

void Game::printCurrentBoard() const {
    const Player& opponent = players[(currentPlayerIndex + 1) % 2];
    std::cout << "Доска соперника (" << opponent.name << "):\n";
    opponent.board.printBoard();
}

const std::string& Game::getCurrentPlayerName() const {
    return players[currentPlayerIndex].name;
}

// ✅ Реализация нового метода доступа к доске игрока
Board& Game::getBoard(int index) {
    return players[index].board;
}
