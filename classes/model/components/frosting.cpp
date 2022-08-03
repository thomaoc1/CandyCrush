#include "frosting.hpp"


int Frosting::pop() {
    --layers;
    if (layers >= 1) return Constants::NOT_POPPED;
    return Constants::POPPED;
}