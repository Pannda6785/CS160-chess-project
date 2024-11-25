#include "Game.h"

#include "agents/InputUtilities.h"
#include "agents/RandomAgent.h"
#include "agents/ManualAgent.h"
#include "agents/SearchTreeAgent.h"
#include "agents/AlphaBetaAgent.h"
#include "agents/BitboardAgent.h"

#include "Renderer.h"
#include "Properties.h"
#include <map>
#include <fstream>
#include <algorithm>

Game game;

void Game::SetAgent(CHESS_COLOR agentColor, std::string agentTag) {
    if (agentTag == "Human") SetAgent(std::make_unique<ManualAgent>(agentColor));
    if (agentTag == "Bot1") SetAgent(std::make_unique<RandomAgent>(agentColor));
    if (agentTag == "Bot2") SetAgent(std::make_unique<SearchTreeAgent>(agentColor));
    if (agentTag == "Bot3") SetAgent(std::make_unique<BitboardAgent>(agentColor));
}
void Game::SetAgent(std::unique_ptr<Agent> agent) {
    if (agent->GetColor() == CHESS_WHITE) {
        whiteAgent = std::move(agent);
    } else {
        blackAgent = std::move(agent);
    }
}

void Game::Init() {
    whiteAgent->Init();
    blackAgent->Init();

    turn = 0;
    board.Init();
    std::vector<Board>().swap(undoHistory);
    std::vector<Board>().swap(redoHistory);
    notations.clear();
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

    UpdateNotations();

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
        renderer.RenderSelectedPosition(selectedPosition.value(), Color{144, 238, 144, 150});
    }

    // Then if king being checked, render checking piece(s)
    if(board.IsInCheck(GetCurrentAgent()->GetColor())) {
        CHESS_COLOR color = GetCurrentAgent()->GetColor();
        for (const Piece* king : board.GetPieces()) {
            if (king->GetType() == KING && king->GetColor() == color) {
                Position position = king->GetPosition();

                for (const Piece* piece : board.GetPieces()) {
                    if (piece->GetColor() == color) continue;
                    if (piece->GetType() == PAWN) { // since pawn's attack pattern is a bit weird
                        int i = piece->GetPosition().i + (color == CHESS_WHITE ? +1 : -1);
                        int j = piece->GetPosition().j;
                        if (position == Position{i, j - 1} || position == Position{i, j + 1}) {
                            if(verdict == CHESS_RUNNING) {
                                renderer.RenderSelectedPosition(piece->GetPosition(), Color{253, 249, 0, 150});
                                renderer.RenderSelectedPosition(position, Color{253, 249, 0, 150});
                            }
                            else {
                                renderer.RenderSelectedPosition(piece->GetPosition(), Color{230, 41, 55, 150});
                                renderer.RenderSelectedPosition(position, Color{230, 41, 55, 150});
                            }
                        }
                    }
                    else { // Non-special pieces (Queen, Knight, Bishop, Rooks) attack the same way they move
                        for (Move move : piece->GetPossibleMoves(board)) {
                            // just to clarify, by now move.type can only be either WALK or ATTACK
                            if (move.toPosition != position) continue;
                            if(verdict == CHESS_RUNNING) {
                                renderer.RenderSelectedPosition(piece->GetPosition(), Color{253, 249, 0, 150});
                                renderer.RenderSelectedPosition(position, Color{253, 249, 0, 150});
                            }
                            else {
                                renderer.RenderSelectedPosition(piece->GetPosition(), Color{230, 41, 55, 150});
                                renderer.RenderSelectedPosition(position, Color{230, 41, 55, 150});
                            }
                        }
                    }
                }
            }
        }
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

    // Render hovering pieceName
    if(board.GetPieceByPosition(InputUtilities::GetMouseChessPosition()) != nullptr) {
        renderer.RenderHoveringPieceName(board.GetPieceByPosition(InputUtilities::GetMouseChessPosition()));
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
    bool isPromoting = GetCurrentAgent()->IsPromoting();
    whiteAgent->Init();
    blackAgent->Init();
    if (isPromoting) return false; // if undo during promotion choosing, then cancel the promotion only

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

void Game::UpdateNotations() {
    std::vector<std::string> ret;

    Board currentBoard = this->board;
    int idx = undoHistory.size();

    while(currentBoard.GetLastMove() != std::nullopt) {   
        std::string s;

        switch(currentBoard.GetLastMove()->type) {
            case WALK: {
                if(currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == PAWN) {
                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                }
                else if(currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == QUEEN
                || currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == KING) {
                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                }
                else {
                    CHESS_COLOR color = GetCurrentAgent()->GetColor();
                    bool yes = true;

                    for (const Piece* piece : board.GetPieces()) {
                        if(piece->GetType() == currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType()
                        && piece->GetColor() == color && piece->GetPosition() != currentBoard.GetLastMove()->toPosition) {
                            Position position = piece->GetPosition();
                            
                            for (Move move : piece->GetPossibleMoves(board)) {
                                // just to clarify, by now move.type can only be either WALK or ATTACK
                                if(move.toPosition != position) continue;
                                if(move.fromPosition.j != currentBoard.GetLastMove()->fromPosition.j) {
                                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                                    s += char('a' + currentBoard.GetLastMove()->fromPosition.j);
                                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                                    yes = false;
                                }
                                else {
                                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                                    s += char('8' - currentBoard.GetLastMove()->fromPosition.i);
                                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                                    yes = false;
                                }
                            }
                        }
                    }

                    if(yes) {
                        s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                        s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                        s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                        yes = false;
                    }
                }
            } break;
            case DOUBLE_WALK: {
                s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                s += char('8' - currentBoard.GetLastMove()->toPosition.i);
            } break;
            case ATTACK: {
                if(currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == PAWN) {
                    s += char('a' + currentBoard.GetLastMove()->fromPosition.j);
                    s += 'x';
                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                }
                else if(currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == QUEEN
                || currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType() == KING) {
                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                    s += 'x';
                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                }
                else {
                    CHESS_COLOR color = GetCurrentAgent()->GetColor();
                    bool yes = true;

                    for (const Piece* piece : board.GetPieces()) {
                        if(piece->GetType() == currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetType()
                        && piece->GetColor() == color && piece->GetPosition() != currentBoard.GetLastMove()->toPosition) {
                            Position position = piece->GetPosition();
                            
                            for (Move move : piece->GetPossibleMoves(board)) {
                                // just to clarify, by now move.type can only be either WALK or ATTACK
                                if(move.toPosition != position) continue;
                                if(move.fromPosition.j != currentBoard.GetLastMove()->fromPosition.j) {
                                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                                    s += char('a' + currentBoard.GetLastMove()->fromPosition.j);
                                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                                    yes = false;
                                }
                                else {
                                    s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                                    s += char('8' - currentBoard.GetLastMove()->fromPosition.i);
                                    s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                                    s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                                    yes = false;
                                }
                            }
                        }
                    }

                    if(yes) {
                        s += currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetTag();
                        s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                        s += char('8' - currentBoard.GetLastMove()->toPosition.i);

                        yes = false;
                    }
                }
            } break;
            case SHORT_CASTLING: {
                s = "O-O";
            } break;
            case LONG_CASTLING: {
                s = "O-O-O";
            } break;
            case EN_PASSANT: {
                s += char('a' + currentBoard.GetLastMove()->fromPosition.j);
                s += 'x';
                s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                s += " e.p";
            } break;
            case PROMOTION: {
                s += char('a' + currentBoard.GetLastMove()->toPosition.j);
                s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                s += "=";
                
                switch(currentBoard.GetLastMove()->promotionPiece) {
                    case QUEEN: s += "Q"; break;
                    case ROOK: s += "R"; break;
                    case BISHOP: s += "B"; break;
                    case KNIGHT: s += "N"; break;
                }
            } break;
            case ATTACK_AND_PROMOTION: {
                s += char('a' + currentBoard.GetLastMove()->fromPosition.j);
                s += 'x';
                s += char('a' + currentBoard.GetLastMove()->toPosition.i);
                s += char('8' - currentBoard.GetLastMove()->toPosition.i);
                s += "=";
                
                switch(currentBoard.GetLastMove()->promotionPiece) {
                    case QUEEN: s += "Q"; break;
                    case ROOK: s += "R"; break;
                    case BISHOP: s += "B"; break;
                    case KNIGHT: s += "N"; break;
                }
            } break;
        }

        if(idx == undoHistory.size() && verdict != CHESS_RUNNING) {
            s += '#';
        }
        else if(currentBoard.IsInCheck(currentBoard.GetPieceByPosition(currentBoard.GetLastMove()->toPosition)->GetColor() == CHESS_WHITE ? CHESS_BLACK : CHESS_WHITE)) {
            s += '+';
        }

        ret.push_back(s);

        if(idx == 0) break; 
        else --idx;
        currentBoard = undoHistory[idx];
    }

    std::reverse(ret.begin(), ret.end());
    for(int i=0;i<ret.size();++i) {
        if(i%2 == 0) {
            ret[i] = std::to_string(i/2 + 1) + ". " + ret[i];
        }
    }
    notations = ret;
}
std::vector<std::string> Game::GetNotations() {
    return notations;
}

void Game::Running() {
    if (!redoHistory.empty() && GetCurrentAgent()->GetTag() != "Human") { // if reviewing history (through undos), then AI agents are to be frozen
        return;
    }
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
    UpdateNotations();
    
    if(IsGameEnded() || board.IsInCheck(CHESS_WHITE) || board.IsInCheck(CHESS_BLACK)) {
        PlaySound(Properties::sounds["notify"]);
    }
    else if(move.type == ATTACK || move.type == ATTACK_AND_PROMOTION || move.type == EN_PASSANT) {
        PlaySound(Properties::sounds["capture"]);
    }
    else PlaySound(Properties::sounds["move"]);
}
void Game::UpdateGameStatus() {
    // Checking preparation
    bool isAnyMovePossible = false;
    bool is50Moves = true;
    int countPieces = 0;
    std::map<PIECE_TYPE, int> countWhite, countBlack;
    bool isThreefoldRepetition = false;

    // Counting
    for (const Piece* piece : board.GetPiecesByColor(WhoseTurn())) { // For no possible move
        if (!board.GetPossibleMoves(piece).empty()) {
            isAnyMovePossible = true;
            break;
        }
    }
    for (const Piece* piece : board.GetPieces()) { // For insufficent move
        if(piece->GetColor() == CHESS_WHITE) {
            ++countWhite[piece->GetType()];
        }
        else ++countBlack[piece->GetType()];
        ++countPieces;
    }
    for(Board board1 : undoHistory) { // For ThreeFold Repetition
        int countBoard = 0;
        if(board1 == board) ++countBoard;
        for(const Board board2 : undoHistory) {
            if(board1 == board2) ++countBoard;
        }
        if(countBoard == 3) {
            isThreefoldRepetition = true;
            break;
        }
    }
    /*
    */
    // For 50 moves
    if(undoHistory.size() < 99) {
        is50Moves = false;
    }
    else if(board.GetLastMove()->type == ATTACK || board.GetPieceByPosition(board.GetLastMove()->toPosition)->GetType() == PAWN) is50Moves = false;
    else for(int i = undoHistory.size() - 1; i > (board.GetPieceByPosition(board.GetLastMove()->toPosition)->GetColor() == CHESS_WHITE ? undoHistory.size() - 99 : undoHistory.size() - 100); --i) {
        if(undoHistory[i].GetLastMove()->type == ATTACK || undoHistory[i].GetPieceByPosition(undoHistory[i].GetLastMove()->toPosition)->GetType() == PAWN) is50Moves = false;
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