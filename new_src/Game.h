#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include <optional>

#include "ChessUnits.h"
#include "Board.h"
#include "pieces/Piece.h"
#include "agents/Agent.h"

#include "agents/RandomAgent.h"
#include "agents/ManualAgent.h"

#include "Renderer.h"

class Game {
public:
    // Sets the agent that plays the game (Human or Chessbot and of which difficultoes)
    void SetAgent(std::unique_ptr<Agent> agent);
    
    void Init(); // Makes game the default game
    void LoadGame(); // Load from gamesave

    void Render(); // Is called per frame when game is running. Renders the game.
    void Run(); // Is called per frame. Handles input, game flow control and everything about the gameplay

    bool Undo();
    bool Redo();

    CHESS_COLOR WhoseTurn() const;
    int GetTurn() const; // The number of turns passed
    bool IsGameEnded() const;
    CHESS_VERDICT GetVerdict() const;

private:
    std::unique_ptr<Agent> whiteAgent;
    std::unique_ptr<Agent> blackAgent;

    int turn;
    Board board;
    std::stack<Board> undoHistory;
    std::stack<Board> redoHistory;

    enum GAME_STATE {
        GAME_RUNNING,
        GAME_ENDED
    }; 
    GAME_STATE state;

    // Volatile info to render human player related moves
    std::optional<Position> selectedPosition;
    bool isPromoting;
    int promotingFile;
    
    void Running(); // Handles the moving of pieces
    void Ended(); // Probably does nothing (chess board is retained and game informations as well as extra buttons are handled in GameScene)
    void ExecuteMove(const Move move); // Board handle, turn swap, state handle, audio, stacks
        
};

extern Game game;

#endif //GAME_H