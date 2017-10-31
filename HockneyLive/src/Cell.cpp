#include "Cell.h"

Cell::Cell() {

}

void Cell::setOutputRect() {
	float randomRange = 50;
	ofVec3f randomOffset;
	randomOffset.x = ofRandom(-randomRange, randomRange);
	randomOffset.y = ofRandom(-randomRange, randomRange);
	randomOffset.z = ofRandom(0, randomRange);
	offsetInputRect.x = inputRect.x + randomOffset.x;
	offsetInputRect.y = inputRect.y + randomOffset.y;
	offsetInputRect.width = inputRect.width + randomOffset.z;
	offsetInputRect.height = inputRect.height + randomOffset.z;

	if (offsetInputRect.x < 0) {
		float offLeft = abs(offsetInputRect.x);
		offsetInputRect.x = 0;
		offsetInputRect.width += offLeft;
	}
	if (offsetInputRect.y < 0) {
		float offTop = abs(offsetInputRect.y);
		offsetInputRect.y = 0;
		offsetInputRect.height += offTop;
	}
	if (offsetInputRect.x + offsetInputRect.width > img->getWidth()) {
		float offRight = img->getWidth() - offsetInputRect.x + offsetInputRect.width;
		offsetInputRect.x -= offRight;
		offsetInputRect.width -= offRight;
	}
	if (offsetInputRect.y + offsetInputRect.height > img->getHeight()) {
		float offBottom = offsetInputRect.height - (img->getHeight() - offsetInputRect.y);
		offsetInputRect.y -= offBottom;
		offsetInputRect.height -= offBottom;
	}
}

void Cell::update(ofRectangle _rect) {
	if (ofGetElapsedTimef() - lastSwapTime > swapDuration) {

		float randomRange = 50;

		inputRect = _rect;

		setOutputRect();

		lastSwapTime = ofGetElapsedTimef();
	}
}

void Cell::draw(int x, int y, int width, int height) {
	img->drawSubsection(x, y, width, height, offsetInputRect.x, offsetInputRect.y, offsetInputRect.width, offsetInputRect.height);
}

void Cell::draw(ofRectangle _rect) {
	draw(_rect.x, _rect.y, _rect.width, _rect.height);
}
