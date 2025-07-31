#pragma once
#include "../include/Board.h"
#include <string>

// 🎮 Фазы игрового процесса
enum class GamePhase {
    Setup,
    InProgress,
    Finished
};

// 🧑‍✈️ Игрок: имя + его поле
struct Player {
    std::string name;
    Board board;
};

// 🕹️ Главный игровой контроллер
class Game {
public:
    Game(const std::string& player1, const std::string& player2);

    void playerTurn(int x, int y);
    bool isGameOver() const;
    GamePhase getPhase() const;
    void printCurrentBoard() const;
    const std::string& getCurrentPlayerName() const;

    // ✅ Новый метод — доступ к доске по индексу игрока (0 или 1)
    Board& getBoard(int index);

private:
    Player players[2];
    int currentPlayerIndex;
    GamePhase phase;
};

