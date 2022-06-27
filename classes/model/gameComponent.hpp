#ifndef CELL_HPP
#define CELL_HPP

#include "../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class GameComponent {
    std::vector< std::shared_ptr<GameComponent> > neighbours;
public:
    virtual ~GameComponent() {};
    virtual std::string package() const=0;
    virtual void setNeighbours(const std::vector< std::shared_ptr<GameComponent> > &nbs) {neighbours = nbs;}
    virtual std::vector< std::shared_ptr<GameComponent> > getNeighbours() const {return neighbours;}
};

#endif