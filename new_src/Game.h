#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include <optional>

#include "ChessUnits.h"
#include "Board.h"
#include "Renderer.h"

#include "agents/Agent.h"
#include "agents/RandomAgent.h"
#include "agents/ManualAgent.h"

#include "pieces/Piece.h"
#include "pieces/Pawn.h"
// #include "pieces/Rook.h"
// #include "pieces/Knight.h"
// #include "pieces/Bishop.h"
// #include "pieces/Queen.h"
// #include "pieces/King.h"

class Game {
public:

    // Makes game the default game
    void Init() {
        turn = 0;
        std::stack<Board>().swap(undoHistory);
        std::stack<Board>().swap(redoHistory);
        state = GAME_RUNNING;
        board.Clear();

        // TO DO: properly standard game
        for (int j = 0; j < 8; j++) {
            board.Add(std::make_unique<Pawn>(CHESS_WHITE, Position{6, j}));
            board.Add(std::make_unique<Pawn>(CHESS_BLACK, Position{1, j}));
        }
        if (whiteAgent == nullptr) whiteAgent = std::make_unique<ManualAgent>(CHESS_WHITE);
        if (blackAgent == nullptr) blackAgent = std::make_unique<RandomAgent>(CHESS_BLACK);
    }

    // Sets the agent that plays the game (Human or Chessbot and of which difficultoes)
    void SetAgent(std::unique_ptr<Agent> agent) {
        if (agent->GetColor() == CHESS_WHITE) {
            whiteAgent = std::move(agent);
        } else {
            blackAgent = std::move(agent);
        }
    }

    // Load from gamesave
    void LoadGame() {
        // TO DO: load from game save
    }

    // Is called per frame when game is running. Renders the game.
    void Render() {
        renderer.RenderBackground();
        if (selectedPosition != std::nullopt) {
            renderer.RenderSelectedPiece(selectedPosition.value());
        }
        renderer.RenderPieces(board);
        if (selectedPosition != std::nullopt) {
		    const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
		    std::vector<Move> possibleMoves = board.GetPossibleMoves(selectedPiece);
		    renderer.RenderPossibleMoves(possibleMoves);
        }
    }

    // Is called per frame. Handles input, game flow control and everything about the gameplay
    void Run() {
        switch(state) {
            case GAME_RUNNING: {
                Running();
            }; break;
            case GAME_ENDED: {
                Ended();
            }; break;
            default: break;
        }
    }   

    bool Undo() {
        // TO DO: undo
        return false;
    }

    bool Redo() {
        // TO DO: redo
        return false;
    }

    CHESS_COLOR WhoseTurn() const {
        if (turn % 2 == 0) return CHESS_WHITE;
        else return CHESS_BLACK;
    }

    // The number of turns passed
    int GetTurn() const {
        return turn;
    }

    bool IsGameEnded() const {
        return state == GAME_ENDED;
    }

    CHESS_VERDICT GetVerdict() const {
        if (!IsGameEnded()) return CHESS_RUNNING;
        if (board.IsInCheck(CHESS_WHITE)) return BLACK_WINS;
        if (board.IsInCheck(CHESS_BLACK)) return WHITE_WINS;
        return STALEMENT;
    }

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

    std::optional<Position> selectedPosition;
    
    // Handles the moving of pieces
    void Running() {
        std::optional<Move> move;
        if (WhoseTurn() == CHESS_WHITE) {
            move = whiteAgent->GetMove(board);
            selectedPosition = whiteAgent->GetSelectedPosition();
        } else {
            move = blackAgent->GetMove(board);
            selectedPosition = blackAgent->GetSelectedPosition();
        }
        if (move != std::nullopt) {
            ExecuteMove(move.value());
        }
    }

    // Probably does nothing (chess board is retained and game informations as well as extra buttons are handled in GameScene)
    void Ended() {

    }

    // Board handle, turn swap, state handle, audio, stacks
    void ExecuteMove(const Move move) {
        undoHistory.push(board);
        if (!board.ExecuteMove(move)) { // Execute fail
            undoHistory.pop();
            return;
        }
        std::stack<Board>().swap(redoHistory);
        
        turn++;

        // TO DO: properly execute game

    }

};

inline Game game;

#endif //GAME_H