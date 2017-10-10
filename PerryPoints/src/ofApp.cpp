#include "ofApp.h"
#define NUM_STEPS 500

//--------------------------------------------------------------
void ofApp::setup(){
	img.load("Tapestry.jpg");

	for (int x = 0; x < img.getWidth(); x += img.getWidth()/NUM_STEPS) {
		for (int y = 0; y < img.getHeight(); y += img.getHeight() / NUM_STEPS) {
			mesh.addVertex(ofVec3f(x, y, 0));
			mesh.addColor(img.getColor(x, y));
		}
	}

	mesh.setMode(OF_PRIMITIVE_POINTS);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
	mesh.draw();
	cam.end();
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
