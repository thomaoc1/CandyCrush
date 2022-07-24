#include "stripedBomb.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/

 
/**
 * @brief Gives type of Striped Candy Bomb depending on colour
 *  
 * @return int
 * 
 */
int StripedBomb::type() const {
    return Constants::associatedStripedBomb(getColour(), getBlastDirection());
}