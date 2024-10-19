#include "Game.h"
#include "Position.h"
#include "raylib.h"
#include "Renderer.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Rook.h"
#include "Properties.h"

#include <filesystem>
#include <iostream>

const Color Game::LIGHT_SHADE = Color{240, 217, 181, 255};
const Color Game::DARK_SHADE = Color{181, 136, 99, 255};

Game::Game() {
    // Init the board and calculate the initial movements for the white player.
    board.Init();

    CalculateAllPossibleMovements();
}

Game::~Game() {
    board.Clear();
    Properties::currentScreen = WINLOSE;
}

void Game::Run() {
    //temp condition
    while (!WindowShouldClose() && Properties::currentScreen == TWOPLAYER){
        // Input.
        if (state == GAME_STATE::S_RUNNING) {
            HandleInput();

            // Getting new time.
            time += GetFrameTime();
        }

        if (state == GAME_STATE::S_PROMOTION) {
            HandleInputPromotion();
        }

        // Render.
        BeginDrawing();
        {
            std::vector<Move> movesOfSelectedPiece;

            if (selectedPiece) {
                movesOfSelectedPiece = possibleMovesPerPiece.at(selectedPiece);
            }

            Renderer::ChangeMouseCursor(board, movesOfSelectedPiece, turn, state == GAME_STATE::S_PROMOTION);
            Renderer::Clear();
            Renderer().RenderBackground();
            Renderer::RenderPieces(board, Properties::textures);

            if (state != GAME_STATE::S_PROMOTION) {
                Renderer::RenderMovesSelectedPiece(Properties::textures, movesOfSelectedPiece);
            }

            Renderer::RenderGuideText();

            // Render promotion screen.
            if (state == GAME_STATE::S_PROMOTION) {
                Renderer::RenderPromotionScreen(Properties::textures, selectedPiece->color);
            }

            // Render end-game screen.
            if (state == GAME_STATE::S_WHITE_WINS || state == GAME_STATE::S_BLACK_WINS) {
                Renderer::RenderEndScreen(state);
                Properties::currentScreen = WINLOSE;
            }
        }
        EndDrawing();
    }
}

void Game::HandleInput() {
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePosition = GetMousePosition();

        Position clickedPosition = {int(mousePosition.y) / Properties::cell_size, int(mousePosition.x) / Properties::cell_size};
        Piece* clickedPiece = board.At(clickedPosition);

        // Select piece.
        if (clickedPiece != nullptr && clickedPiece->color == turn) {
            PlaySound(Properties::sounds["click"]);
            selectedPiece = clickedPiece;
        } else {
            // Do movement.
            Move* desiredMove = GetMoveAtPosition(clickedPosition);

            if (desiredMove && selectedPiece != nullptr) {
                DoMoveOnBoard(*desiredMove);
            } else {
                PlaySound(Properties::sounds["clickCancel"]);
            }

            // Piece must still be selected to render promotion screen.
            if (!desiredMove ||
               (desiredMove->type != MOVE_TYPE::PROMOTION &&
                desiredMove->type != MOVE_TYPE::ATTACK_AND_PROMOTION)
            ) {
                selectedPiece = nullptr;
            }
        }
    }
}

void Game::HandleInputPromotion() {
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePosition = GetMousePosition();

        Position clickedPosition = {int(mousePosition.y) / Properties::cell_size, int(mousePosition.x) / Properties::cell_size};

        if (clickedPosition.i == 3 && clickedPosition.j >= 2 && clickedPosition.j <= 5) {
            Piece* newPiece;

            if (clickedPosition.j == 2) { // Clicked queen.
                newPiece = new Queen(selectedPiece->GetPosition(), selectedPiece->color);
            } else if (clickedPosition.j == 3) { // Clicked rook.
                newPiece = new Rook(selectedPiece->GetPosition(), selectedPiece->color);
            } else if (clickedPosition.j == 4) { // Clicked bishop.
                newPiece = new Bishop(selectedPiece->GetPosition(), selectedPiece->color);
            } else { // Clicked knight.
                newPiece = new Knight(selectedPiece->GetPosition(), selectedPiece->color);
            }

            // Destroy peon, create new piece at same position.
            board.Destroy(selectedPiece->GetPosition());
            board.Add(newPiece);

            // Quit promotion, deselect peon and swap turns.
            state = GAME_STATE::S_RUNNING;

            selectedPiece = nullptr;
            possibleMovesPerPiece.clear();

            SwapTurns();
        }
    }
}

Move* Game::GetMoveAtPosition(const Position& position) {
    for (auto& [piece, moves] : possibleMovesPerPiece) {
        if (piece == selectedPiece) {
            for (Move& move : moves) {
                if (move.position.i == position.i && move.position.j == position.j) {
                    return &move;
                }
            }
        }
    }
    
    return nullptr;
}

void Game::DoMoveOnBoard(const Move& move) {
    board.DoMove(selectedPiece, move);

    // If the move was a promotion move, show the promotion screen. Else, swap turns.
    if (move.type == MOVE_TYPE::PROMOTION || move.type == MOVE_TYPE::ATTACK_AND_PROMOTION) {
        state = GAME_STATE::S_PROMOTION;
    } else {
        SwapTurns();
    }
}

void Game::SwapTurns() {
    turn = Piece::GetInverseColor(turn);

    // Advance round.
    if (turn == PIECE_COLOR::C_WHITE) {
        round++;
    }

    // Calculate all possible movements for the current pieces.
    CalculateAllPossibleMovements();

    // Check for stalemates or checkmates. If so, ends the game.
    CheckForEndOfGame();
}

void Game::CalculateAllPossibleMovements() {
    possibleMovesPerPiece.clear();

    for (Piece* piece : board.GetPiecesByColor(turn)) {
        possibleMovesPerPiece[piece] = piece->GetPossibleMoves(board);
    }

    // Remove the moves that could destroy the opponent's king.
    FilterMovesThatAttackOppositeKing();

    // Remove the moves that cause the player to get in check.
    FilterMovesThatLeadToCheck();
}

void Game::CheckForEndOfGame() {
    std::vector<Piece*> piecesOfCurrentTurn = board.GetPiecesByColor(turn);

    if (board.IsInCheck(turn)) {
        // If there are no moves possible and in check, declare checkmate.
        if (!IsAnyMovePossible()) {
            state = (turn == PIECE_COLOR::C_WHITE ? GAME_STATE::S_BLACK_WINS : GAME_STATE::S_WHITE_WINS);
        }
    } else if (!IsAnyMovePossible()) {
        // If not in check and there is not any move possible, declare stalemate.
        state = GAME_STATE::S_STALEMATE;
    }
}

void Game::FilterMovesThatAttackOppositeKing() {
    for (auto& [piece, possibleMoves] : possibleMovesPerPiece) {
        for (int i = possibleMoves.size() - 1; i >= 0; i--) {
            Move& move = possibleMoves[i];

            // Remove moves that attack the opponent's king.
            bool isAttackMove = move.type == MOVE_TYPE::ATTACK || move.type == MOVE_TYPE::ATTACK_AND_PROMOTION;

            if (isAttackMove) {
                Piece* attackedPiece = board.At(move.position);

                if (attackedPiece->type == PIECE_TYPE::KING && attackedPiece->color != turn) {
                    possibleMoves.erase(possibleMoves.begin() + i);
                }
            }
        }
    }
}

void Game::FilterMovesThatLeadToCheck() {
    for (auto& [piece, possibleMoves] : possibleMovesPerPiece) {
        for (int i = possibleMoves.size() - 1; i >= 0; i--) {
            Move& move = possibleMoves[i];

            // If short castling or long castling, check for intermediary positions between king and rook.
            if (move.type == MOVE_TYPE::SHORT_CASTLING || move.type == MOVE_TYPE::LONG_CASTLING) {
                std::vector<Position> intermediaryPositions;

                if (move.type == MOVE_TYPE::SHORT_CASTLING) {
                    intermediaryPositions = {{piece->GetPosition().i, 5}, {piece->GetPosition().i, 6}};
                } else {
                    intermediaryPositions = {{piece->GetPosition().i, 3}, {piece->GetPosition().i, 2}};
                }

                for (const Position& position : intermediaryPositions) {
                    if (board.MoveLeadsToCheck(piece, {MOVE_TYPE::WALK, position})) {
                        possibleMoves.erase(possibleMoves.begin() + i);
                        break;
                    }
                }

            // If normal move.
            } else if (board.MoveLeadsToCheck(piece, possibleMoves[i])) {
                possibleMoves.erase(possibleMoves.begin() + i);
            }
        }
    }
}

bool Game::IsAnyMovePossible() {
    for (const auto& [pieceName, possibleMoves] : possibleMovesPerPiece) {
        if (!possibleMoves.empty()) {
            return true;
        }
    }

    return false;
}
