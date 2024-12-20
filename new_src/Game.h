#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include <optional>

#include "ChessUnits.h"
#include "Board.h"
#include "agents/Agent.h"

#include <thread>

class Game {
public:
    // Sets the agent that plays the game (Human or Chessbot and of which difficultoes)
    void SetAgent(CHESS_COLOR agentColor, std::string agentTag);
    void SetAgent(std::unique_ptr<Agent> agent);
    
    void Init(); // Makes game the default game
    void LoadGame(int slot); // Load from gamesave
    void SaveGame(int slot) const; // Save to gamesave

    void Render(); // Is called per frame when game is running. Renders the game.
    void Pause(); // Is called per frame when paused. Renders less information than Render()
    void Run(); // Is called per frame. Handles input, game flow control and everything about the gameplay

    bool Undo();
    bool Redo();

    CHESS_COLOR WhoseTurn() const;
    const Agent* GetCurrentAgent() const;
    int GetTurn() const; // The number of turns passed
    bool IsGameEnded() const;
    CHESS_VERDICT GetVerdict() const;
    std::vector<std::string> GetNotations();
    void UpdateNotations();

    // thread-running bot get move
    void GetBotMove();

private:
    std::unique_ptr<Agent> whiteAgent;
    std::unique_ptr<Agent> blackAgent;

    int turn;
    bool isPause;
    std::optional<Move> nextMove;
    std::thread t;
    bool isThreadRunning;
    Board board;
    std::vector<Board> undoHistory;
    std::vector<Board> redoHistory;
    std::vector<std::string> notations;

    CHESS_VERDICT verdict;
    
    void Running(); // Handles the moving of pieces
    void Ended(); // Probably does nothing (chess board is retained and game informations as well as extra buttons are handled in GameScene)
    void ExecuteMove(const Move move); // Board handle, turn swap, state handle, audio, stacks
    void UpdateGameStatus(); // update state and verdict. checks for end of game and stuffs
};

extern Game game;

#endif //GAME_H