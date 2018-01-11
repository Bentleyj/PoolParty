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
    line* comparatorLine;
    ofShader noiseWobble;
    int noiseIterations;
    float noiseSize;
    float noiseSpeed;
    float noiseScale;
    
    line();
    void setup();
    void update();
    void draw();

};

#endif /* line_hpp */
