/**
 * @file gridDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of 
 *  a the entire Grid.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "animation/animationQueue.hpp"
#include "components/componentDisplay.hpp"
#include "components/candyDisplay.hpp"
#include "components/stripedDisplay.hpp"
#include "components/wrappedDisplay.hpp"
#include "components/specialDisplay.hpp"
#include "components/wallDisplay.hpp"
#include "components/cherryDisplay.hpp"
#include "components/hazelnutDisplay.hpp"
#include "components/frostingDisplay.hpp"
#include "cellDisplay.hpp"
#include "text/broadcast.hpp"
#include "common/background.hpp"
#include "../common/componentType.hpp"

#include <memory>
#include <vector>
#include <queue>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class GridDisplay {

    const int ROWS = Constants::ROWS;
    const int COLS = Constants::COLS;

    using CellMatrix = std::vector< std::vector<CellDisplay> >;
    CellMatrix visualGrid;
    
    using ComponentMatrix = std::vector< std::vector< std::shared_ptr<ComponentDisplay> > >;
    ComponentMatrix visualComponents;

    using CoordComponent = std::pair< Point, ComponentType >;
    using CoordPair = std::pair< Point, Point >;
    enum class Animations{Pop, Fill, DropDown, DropLeft, DropRight, Swap};
    AnimationQueue animationQueue;

    CoordPair suggestion;
    
    int time = 0;
    const int suggestionTime = 90; 

    BroadcastBox broadcast;
    Background bg{FL_GRAY};

public:
    GridDisplay();
    GridDisplay(const GridDisplay &) = default;
    GridDisplay(GridDisplay &&) = default;

    void draw();
    bool inAnimation() const;
    void notifyInit(const Point &coord, const ComponentType &type);

    /** Queues insert animation */
    void notifyInsert(const Point &coord, const ComponentType &type) {animationQueue.enqueueFill({{coord, type}});}
    void notifyInsert(const std::vector<CoordComponent> &toInsert) {animationQueue.enqueueFill(toInsert);}

    /** Queues fill animation */
    void notifyFill(const std::vector<CoordComponent> &toFill) {animationQueue.enqueueFill(toFill);}

    /** Queues insert animation */
    void notifyDrop(const std::vector<Point> &toDrop, Beneath direction) {animationQueue.enqueueDrop(toDrop, direction);}

    /** Queues pop animation */
    void notifyPop(const std::vector<Point> &toPop) {animationQueue.enqueuePop(toPop);}

    void notifySuggestion(const Point &start, const Point &dest) {suggestion = {start, dest};}

    void notifySwap(const Point &start, const Point &dest);
    void notifyFailedSwap(const Point &start, const Point &dest);

    void notifySwapsLeft(int swaps) {broadcast.setSwaps(swaps);}
    void notifyNoSwaps();
    void notifyGameState(GameState state);
    void notifyObjective(ObjectiveType objType, int obj);
    void notifyObjective(ObjectiveType objType, int obj, Colour colour);
    
    void notifyReset();

    /** Modifies score displayed */
    void notifyScore(int newScore) {broadcast.setScore(newScore);}

private:

    void resetGrid();


    void won() {broadcast.setMessage(Constants::GAME_WON);}
    void lost() {broadcast.setMessage(Constants::GAME_LOST);}

    /* Animations */
    void nextAnimation();
    void performFill();
    void performDrop(Beneath direction);
    void performPop();
    void performSwap();
    void performSuggestion();

    /* Utility */
    Point calculateCenter(const Point &coord) const;
    std::shared_ptr<ComponentDisplay> factoryMethod(int row, int col, const ComponentType &type) const;

};

#endif