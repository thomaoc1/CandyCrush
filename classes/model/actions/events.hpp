#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "../point.hpp"
#include "action.hpp"

#include <vector>
#include <memory>


class Events {
    std::vector< std::shared_ptr<Action> > moves;
public:
    void addAction(std::shared_ptr<Action> action);
    void reset() {moves.clear();}
    int eventLength() const {return static_cast<int>(moves.size());}
    std::shared_ptr<Action> getAction(int i) const {return moves[i];}
};


#endif