#include "ofApp.h"
#define NUM_PARTICLES 200

//--------------------------------------------------------------
void ofApp::setup(){
	//shader.load("shaders/Rothko");

	string settingsPath = "settings/settings.xml";
	gui.setup("Controls", settingsPath);
	gui.add(noiseIterations.set("noiseIterations", 0, 0, 10));
	gui.add(noiseSize.set("noiseSize", 0, 0, 1000));
	gui.add(noiseScale.set("noiseScale", 1, 0, 1));
	gui.loadFromFile(settingsPath);

	float x = ofGetWidth() / NUM_PARTICLES + 5;
	float y = ofGetHeight() / 2;

	for (int i = 0; i < NUM_PARTICLES; i++) {
		Particle p;
		p.col = ofColor(255);
		p.pos = ofVec2f(x, y);
		p.width = ofGetWidth() / NUM_PARTICLES - 2;
		p.height = ofRandom(10, 20);
		x += ofGetWidth() / NUM_PARTICLES + 1;
		particles.push_back(p);
	}

	cout << particles.size() << endl;

	ofBackground(20);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}

	//gui.draw();
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
