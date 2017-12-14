#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	shader.load("shaders/Rothko");

	img.load("images/hsportrait.png");
	img.resize(ofGetWidth()/3, ofGetHeight()/3);
	img.update();

	ofBackground(20);
	buffer[0].allocate(ofGetWidth()/3, ofGetHeight()/3);
	buffer[1].allocate(ofGetWidth()/3, ofGetHeight()/3);

	buffer[0].begin();
	img.draw(0, 0);
	buffer[0].end();


	index = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	buffer[index].begin();
	shader.begin();
	shader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
	shader.setUniformTexture("texture0", buffer[(index+1)%2].getTexture(), 0);
	ofDrawRectangle(0, 0, buffer[index].getWidth(), buffer[index].getHeight());
	shader.end();
	buffer[index].end();

	buffer[index].draw(0, 0);

	index++;
	index %= 2;

	buffer[0].draw(buffer[0].getWidth(), 0);
	buffer[1].draw(buffer[0].getWidth() * 2, 0);
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
