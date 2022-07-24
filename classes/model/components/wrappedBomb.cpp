#include "wrappedBomb.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/

 
/**
 * @brief Gives type of Wrapped Candy Bomb depending on colour
 *  
 * @return int
 * 
 */
int WrappedBomb::type() const {
    return Constants::associatedWrappedBomb(getColour());
}