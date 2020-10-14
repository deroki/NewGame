#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "character.h"

class Controller {
    public:
        void HandleInput(Character &character, bool& running) const;

};

#endif