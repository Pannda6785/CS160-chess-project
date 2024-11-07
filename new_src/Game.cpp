#include "Game.h"

void Game::SetAgent(std::unique_ptr<Agent> agent) {
    if (agent->GetColor() == CHESS_WHITE) {
        whiteAgent = std::move(agent);
    } else {
        blackAgent = std::move(agent);
    }
}

void Game::Init() {
    turn = 0;
    std::stack<Board>().swap(undoHistory);
    std::stack<Board>().swap(redoHistory);
    state = GAME_RUNNING;
    board.Init();
    // TO DO: properly have the right kind of agent set
    if (whiteAgent == nullptr) whiteAgent = std::make_unique<ManualAgent>(CHESS_WHITE);
    if (blackAgent == nullptr) blackAgent = std::make_unique<RandomAgent>(CHESS_BLACK);
}
void Game::LoadGame() {
    // TO DO: load from game save
}

void Game::Render() {
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
void Game::Run() {
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

bool Game::Undo() {
    // TO DO: undo
    return false;
}
bool Game::Redo() {
    // TO DO: redo
    return false;
}

CHESS_COLOR Game::WhoseTurn() const {
    if (turn % 2 == 0) return CHESS_WHITE;
    else return CHESS_BLACK;
}
int Game::GetTurn() const {
    return turn;
}
bool Game::IsGameEnded() const {
    return state == GAME_ENDED;
}
CHESS_VERDICT Game::GetVerdict() const {
    if (!IsGameEnded()) return CHESS_RUNNING;
    if (board.IsInCheck(CHESS_WHITE)) return BLACK_WINS;
    if (board.IsInCheck(CHESS_BLACK)) return WHITE_WINS;
    return STALEMENT;
}

void Game::Running() {
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
void Game::Ended() {

}
void Game::ExecuteMove(const Move move) {
    undoHistory.push(board);
    if (!board.ExecuteMove(move)) { // Execute fail. Should never happen
        undoHistory.pop();
        return;
    }
    std::stack<Board>().swap(redoHistory); // clear the redo history
    
    turn++;

    // TO DO: properly execute game

}

Game game;