#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	frame f1;

	f1.x = 20;
	f1.y = 20;
	f1.width = 200;
	f1.height = 200;

	f1.lines = &lines;

	frames.push_back(f1);

	linkPoint.x = ofGetWidth() / 2;
	linkPoint.y = ofGetHeight() / 2;
}

//--------------------------------------------------------------
void ofApp::update(){
	frames[0].x = ofGetMouseX();
	frames[0].y = ofGetMouseY();

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < lines.size(); i++) {
		lines[i].draw();
	}
	if (!drawingLines) {
		for (int i = 0; i < frames.size(); i++) {
			frames[i].draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		lines.clear();
		//frames.clear();
	}
	if (key == 'd') {
		drawingLines = !drawingLines;
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
	if (drawingLines) {
		lines[lines.size()-1].addVertex(x, y);
	}

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (drawingLines) {
		ofPolyline line;
		lines.push_back(line);
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
