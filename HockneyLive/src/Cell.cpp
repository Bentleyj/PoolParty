#include "Cell.h"

Cell::Cell() {
	float randomRange = 50;
	randomOffset.x = ofRandom(-randomRange, randomRange);
	randomOffset.y = ofRandom(-randomRange, randomRange);
	randomOffset.z = ofRandom(0, randomRange);
}

void Cell::update(ofRectangle _rect) {
	if (ofGetElapsedTimef() - lastSwapTime > swapDuration) {
		float randomRange = 50;
		inputRect = _rect;
		randomOffset.x = ofRandom(-randomRange, randomRange);
		randomOffset.y = ofRandom(-randomRange, randomRange);
		randomOffset.z = ofRandom(0, randomRange);

		lastSwapTime = ofGetElapsedTimef();
	}
}

void Cell::draw(int x, int y, int width, int height) {
	img->drawSubsection(x, y, width, height, inputRect.x + randomOffset.x, inputRect.y + randomOffset.y, inputRect.width + randomOffset.z, inputRect.height + randomOffset.z);
}

void Cell::draw(ofRectangle _rect) {
	draw(_rect.x, _rect.y, _rect.width, _rect.height);
}
