#ifndef GAME_H
#define GAME_H

#include "agents/Agent.h"
#include "RenderUtilities.h"

enum CHESS_COLOR {
    CHESS_WHITE,
    CHESS_BLACK
};

class Game {
public:
    Game() {}
    ~Game() {}

    int score = 0; // TO DO: this is not chess

    // Makes game the default game
    void Init() {
        score = 0;
    }

    // Is called per frame, Render the game, handle input, game flow control and everything about the gameplay
    void Run() {
        DrawTextCen("This isn't chess, but it is fun!", GetScreenHeight() / 2, 100, 25, PINK);
        DrawTextCen("Try clicking around!", GetScreenHeight() / 2, 140, 20, PINK);
        DrawTextCen(TextFormat("SCORE: %i", score), GetScreenHeight() / 2, 200, 40, PINK);
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mousePos.x < GetScreenHeight()) {
            score++;
        }
    }

    void LoadGamesave() {

    }

    void SetAgent(CHESS_COLOR color, Agent* agent) {
        if (color == CHESS_WHITE) {
            if (white_agent) delete white_agent;
            white_agent = agent;
        } else {
            if (black_agent) delete black_agent;
            white_agent = agent;
        }
    }

    void Undo() {

    }

    void Redo() {

    }

private:

    Agent* white_agent;
    Agent* black_agent;

    // void HandleInput();
    // void HandleInputPromotion();
    // Move* GetMoveAtPosition(const Position& position);
    // void DoMoveOnBoard(const Move& move);

    // void CalculateAllPossibleMovements();
    // void CheckForEndOfGame();
    // void FilterMovesThatAttackOppositeKing();
    // void FilterMovesThatLeadToCheck();
    // bool IsAnyMovePossible();

    // // Game state.
    // Board board;
    // PIECE_COLOR turn = PIECE_COLOR::C_WHITE;
    // GAME_STATE state = GAME_STATE::S_RUNNING;

    // // Selected piece/possible moves state.
    // Piece* selectedPiece = nullptr;
    // std::map<Piece*, std::vector<Move>> possibleMovesPerPiece;

    // // Game information (current round and time).
    // int round = 1;
    // double time = 0;
};

#endif //GAME_H
