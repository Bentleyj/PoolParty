#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	frame f1;
	frame f2;

	img1.load("images/maps/coastline drone/Gabriel-Scanu-2.jpg");
	img2.load("images/maps/coastline drone/d964bb35d4a94351a1c6301edad31573.jpg");

	f1.x = 20;
	f1.y = 20;
	f1.width = 400;
	f1.height = 1000;
	f1.img = &img1;

	f2.x = f1.width + 40;
	f2.y = 20;
	f2.width = 400;
	f2.height = 1000;
	f2.img = &img2;

	f1.lines = &lines1;
	f2.lines = &lines2;

	frames.push_back(f1);
	frames.push_back(f2);

	linkPoint.x = ofGetWidth() / 2;
	linkPoint.y = ofGetHeight() / 2;

	ofBackground(210);
}

//--------------------------------------------------------------
void ofApp::update(){
	frames[0].x = ofGetMouseX();
	frames[0].y = ofGetMouseY();

	frames[1].x = ofGetMouseX() + 20 + frames[0].width;
	frames[1].y = ofGetMouseY();

	//if (lines2.size() > 0) {
	//	vector<ofPoint> verts = lines2[0].getVertices();

	//	for (int i = 0; i < verts.size(); i++) {
	//		verts[i].y += diff;
	//	}
	//	lines2[0].clear();
	//	lines2[0].addVertices(verts);
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	if (state == draw1) {
		img1.draw(0, 0);
	}
	if (state == draw2) {
		img2.draw(0, 0);
	}

	if (state == display) {
		float endPoint0 = frames[0].endPoint.y;
		float startPoint1 = frames[1].startPoint.y;
		float diff = endPoint0 - startPoint1;

		ofSetColor(255, 255, 0);
		frames[0].draw(0);

		ofSetColor(0, 255, 255);
		frames[1].draw(diff);
	}
	else {
		ofPushStyle();
		ofSetColor(255);
		for (int i = 0; i < frames.size(); i++) {
			frames[i].draw(0);
		}
		ofSetColor(255, 255, 0);
		for (int i = 0; i < lines1.size(); i++) {
			lines1[i].draw();
		}
		ofSetColor(0, 255, 255);
		for (int i = 0; i < lines2.size(); i++) {
			lines2[i].draw();
		}
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		lines1.clear();
		lines2.clear();
		//frames.clear();
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
		lines1[lines1.size()-1].addVertex(x, y);
	}
	else if (state == draw2) {
		lines2[lines2.size() - 1].addVertex(x, y);
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
		ofPolyline line;
	if (state == draw1) {
		lines1.push_back(line);
	}
	else if (state == draw2) {
		lines2.push_back(line);
	}
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
