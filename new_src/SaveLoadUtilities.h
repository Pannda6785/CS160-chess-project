#ifndef SAVE_LOAD_UTILITIES_H
#define SAVE_LOAD_UTILITIES_H

#include <fstream>
#include <string>
#include "Properties.h"

namespace SaveLoadUtilities {
    inline bool IsSlotEmpty(int slot) {
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        // Check if the file exists and has content
        if (!savefile.is_open() || savefile.peek() == std::ifstream::traits_type::eof()) {
            return true;  // The file doesn't exist or is empty
        }

        return false;  // The file exists and is not empty
    }

    inline std::string GetDifficulty(int slot) { // only when is 1 Player. {"Easy", "Normal", "Hard"}
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        std::string agent1, agent2;
        int turn; 
        savefile >> agent1 >> agent2 >> turn;
        
        if (agent1 == "Bot1" || agent2 == "Bot1") return "Easy";
        if (agent1 == "Bot2" || agent2 == "Bot2") return "Normal";
        if (agent1 == "Bot3" || agent2 == "Bot3") return "Hard";
        return "What";
    }

    inline std::string GetMode(int slot) { // {"1 Player", "2 Player"} 
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        std::string agent1, agent2;
        int turn; 
        savefile >> agent1 >> agent2 >> turn;

        if (agent1 == "Human" && agent2 == "Human") return "2 Player";
        return "1 Player " + GetDifficulty(slot);
    }

    inline std::string GetPlayerColor(int slot) { // only when is 1 PLayer, {"White", "Black"}
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        std::string agent1, agent2;
        int turn; 
        savefile >> agent1 >> agent2 >> turn;
        
        if (agent1 == "Human") return "White";
        return "Black";
    }

    inline std::string GetTurn(int slot) { // number of turn passed
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        std::string agent1, agent2;
        int turn; 
        savefile >> agent1 >> agent2 >> turn;

        return std::to_string(turn);
    }

    inline std::string GetWhoseTurn(int slot) { // "White" or "Black"
        std::ifstream savefile(Properties::GetSavefilePath(slot));

        std::string agent1, agent2;
        int turn; 
        savefile >> agent1 >> agent2 >> turn;

        if (turn & 1) {
            return "White";
        } else {
            return "Black";
        }
    }

}

#endif //SAVE_LOAD_UTILITIES_H