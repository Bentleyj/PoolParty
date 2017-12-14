#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//shader.load("shaders/Rothko");

	string settingsPath = "settings/settings.xml";
	gui.setup("Controls", settingsPath);
	gui.add(noiseIterations.set("noiseIterations", 0, 0, 10));
	gui.add(noiseSize.set("noiseSize", 0, 0, 1000));
	gui.add(noiseScale.set("noiseScale", 1, 0, 1));
	gui.loadFromFile(settingsPath);

	float x = ofGetWidth() / 1000 + 5;
	float y = ofGetHeight() / 2;
	for (int i = 0; i < 1000; i++) {
		points.push_back(ofVec3f(x, y));
		line.addVertex(ofVec3f(x, y, 0));
		x += ofGetWidth() / 1000;
	}

	line.setMode(OF_PRIMITIVE_LINE_STRIP);

	ofBackground(20);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < line.getNumVertices(); i++) {
		ofVec2f p = points[i];
		p.y += (0.5 - ofNoise(p.x * noiseScale)) * 2.0 * noiseSize;
		line.setVertex(i, p);
	}

	for (int i = 1; i < noiseIterations; i++) {
		for (int j = 0; j < line.getNumVertices()-1; j++) {
			ofVec2f p = line.getVertex(j);
			ofVec2f pNext = line.getVertex(j + 1);
			ofVec2f v = pNext - p;
			ofVec2f vPerp = ofVec2f(v.y, -v.x);
			vPerp /= v.length();
			p.x -= vPerp.x * (0.5 - ofNoise(p.x * noiseScale * i)) * 2.0 * noiseSize / i;
			p.y -= vPerp.y * (0.5 - ofNoise(p.x * noiseScale * i)) * 2.0 * noiseSize / i;
			line.setVertex(j, p);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	line.draw();

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
