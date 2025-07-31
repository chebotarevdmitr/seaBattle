#pragma once
#include "../include/Board.h"
#include <string>

// Перечисление фаз игры
enum class GamePhase {
    Setup,
    InProgress,
    Finished
};

// Игрок в игре
struct Player {
    std::string name;
    Board board;
};

class Game {
public:
    Game(const std::string& player1, const std::string& player2);

    // Главный игровой цикл — 1 ход
    void playerTurn(int x, int y);

    // Проверка окончания игры
    bool isGameOver() const;

    // Получение текущей фазы
    GamePhase getPhase() const;

    // Вывод состояния доски
    void printCurrentBoard() const;

    // Получение текущего игрока
    const std::string& getCurrentPlayerName() const;

private:
    Player players[2];
    int currentPlayerIndex;
    GamePhase phase;
};
