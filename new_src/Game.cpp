#include "Game.h"

#include "agents/RandomAgent.h"
#include "agents/ManualAgent.h"
#include "agents/SearchTreeAgent.h"
#include "agents/AlphaBetaAgent.h"

#include "Renderer.h"
#include "Properties.h"
#include <map>
#include <iostream>
#include <fstream>

Game game;

void Game::SetAgent(CHESS_COLOR agentColor, std::string agentTag) {
        // TO DO: set the right agent
    if (agentTag == "Human") SetAgent(std::make_unique<ManualAgent>(agentColor));
  
    if (agentTag == "Easy") SetAgent(std::make_unique<RandomAgent>(agentColor));
    if (agentTag == "Medium") SetAgent(std::make_unique<SearchTreeAgent>(agentColor));
    if (agentTag == "Hard") SetAgent(std::make_unique<RandomAgent>(agentColor));
}
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
    if (blackAgent == nullptr) blackAgent = std::make_unique<AlphaBetaAgent>(CHESS_BLACK, 0.1);
    whiteAgent->Init();
    blackAgent->Init();

    turn = 0;
    board.Init();
    std::vector<Board>().swap(undoHistory);
    std::vector<Board>().swap(redoHistory);
    verdict = CHESS_RUNNING;
}
void Game::LoadGame(int slot) {
    std::ifstream savefile(Properties::GetSavefilePath(slot));

    auto loadAgent = [&](CHESS_COLOR color) -> void {
        std::string agentTag;
        savefile >> agentTag;
        SetAgent(color, agentTag);
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

    loadAgent(CHESS_WHITE);
    loadAgent(CHESS_BLACK);
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
    // First render the background
    renderer.RenderBackground();

    // Then render the last move, if any
    if (board.GetLastMove() != std::nullopt) {
        renderer.RenderLastMove(board.GetLastMove().value());
    }

    // Then render the highlight of the selected position
    std::optional<Position> selectedPosition = GetCurrentAgent()->GetSelectedPosition();
    if (selectedPosition != std::nullopt) {
        renderer.RenderSelectedPosition(selectedPosition.value());
    }

    // Then render the non-selected pieces
    std::vector<const Piece*> staticPieces;
    for (const Piece* piece : board.GetPieces()) {
        if (piece->GetPosition() != selectedPosition) {
            staticPieces.push_back(piece);
        }
    }
    renderer.RenderPieces(staticPieces);

    if (GetCurrentAgent()->IsPromoting()) { // Promotion render: The selected piece is not rendered and the promotion options are shown.
        renderer.RenderPromotion(WhoseTurn(), GetCurrentAgent()->GetPromotingFile());
    } else { 
        // Render the possible moves of the selected position
        if (selectedPosition != std::nullopt) {
            const Piece* selectedPiece = board.GetPieceByPosition(selectedPosition.value());
            std::vector<Move> possibleMoves = board.GetPossibleMoves(selectedPiece);
            renderer.RenderPossibleMoves(possibleMoves);
        }
        // Render the pieces along the drag. Render the piece at intial position if not dragging.
        if (GetCurrentAgent()->IsDragging()) {
            renderer.RenderDraggingPiece(board.GetPieceByPosition(selectedPosition.value()));
        } else if (selectedPosition != std::nullopt) {
            renderer.RenderPieces(std::vector<const Piece*>{board.GetPieceByPosition(selectedPosition.value())});
        }
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
const Agent* Game::GetCurrentAgent() const {
    if (WhoseTurn() == CHESS_WHITE) return whiteAgent.get();
    else return blackAgent.get();
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
    } else {
        move = blackAgent->GetMove(board);
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

    UpdateGameStatus();
}
void Game::UpdateGameStatus() {
    // Checking preparation
    bool isAnyMovePossible = false;
    bool is50Moves = false;
    int countPieces = 0;
    std::map<PIECE_TYPE, int> countWhite, countBlack;
    bool isThreefoldRepetition = false;

    // Counting
    for (const Piece* piece : board.GetPiecesByColor(WhoseTurn())) {
        if (!board.GetPossibleMoves(piece).empty()) {
            isAnyMovePossible = true;
            break;
        }
    }
    for (const Piece* piece : board.GetPieces()) {
        if(piece->GetColor() == CHESS_WHITE) {
            ++countWhite[piece->GetType()];
        }
        else ++countBlack[piece->GetType()];
        ++countPieces;
    }
    for(Board board1 : undoHistory) {
        int countBoard = 0;
        for(const Board board2 : undoHistory) {
            if(board1 == board2) ++countBoard;
        }
        if(countBoard == 3) isThreefoldRepetition = true;
        std::cout << countBoard << "\n";
    }
    if(board.GetLastMove()->type == ATTACK || board.GetPieceByPosition(board.GetLastMove()->fromPosition)->GetType() == PAWN) is50Moves = true;
    for(int i = undoHistory.size() - 1; !is50Moves && i >= 0 && i > (board.GetPieceByPosition(board.GetLastMove()->fromPosition)->GetColor() == CHESS_WHITE ? undoHistory.size() - 99 : undoHistory.size() - 100); --i) {
        if(board.GetLastMove()->type == ATTACK || board.GetPieceByPosition(board.GetLastMove()->fromPosition)->GetType() == PAWN) is50Moves = true;
    }

    // Insufficent Rule
    auto IsKingvsKing = [&]() -> bool {
        return countPieces == 2;
    };
    auto IsKingBishopvsKing = [&]() -> bool {
        return countPieces == 3 && (countWhite[BISHOP] == 1 || countBlack[BISHOP] == 1);
    };
    auto IsKingKnightvsKing = [&]() -> bool {
        return countPieces == 3 && (countWhite[KNIGHT] == 1 || countBlack[KNIGHT] == 1);
    };
    auto IsKingBishopvsKingBishop = [&]() -> bool {
        // base condition
        if(countPieces != 4) return false;
        if(countWhite[BISHOP] != 1 || countWhite[BISHOP] != 1) return false;
        
        Position whiteBishop, blackBishop;
        for (const Piece* piece : board.GetPieces()) {
            if(piece->GetColor() == CHESS_WHITE && piece->GetType() == BISHOP) whiteBishop = piece->GetPosition();
            if(piece->GetColor() == CHESS_BLACK && piece->GetType() == BISHOP) whiteBishop = piece->GetPosition();
        }

        return ((whiteBishop.i + whiteBishop.j) - (blackBishop.i + blackBishop.j)) % 2 == 0;
    };

    // Conditions
    if (!isAnyMovePossible) {
        if (board.IsInCheck(CHESS_WHITE)) verdict = BLACK_WINS;
        else if (board.IsInCheck(CHESS_BLACK)) verdict = WHITE_WINS;
        else verdict = STALEMENT;
    } 
    else if(IsKingvsKing() || IsKingBishopvsKing() || IsKingKnightvsKing() || IsKingBishopvsKingBishop()) {
        verdict = INSUFFICIENT;
    }
    else if(is50Moves) {
        verdict = FIFTYMOVE;
    }
    else if(isThreefoldRepetition) {
        verdict = THREEFOLD;
    }
    else {
        verdict = CHESS_RUNNING;
    }
}