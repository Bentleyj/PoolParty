#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	bool setup = cameraStream.setup(1920, 1080);

	analyzer.setup(&cameraStream);

	largeImg.allocate(1920, 1080, OF_IMAGE_COLOR);

	outputRectangles = analyzer.getOutputRectangles();
    
    crossProcess.load("shaders/crossProcess");
    
    curveTexture.load("images/curve.jpg");

	int spacing = 10;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			ofRectangle rect;
			rect.width = 400;
			rect.height = 400;
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
    
    gui.setup("Gui", "settings/settings.xml");
    gui.add(flowScale.set("Flow Scale", 200.0, 0.0, 200.0));
	gui.add(drawDebug.set("Draw Debug", false));
	gui.setPosition(displayPositions[displayPositions.size() - 1].x + displayPositions[displayPositions.size() - 1].width + 20, 0);

	gui.loadFromFile("settings/settings.xml");

	ofSetBackgroundAuto(false);
    
    ofSetFrameRate(120);
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

	int index = ofRandom(20);
	for (int i = 0; i < cells.size(); i++) {
        cells[i].setScale(flowScale);
		mutex.lock();
		cells[i].update(outputRectangles[analyzer.orderedIDs[index]], analyzer.orderedFlows[index]);
		mutex.unlock();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
    
    crossProcess.begin();
    crossProcess.setUniformTexture("curveTex", curveTexture, 1);
    crossProcess.setUniform1f("curveWidth", curveTexture.getWidth());
    crossProcess.setUniform1f("curveHeight", curveTexture.getHeight());

	for (int i = 0; i < cells.size(); i++) {
		cells[i].draw(displayPositions[i]);
	}
    
	if (drawDebug) {
		ofPushMatrix();
		ofTranslate(displayPositions[displayPositions.size() - 1].x + displayPositions[displayPositions.size() - 1].width + 20, 0);
		largeImg.draw(0, 0);
		for (int i = 0; i < cells.size(); i++) {
			cells[i].drawDebug();
		}
		ofPopMatrix();
	}
	crossProcess.end();

    gui.draw();
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
