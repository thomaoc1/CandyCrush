#include "frosting.hpp"
#include <iostream>

ComponentState Frosting::pop() {
    --layers;
    if (layers == 1) {
        compType.type = Component::FROSTING1;
        return ComponentState::NOT_POPPED;
    }
    return ComponentState::POPPED;
}