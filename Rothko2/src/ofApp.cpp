#include "ofApp.h"
#define NUM_PARTICLES 2

//--------------------------------------------------------------
void ofApp::setup(){
	//shader.load("shaders/Rothko");

	string settingsPath = "settings/settings.xml";
	gui.setup("Controls", settingsPath);
	gui.add(noiseIterations.set("noiseIterations", 2, 2, 10));
	gui.add(noiseSize.set("noiseSize", 0, 0, 1000));
	gui.add(noiseScale.set("noiseScale", 0.005, 0, 0.1));
    gui.add(noiseSpeed.set("noiseSpeed", 1, 0, 2));
	gui.loadFromFile(settingsPath);
    
    line* linep = nullptr;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        line newLine;
        newLine.setup();
        newLine.comparatorLine = linep;
        linep = &newLine;
        lines.push_back(newLine);
    }

	ofBackground(20);
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < lines.size(); i++) {
        lines[i].noiseSpeed = noiseSpeed;
        lines[i].noiseSize = noiseSize;
        lines[i].noiseScale = noiseScale;
        lines[i].noiseIterations = noiseIterations;
        lines[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < lines.size(); i++) {
        lines[i].draw();
    }
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
