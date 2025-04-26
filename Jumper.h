#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength; // count jumps 2-4square
    
public:
    Hopper(int id, int x, int y, int dir, int size);
    
    // override the function from Bug
    void move() override;
};

#endif // HOPPER_H