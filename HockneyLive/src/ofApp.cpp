#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	cameraStream.setup(1920, 1080);

	analyzer.setup(&cameraStream);

	largeImg.allocate(1920, 1080, OF_IMAGE_COLOR);

	outputRectangles = analyzer.getOutputRectangles();

	int spacing = 10;
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			ofRectangle rect;
			rect.width = 100;
			rect.height = 100;
			rect.x = x * rect.width + spacing * x + spacing;
			rect.y = y * rect.height + spacing * y + spacing;
			displayPositions.push_back(rect);
		}
	}

	cells.resize(displayPositions.size());
	int duration = 10;
	for (int i = 0; i < cells.size(); i++) {
		cells[i].setImg(&largeImg);
		cells[i].setInputRect(ofRectangle(0, 0, 100, 100));
		cells[i].setSwapDuration(duration);
		float start = ofRandom(-duration, 0);
		cells[i].setLastSwapTime(start);
        cells[i].setScale(analyzer.scale);
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
        ofxCv::copy(cameraStream, largeImg);
        largeImg.update();
		if(!analyzer.isThreadRunning())
			analyzer.startThread();
	}

	int index = ofRandom(0, 4);
	for (int i = 0; i < cells.size(); i++) {
		mutex.lock();
		cells[i].update(outputRectangles[analyzer.orderedIDs[0]]);
		mutex.unlock();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
    
	for (int i = 0; i < cells.size(); i++) {
		cells[i].draw(displayPositions[i]);
	}
    
    ofPushMatrix();
    ofTranslate( 600, 0 );
    largeImg.draw(0, 0);
    for (int i = 0; i < cells.size(); i++) {
        cells[i].drawDebug();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//analyzer.startThread();
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
