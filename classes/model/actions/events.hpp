#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "../point.hpp"
#include "action.hpp"

#include <vector>
#include <memory>


class Events {
    std::vector< std::shared_ptr<Action> > moves;
public:
    bool occurrence() const {return moves.size() > 0;}
    void addAction(std::shared_ptr<Action> action) {moves.push_back(action);}
    int eventLength() const {return static_cast<int>(moves.size());}

    void reset() {moves.clear();}
    std::shared_ptr<Action> getAction(int i) const {return moves[i];}

    bool operator==(const Events &other) const {return moves == other.moves;}
    bool operator!=(const Events &other) const {return moves != other.moves;}
};


#endif