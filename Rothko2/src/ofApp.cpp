#include "ofApp.h"
#define NUM_PARTICLES 10

//--------------------------------------------------------------
void ofApp::setup(){
	//shader.load("shaders/Rothko");

	string settingsPath = "settings/settings.xml";
	gui.setup("Controls", settingsPath);
	gui.add(noiseIterations.set("noiseIterations", 2, 2, 10));
	gui.add(noiseSize.set("noiseSize", 0, 0, 1000));
	gui.add(noiseScale.set("noiseScale", 0.005, 0, 0.1));
    gui.add(noiseSpeed.set("noiseSpeed", 1, 0, 2));
    gui.add(horizon.set("Horizon", 0, -ofGetHeight()/2, ofGetHeight()/2));
	gui.loadFromFile(settingsPath);
    
    for(int i = 0; i < NUM_PARTICLES; i++) {
        line newLine;
        newLine.setup();
        newLine.sign = 1;
        newLine.col = ofColor(28, 81, 170);
        linesBottom.push_back(newLine);
    }
    
    for(int i = 0; i < NUM_PARTICLES; i++) {
        line newLine;
        newLine.setup();
        newLine.sign = -1;
        newLine.col = ofColor(149, 113, 105);
        linesTop.push_back(newLine);
    }

	ofBackground(20);
    
    ofSetLineWidth(2);
    
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 1; i < linesBottom.size(); i++) {
        linesBottom[i].noiseSpeed = noiseSpeed;
        linesBottom[i].noiseSize = noiseSize;
        linesBottom[i].noiseScale = noiseScale;
        linesBottom[i].noiseIterations = noiseIterations;
        linesBottom[i].update(&linesBottom[i-1]);
    }
    
    for(int i = 1; i < linesTop.size(); i++) {
        linesTop[i].noiseSpeed = noiseSpeed;
        linesTop[i].noiseSize = noiseSize;
        linesTop[i].noiseScale = noiseScale;
        linesTop[i].noiseIterations = noiseIterations;
        linesTop[i].update(&linesTop[i-1]);
    }
    for(int i = 0; i < linesBottom[0].mesh.getNumVertices(); i++) {
        ofVec3f vb =  linesBottom[0].mesh.getVertex(i);
        vb.y = horizon;
        linesBottom[0].mesh.setVertex(i, vb);
        ofVec3f vt =  linesTop[0].mesh.getVertex(i);
        vt.y = ofGetHeight() - horizon;
        linesTop[0].mesh.setVertex(i, vt);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 1; i < linesBottom.size(); i++) {
        linesBottom[i].draw();
    }
    for(int i = 1; i < linesTop.size(); i++) {
        linesTop[i].draw();
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
