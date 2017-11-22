#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	Frame f1;
	Frame f2;

	//img1.load("images/maps/coastline drone/Gabriel-Scanu-2.jpg");
	//img2.load("images/maps/coastline drone/d964bb35d4a94351a1c6301edad31573.jpg");

	f1.x = 100;
	f1.y = 100;
	f1.width = 400;
	f1.height = 1000;
	//f1.img = &img1;

	f2.x = f1.width + 120;
	f2.y = 100;
	f2.width = 400;
	f2.height = 1000;
	//f2.img = &img2;

	f1.line = &line1;
	f2.line = &line2;

	frames.push_back(f1);
	frames.push_back(f2);

	linkPoint.x = ofGetWidth() / 2;
	linkPoint.y = ofGetHeight() / 2;

	ofBackground(210);
    
    state = draw1;
}

//--------------------------------------------------------------
void ofApp::update(){
	frames[0].x = ofGetMouseX() - 10 - frames[0].width;
    
	frames[1].x = ofGetMouseX() + 10 ;
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	if (state == draw1) {
		img1.draw(0, 0);
        ofSetColor(255, 255, 0);
        line1.draw();
	}
	if (state == draw2) {
		img2.draw(0, 0);
        ofSetColor(0, 255, 255);
        line2.draw();
	}

	if (state == display) {
		float endPoint0 = frames[0].endPoint.y;
		float startPoint1 = frames[1].startPoint.y;
        float target = ofGetMouseY();
		float diff1 = (target - endPoint0);
        float diff2 = (target - startPoint1);

		ofSetColor(255, 255, 0);
		frames[0].draw();

		ofSetColor(0, 255, 255);
		frames[1].draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		line1.clear();
		line2.clear();
	}
	if (key == '1') {
		state = draw1;
	}
	if (key == '2') {
		state = draw2;
	}
	if (key == 'f') {
		state = display;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (state == draw1) {
		line1.addVertex(x, y);
	}
	else if (state == draw2) {
		line2.addVertex(x, y);
	}

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
