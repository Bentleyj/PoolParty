#include "ofApp.h"

#define NUM_VIDEOS 9

//--------------------------------------------------------------
void ofApp::setup(){

	ofxNestedFileLoader loader;
	videoPaths = loader.load("videos");

	for (int i = 0; i < NUM_VIDEOS; i++) {
		ofVideoPlayer* vp = new ofVideoPlayer();
		videoPlayers.push_back(vp);
	}

	for (int i = 0; i < videoPlayers.size(); i++) {
		int val = (int)ofRandom(videoPaths.size());
		bool loaded = videoPlayers[i]->load(videoPaths[val]);
		videoPlayers[i]->setLoopState(OF_LOOP_NONE);
		videoPlayers[i]->play();
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < videoPlayers.size(); i++) {
		videoPlayers[i]->update();
		if (videoPlayers[i]->getIsMovieDone()) {
			int val = (int)ofRandom(videoPaths.size());
			videoPlayers[i]->load(videoPaths[val]);
			videoPlayers[i]->setLoopState(OF_LOOP_NONE);
			videoPlayers[i]->play();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	int x = 50;
	int y = 50;
	float size = 500;
	for (int i = 0; i < videoPlayers.size(); i++) {
		videoPlayers[i]->draw(x, y, 500, 500);
		x += size + 50;
		if (x + size + 50 > ofGetWidth()) {
			y += size + 50;
			x = 50;
		}
	}

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
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
