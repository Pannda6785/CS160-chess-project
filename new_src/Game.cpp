#include "Game.h"

#include "agents/RandomAgent.h"
#include "agents/ManualAgent.h"

#include "Renderer.h"
#include "Properties.h"
#include <fstream>

Game game;

void Game::SetAgent(std::unique_ptr<Agent> agent) {
    if (agent->GetColor() == CHESS_WHITE) {
        whiteAgent = std::move(agent);
    } else {
        blackAgent = std::move(agent);
    }
}

void Game::Init() {
    // TO DO: properly have the right kind of agent set (decided from the 1P, 2P choosing title and the Difficulty title)
    if (whiteAgent == nullptr) whiteAgent = std::make_unique<ManualAgent>(CHESS_WHITE);
    if (blackAgent == nullptr) blackAgent = std::make_unique<ManualAgent>(CHESS_BLACK);
    whiteAgent->Init();
    blackAgent->Init();

    turn = 0;
    board.Init();
    std::vector<Board>().swap(undoHistory);
    std::vector<Board>().swap(redoHistory);
    verdict = CHESS_RUNNING;

    selectedPosition = std::nullopt;
    isPromoting = false;
}
void Game::LoadGame(int slot) {
    std::ifstream savefile(Properties::GetSavefilePath(slot));

    auto loadAgent = [&](CHESS_COLOR color) -> std::unique_ptr<Agent> {
        // TO DO: set the right agent
        std::string agentType;
        savefile >> agentType;
        if (agentType == "Human") return std::make_unique<ManualAgent>(color);
        if (agentType == "Bot1") return std::make_unique<RandomAgent>(color);
        if (agentType == "Bot2") return std::make_unique<RandomAgent>(color);
        if (agentType == "Bot3") return std::make_unique<RandomAgent>(color);
        return nullptr;
    };
    auto loadBoard = [&]() -> Board {
        Board board;

        int numPieces;
        savefile >> numPieces;
        while (numPieces--) {
            std::string tag;
            CHESS_COLOR color;
            Position position;
            bool hasMoved;
            savefile >> tag >> color >> position >> hasMoved;
            board.Add(tag, color, position, hasMoved);
        }
        
        std::string lastMoveStr;
        savefile >> lastMoveStr;
        if (lastMoveStr == "NO_LAST_MOVE") {
            board.SetLastMove(std::nullopt);  // No last move
        } else {
            Move lastMove;
            savefile >> lastMove;
            board.SetLastMove(lastMove);
        }

        return board;   
    };

    whiteAgent = loadAgent(CHESS_WHITE);
    blackAgent = loadAgent(CHESS_BLACK);
    whiteAgent->Init();
    blackAgent->Init();

    savefile >> turn;

    board = loadBoard();

    std::vector<Board>().swap(undoHistory);
    int numUndos; 
    savefile >> numUndos;
    while (numUndos--) {
        undoHistory.push_back(loadBoard());
    }

    std::vector<Board>().swap(redoHistory);
    int numRedos;
    savefile >> numRedos;
    while (numRedos--) {
        redoHistory.push_back(loadBoard());
    }

    savefile >> verdict;

    selectedPosition = std::nullopt;
    isPromoting = false;

    savefile.close();
}
void Game::SaveGame(int slot) const {
    std::ofstream savefile(Properties::GetSavefilePath(slot));

    auto saveAgent = [&](const std::unique_ptr<Agent>& agent) -> void {
        savefile << agent->GetTag() << '\n';
    };
    auto saveBoard = [&](const Board &board) -> void {
        std::vector<const Piece*> pieces = board.GetPieces();
        savefile << pieces.size() << '\n';
        for (const Piece* piece : pieces) {
            std::string tag = piece->GetTag();
            CHESS_COLOR color = piece->GetColor();
            Position position = piece->GetPosition();
            bool hasMoved = piece->HasMoved();
            savefile << tag << ' ' << color << ' ' << position << ' ' << hasMoved << '\n';
        }
        if (board.GetLastMove() == std::nullopt) {
            savefile << "NO_LAST_MOVE\n";
        } else {
            savefile << "HAS_LAST_MOVE ";
            savefile << board.GetLastMove().value() << '\n';
        }
    };

    saveAgent(whiteAgent);
    saveAgent(blackAgent);

    savefile << turn << '\n';

    saveBoard(board);

    savefile << undoHistory.size() << '\n';
    for (const Board &board : undoHistory) {
        saveBoard(board);
    }

    savefile << redoHistory.size() << '\n';
    for (const Board &board : redoHistory) {
        saveBoard(board);
    }

    savefile << verdict << '\n';

    savefile.close();
}

void Game::Render() {
    renderer.RenderBackground();
    if (board.GetLastMove() != std::nullopt) {
        renderer.RenderLastMove(board.GetLastMove().value());
    }
    if (selectedPosition != std::nullopt) {
        renderer.RenderSelectedPiece(selectedPosition.value());
    }
    renderer.RenderPieces(board);
    if (selectedPosition != std::nullopt) {
        const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
        std::vector<Move> possibleMoves = board.GetPossibleMoves(selectedPiece);
        renderer.RenderPossibleMoves(possibleMoves);
    }
    if (whiteAgent->IsPromoting()) {
        renderer.RenderPromotion(CHESS_WHITE, whiteAgent->GetPromotingFile());
    }
    if (blackAgent->IsPromoting()) {
        renderer.RenderPromotion(CHESS_BLACK, blackAgent->GetPromotingFile());
    }
}
void Game::Run() {
    switch(verdict) {
        case CHESS_RUNNING: {
            Running();
        }; break;
        default: {
            
        }; break;
    }
}   

bool Game::Undo() {
    if (undoHistory.empty()) return false;

    whiteAgent->Init();
    blackAgent->Init();
    selectedPosition = std::nullopt;
    isPromoting = false;

    turn--;
    redoHistory.push_back(board);
    board = undoHistory.back();
    undoHistory.pop_back();

    UpdateGameStatus();

    return true;
}
bool Game::Redo() {
    if (redoHistory.empty()) return false;

    whiteAgent->Init();
    blackAgent->Init();
    selectedPosition = std::nullopt;
    isPromoting = false;

    turn++;
    undoHistory.push_back(board);
    board = redoHistory.back();
    redoHistory.pop_back();

    UpdateGameStatus();

    return true;
}

CHESS_COLOR Game::WhoseTurn() const {
    if (turn % 2 == 0) return CHESS_WHITE;
    else return CHESS_BLACK;
}
int Game::GetTurn() const {
    return turn;
}
bool Game::IsGameEnded() const {
    return verdict != CHESS_RUNNING;
}
CHESS_VERDICT Game::GetVerdict() const {
    return verdict;
}

void Game::Running() {
    std::optional<Move> move;
    if (WhoseTurn() == CHESS_WHITE) {
        move = whiteAgent->GetMove(board);
        selectedPosition = whiteAgent->GetSelectedPosition();
        isPromoting = whiteAgent->IsPromoting();
        promotingFile = whiteAgent->GetPromotingFile();
    } else {
        move = blackAgent->GetMove(board);
        selectedPosition = blackAgent->GetSelectedPosition();
        isPromoting = blackAgent->IsPromoting();
        promotingFile = blackAgent->GetPromotingFile();
    }
    if (move != std::nullopt) {
        ExecuteMove(move.value());
    }
}
void Game::Ended() {

}
void Game::ExecuteMove(const Move move) {
    undoHistory.push_back(board);
    if (!board.ExecuteMove(move)) { // Execute fail. Should never happen
        undoHistory.pop_back();
        return;
    }
    std::vector<Board>().swap(redoHistory); // clear the redo history
    turn++;

    selectedPosition = std::nullopt;
    isPromoting = false;

    UpdateGameStatus();
}
void Game::UpdateGameStatus() {
    bool isAnyMovePossible = false;
    for (const Piece* piece : board.GetPiecesByColor(WhoseTurn())) {
        if (!board.GetPossibleMoves(piece).empty()) {
            isAnyMovePossible = true;
            break;
        }
    }
    if (!isAnyMovePossible) {
        if (board.IsInCheck(CHESS_WHITE)) verdict = BLACK_WINS;
        else if (board.IsInCheck(CHESS_BLACK)) verdict = WHITE_WINS;
        else verdict = STALEMENT;
    } else {
        verdict = CHESS_RUNNING;
    }
}