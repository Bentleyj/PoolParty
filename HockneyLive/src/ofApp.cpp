#include "ofApp.h"
#define CELL_WIDTH 20
#define CELL_HEIGHT 20

//--------------------------------------------------------------
void ofApp::setup(){
	cameraStream.setup(1920, 1080);
	largeImg.allocate(cameraStream.getWidth(), cameraStream.getHeight(), OF_IMAGE_COLOR);
	smallImg.allocate(largeImg.getWidth() / IMG_SCALE, largeImg.getHeight() / IMG_SCALE, OF_IMAGE_COLOR);
	smallGray.allocate(largeImg.getWidth() / IMG_SCALE, largeImg.getHeight() / IMG_SCALE, OF_IMAGE_GRAYSCALE);

	int id = 0;

	float OffsetAmount = 50;
	float xOffset = 0;
	float yOffset = 0;
	float widthOffset = 0;
	float heightOffset = 0;
	for (int x = 0; x < smallImg.getWidth() - CELL_WIDTH; x += CELL_WIDTH) {
		if (x == 0)
			xOffset = 0;
		else
			xOffset = OffsetAmount;
		if (x == smallImg.getWidth() - CELL_WIDTH * 2)
			widthOffset = 0;
		else
			widthOffset = OffsetAmount;
		for (int y = 0; y < smallImg.getHeight() - CELL_HEIGHT; y += CELL_HEIGHT) {
			if (y == 0)
				yOffset = 0;
			else
				yOffset = OffsetAmount;
			if (y == smallImg.getHeight() - CELL_HEIGHT * 2)
				heightOffset = 0;
			else
				heightOffset = OffsetAmount;
			flowRectangle small;
			small.rect = ofRectangle(x, y, CELL_WIDTH, CELL_HEIGHT);
			small.flowMag = 0;
			small.flow = ofVec2f(0, 0);
			small.id = id;
			id++;

			ofRectangle large = ofRectangle(x * IMG_SCALE - xOffset, y * IMG_SCALE - yOffset, CELL_WIDTH * IMG_SCALE + widthOffset*2, CELL_HEIGHT * IMG_SCALE + heightOffset*2);

			small.outputRect = large;

			smallGrid.push_back(small);

			ofRectangle displayPos = large;
		}
	}

	int spacing = 10;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			ofRectangle rect;
			rect.width = CELL_WIDTH * IMG_SCALE + widthOffset * 2;
			rect.height = CELL_HEIGHT * IMG_SCALE + heightOffset * 2;
			rect.x = x * rect.width + spacing * x + spacing;
			rect.y = y * rect.height + spacing * y + spacing;
			displayPositions.push_back(rect);
		}
	}

	cells.resize(displayPositions.size());
	int duration = 30;
	for (int i = 0; i < cells.size(); i++) {
		cells[i].setImg(&largeImg);
		cells[i].setInputRect(smallGrid[ofRandom(0, cells.size())].outputRect);
		cells[i].setSwapDuration(duration);
		float start = ofRandom(-duration, 0);
		cells[i].setLastSwapTime(start);
	}


	for (int i = 0; i < smallGrid.size(); i++) {
		sortedFlowRectangles.push_back(i);
	}

	lastCheckTime = 0;
	timeBetweenChecks = 20;
}

//--------------------------------------------------------------
void ofApp::update(){
	cameraStream.update();
	if (ofGetElapsedTimef() - lastCheckTime > timeBetweenChecks) {
		flow.resetFlow();
		lastCheckTime = ofGetElapsedTimef();
	}

	float lastCheckTime;
	if(cameraStream.isFrameNew()) {
		ofxCv::copy(cameraStream, largeImg);
		ofxCv::resize(cameraStream, smallImg);
		ofxCv::copyGray(smallImg, smallGray);
		smallGray.update();
		largeImg.update();
		flow.calcOpticalFlow(smallGray);
		for (int i = 0; i < smallGrid.size(); i++) {
			smallGrid[i].calculateFlow(&flow);
		}
		std::sort(smallGrid.begin(), smallGrid.end(), compareFlow);

		int index = ofRandom(0, 4);
		for (int i = 0; i < cells.size(); i++) {
			cells[i].update(smallGrid[index].outputRect);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);

	for (int i = 0; i < cells.size(); i++) {
		cells[i].draw(displayPositions[i]);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
