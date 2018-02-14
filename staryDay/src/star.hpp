//
//  star.hpp
//  staryDay
//
//  Created by cafe on 14/02/2018.
//

#ifndef star_hpp
#define star_hpp

#include "ofMain.h"

class star {
public:
    star() {};
    double ra, de;
    string catID;
    float mag;
    ofVec3f p;
};

#endif /* star_hpp */
