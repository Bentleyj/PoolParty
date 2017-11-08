#pragma once

//	Cells interlinked within cells interlinked
//	Within one stem. And dreadfully distinct
//	Against the dark, a tall white fountain played.

#include "ofMain.h"

class Cell {
public:
    // Constructor
	Cell();
    //Setters
    void setImg(ofImage* _img) { img = _img; };
    void setInputRect(ofRectangle _rect) { inputRect = _rect; }; //  This is the LARGE rectangle from which we sample our image
    void setSwapDuration(float _swapDuration) { swapDuration = _swapDuration; };
    void setLastSwapTime(float _lastSwapTime) { lastSwapTime = _lastSwapTime; };
    void setScale(float _scale) { scale = _scale; };

    //Getters
    
    //Functionality
	void update(ofRectangle _rect, ofVec2f flow);
    
	void draw(int x, int y, int width, int height);
    
	void drawDebug();
    
	void draw(ofRectangle _rect);

	void resizeInputRect();

private:
	float swapDuration;
	float lastSwapTime;
	float scale;
    ofColor debugColor;
	ofImage *img;
	ofRectangle inputRect;
	ofRectangle offsetInputRect;
    ofVec2f flow;
};
