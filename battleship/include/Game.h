#pragma once
#include <string>
#include "Board.h"

// 🎮 Состояние игры
enum class GamePhase {
    Setup,      // ⛵ Расстановка кораблей
    InProgress, // ⚔️ Игра идёт
    Finished    // 🏁 Игра завершена
};

// 👤 Игрок с именем и доской
struct Player {
    std::string name;
    Board board;
};

// 🎯 Класс Game управляет логикой боя
class Game {
private:
    Player players[2];           // 👥 Два игрока
    int currentPlayerIndex;      // 🧭 Кто сейчас ходит (0 или 1)
    GamePhase phase;             // 🕹️ Фаза игры

public:
    // 📦 Создание новой игры с двумя именами
    Game(const std::string& player1, const std::string& player2);

    // 🎮 Выполнение хода
    void playerTurn(int x, int y);

    // 🔁 Получить фазу (например, чтобы завершить игру)
    GamePhase getPhase() const;

    // 🎟️ Получить имя текущего игрока
    std::string getCurrentPlayerName() const {
        return players[currentPlayerIndex].name;
    }

    // 📊 Отобразить доску соперника
    void printCurrentBoard() const {
        const Player& opponent = players[(currentPlayerIndex + 1) % 2];
        opponent.board.printBoardFramed();
    }

    // 📟 Новый метод: показать обе доски
    void displayState() const;

    // 🧭 Доступ к доске игрока по индексу
    Board& getBoard(int index) {
        return players[index].board;
    }

    const Board& getBoard(int index) const {
        return players[index].board;
    }

    // ⚖️ Проверка на завершение игры
    bool isGameOver() const {
        return phase == GamePhase::Finished;
    }
};

