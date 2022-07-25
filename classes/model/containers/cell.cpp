#include "cell.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Sets neighbours into four groups (above, below, vertical, horizontal)
 * 
 * @param nbs
 * 
 */
void Cell::setNbs(const std::vector< Cell * > &newNbs) {
    nbs = newNbs;
    for (int i = 0; i < static_cast<int>(nbs.size()); ++i) {
        if (i < 3) {
            aboveNbs[i] = nbs[i];
            if (i == 1 && nbs[i]) vertNbs.push_back(nbs[i]);
        }
        else if (i < 5 && nbs[i]) horizNbs.push_back(nbs[i]);
        else {
            belowNbs[i - 5] = nbs[i];
            if (i == 6 && nbs[i]) vertNbs.push_back(nbs[i]);
        }
    }
}