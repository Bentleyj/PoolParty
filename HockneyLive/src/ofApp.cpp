#include "ofApp.h"
#define NUM_CELLS_X 5
#define NUM_CELLS_Y 5

//--------------------------------------------------------------
void ofApp::setup() {
	cameraStream.setup(1920, 1080);

	analyzer.setup(&cameraStream);

	float OffsetAmount = 50;
	float xOffset = 0;
	float yOffset = 0;
	float widthOffset = 0;
	float heightOffset = 0;
	int smallCellWidth = analyzer.width * analyzer.scale / NUM_CELLS_X;
	int smallCellHeight = analyzer.height * analyzer.scale / NUM_CELLS_Y;
	for (int x = 0; x < NUM_CELLS_X; x++) {
		for (int y = 0; y < NUM_CELLS_Y; y++) {

			flowRectangle small;
			small.rect = ofRectangle(x+1, y+1, smallCellWidth-2, smallCellHeight-2);
			small.flowMag = 0;
			small.flow = ofVec2f(0, 0);
			small.id = id;
			id++;

			ofRectangle large = ofRectangle(x * analyzer.scale, y * analyzer.scale, smallCellWidth * analyzer.scale, smallCellHeight * analyzer.scale);

			small.outputRect = large;

			smallGrid.push_back(small);
		}
	}

	int spacing = 10;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			ofRectangle rect;
			rect.width = smallCellHeight * analyzer.scale;
			rect.height = smallCellHeight * analyzer.scale;
			rect.x = x * rect.width + spacing * x + spacing;
			rect.y = y * rect.height + spacing * y + spacing;
			displayPositions.push_back(rect);
		}
	}

	cells.resize(displayPositions.size());
	int duration = 30;
	for (int i = 0; i < cells.size(); i++) {
		//cells[i].setImg(&(analyzer.largeImg));
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

	ofSetBackgroundAuto(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	cameraStream.update();
	if (ofGetElapsedTimef() - lastCheckTime > timeBetweenChecks) {
		flow.resetFlow();
		lastCheckTime = ofGetElapsedTimef();
	}

	float lastCheckTime;
	if(cameraStream.isFrameNew()) {
		analyzer.copyImage();
		//analyzer.largeImg.update();
		for (int i = 0; i < smallGrid.size(); i++) {
			smallGrid[i].calculateFlow(&flow);
		}
		std::sort(smallGrid.begin(), smallGrid.end(), compareFlow);

		int index = ofRandom(0, 4);
		//for (int i = 0; i < cells.size(); i++) {
		//	cells[i].update(smallGrid[index].outputRect);
		//}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);

	//analyzer.largeImg.draw(0, 0);
	//flow.draw();
	//for (int i = 0; i < cells.size(); i++) {
	//	cells[i].draw(displayPositions[i]);
	//}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	analyzer.startThread();
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
