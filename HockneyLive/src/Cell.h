#pragma once

//	Cells interlinked within cells interlinked
//	Within one stem. And dreadfully distinct
//	Against the dark, a tall white fountain played.

#include "ofMain.h"

class Cell {
public:
	Cell();
	void update(int _index);
	void draw(int x, int y, int width, int height);
	void setIndex(int _index);
	void setImg(ofImage* _img) { img = _img; };
	void setGrid(vector<ofRectangle>* _grid) { grid = _grid; };
	void setSwapDuration(float _swapDuration) { swapDuration = _swapDuration; };
	void setLastSwapTime(float _lastSwapTime) { lastSwapTime = _lastSwapTime; };
	void draw(ofRectangle _rect);

private:
	float swapDuration;
	float lastSwapTime;
	int index;
	float scale;
	ofImage *img;
	vector<ofRectangle> *grid;
};