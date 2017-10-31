#pragma once

//	Cells interlinked within cells interlinked
//	Within one stem. And dreadfully distinct
//	Against the dark, a tall white fountain played.

#include "ofMain.h"

class Cell {
public:
	Cell();
	void update(ofRectangle _rect);
	void draw(int x, int y, int width, int height);
	void setImg(ofImage* _img) { img = _img; };
	void setInputRect(ofRectangle _rect) { inputRect = _rect; };
	void setSwapDuration(float _swapDuration) { swapDuration = _swapDuration; };
	void setLastSwapTime(float _lastSwapTime) { lastSwapTime = _lastSwapTime; };
	void draw(ofRectangle _rect);

private:
	float swapDuration;
	float lastSwapTime;
	float scale;
	ofImage *img;
	ofRectangle inputRect;
	ofRectangle offsetInputRect;
};