#include "frosting.hpp"


ComponentState Frosting::pop() {
    --layers;
    if (layers >= 1) return ComponentState::NOT_POPPED;
    return ComponentState::POPPED;
}