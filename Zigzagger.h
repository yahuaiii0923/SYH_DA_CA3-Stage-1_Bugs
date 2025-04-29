//
// Created by plo on 27/04/2025.
//

#ifndef ZIGZAGGER_H
#define ZIGZAGGER_H
#include "Bug.h"

class Zigzagger : public Bug {
private:
    bool zigPhase;  //trakcs whether forward or diagonal
public:
    Zigzagger(int id, int x, int y, int dir, int size);
    void move() override;
};

#endif //ZIGZAGGER_H