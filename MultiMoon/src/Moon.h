//
//  Moon.hpp
//  MultiMoon
//
//  Created by cafe on 09/01/2018.
//

#ifndef Moon_hpp
#define Moon_hpp

#include "ofMain.h"

class Moon {
public:
    float x, y, targetY, width, radius, offset, speed;
    ofParameter<float>* horizon;
    ofColor color;
    
    Moon();
    void draw();
    void drawTop();
    void drawBottom();
    void update();
    void rise(float target) {
        targetY = target;
    };
    void set() {
        targetY = ofGetHeight();
    };
    float max(float a, float b);
    
};

#endif /* Moon_hpp */
