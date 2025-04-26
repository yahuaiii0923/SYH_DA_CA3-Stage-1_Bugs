//
// Created by Siew Yahuai on 31/03/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, int x, int y, int dir, int size);


    void move() override;
};

#endif //CRAWLER_H
