//
//  Cell.hpp
//  FluidSim
//
//  Created by cafe on 12/02/2018.
//
// This is a fluid simulation cell. It has a position in a grid as well as a velocity associated with it.

#ifndef Cell_hpp
#define Cell_hpp

#include "ofMain.h"

class Cell {
public:
    Cell() {
        u.x = ofRandom(-0.5, 0.5);
        u.y = ofRandom(-0.5, 0.5);
    }
    ofVec2f u;
};

#endif /* Cell_hpp */
