//
//  drop.hpp
//  colorRain
//
//  Created by James Bentley on 2/27/18.
//
//

#ifndef drop_hpp
#define drop_hpp

#include "ofMain.h"

class drop {
public:
    
    ofVec2f pos;
    ofColor col;
    ofColor* backgroundCol;
    float size;
    
    drop() {
        
    }
    
    void draw() {
        ofPushStyle();
        ofSetColor(col);
        ofDrawCircle(pos.x, pos.y, size);
        ofPopStyle();
    }
    
    void update() {
        size += 2.0;
        col = ofColor.lerp(col, *backgroundCol, 0.1);
    }
};

#endif /* crop_hpp */
