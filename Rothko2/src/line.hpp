//
//  line.hpp
//  Rothko2
//
//  Created by cafe on 11/01/2018.
//

#ifndef line_hpp
#define line_hpp

#include "ofMain.h"

class line {
public:
    vector<ofVec2f> points;
    ofShader noiseWobble;
    ofColor col;
    int sign;
    int noiseIterations;
    float noiseSize;
    float noiseSpeed;
    float noiseScale;
    float offset;
    float baseHeight;
    
    line();
    void setup();
    void update(line* comparatorLine);
    void draw();

};

#endif /* line_hpp */
