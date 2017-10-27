#include "Cell.h"

Cell::Cell() {

}

void Cell::setIndex(int _index) {
	index = _index;
}

void Cell::update(int _index) {
	if (ofGetElapsedTimef() - lastSwapTime > swapDuration) {
		setIndex(_index);
		lastSwapTime = ofGetElapsedTimef();
	}
}

void Cell::draw(int x, int y, int width, int height) {
	img->drawSubsection(x, y, width, height, (*grid)[index].x, (*grid)[index].y, (*grid)[index].width, (*grid)[index].height);
}

void Cell::draw(ofRectangle _rect) {
	draw(_rect.x, _rect.y, _rect.width, _rect.height);
}
