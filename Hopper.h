//
// Created by Siew Yahuai on 26/04/2025.
//

#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"
#include <cstdlib>

class Hopper : public Bug {
private:
    int hopLength; // for jump move (2-4 squares)

public:
    Hopper(int id, int x, int y, int dir, int size);

    int getHopLength() const {
        return hopLength;
    }

    void move() override;
};

#endif //HOPPER_H
