#include "ofApp.h"
#define CELL_WIDTH 20
#define CELL_HEIGHT 20

//--------------------------------------------------------------
void ofApp::setup(){
	cameraStream.setup(1920, 1080);
	largeImg.allocate(1920, 1080, OF_IMAGE_COLOR);
	smallImg.allocate(192, 108, OF_IMAGE_COLOR);
	smallGray.allocate(192, 108, OF_IMAGE_GRAYSCALE);

	for (int x = 0; x < smallImg.getWidth() - CELL_WIDTH; x += CELL_WIDTH) {
		for (int y = 0; y < smallImg.getHeight() - CELL_HEIGHT; y += CELL_HEIGHT) {
			Grid.push_back(ofRectangle(x, y, CELL_WIDTH, CELL_HEIGHT));
		}
	}

	timeBetweenChecks = 1.0;
	lastCheckTime = 0.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
	cameraStream.update();
	if(cameraStream.isFrameNew()) {
		ofxCv::copy(cameraStream, largeImg);
		ofxCv::resize(cameraStream, smallImg);
		ofxCv::copyGray(smallImg, smallGray);
		smallGray.update();
		smallImg.update();
		largeImg.update();
		flow.calcOpticalFlow(smallGray);
		if (timeBetweenChecks < ofGetElapsedTimef() - lastCheckTime) {
			float topFlow = 0;
			for (int i = 0; i < Grid.size(); i++) {
				ofVec2f f = flow.getAverageFlowInRegion(Grid[i]);
				float l = sqrt(f.x*f.x + f.y*f.y);
				if (l > topFlow) {
					topFlow = l;
					topFlowIndex = i;
				}
			}
			lastCheckTime = ofGetElapsedTimef();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	largeImg.draw(0, 0);
	ofPushMatrix();
	ofPushStyle();
	ofScale(10, 10);
	flow.draw();
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofDrawRectangle(Grid[topFlowIndex].x, Grid[topFlowIndex].y, Grid[topFlowIndex].width, Grid[topFlowIndex].height);
	ofPopStyle();
	ofPopMatrix();
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);

	largeImg.drawSubsection(0, largeImg.getHeight() + 10, CELL_WIDTH * 10, CELL_WIDTH * 10, Grid[topFlowIndex].x * 10, Grid[topFlowIndex].y * 10, Grid[topFlowIndex].width * 10, Grid[topFlowIndex].height * 10);
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
