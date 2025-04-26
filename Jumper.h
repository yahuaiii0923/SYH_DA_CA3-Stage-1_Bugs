#ifndef JUMPER_H
#define JUMPER_H

#include "Bug.h"

class Jumper : public Bug {
private:
    int jumpCounter; // count jumps
    
public:
    Jumper(int id, int x, int y, int dir, int size);
    
    // override the function from Bug
    void move() override;
};

#endif // JUMPER_H