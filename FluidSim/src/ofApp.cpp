#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fluidSolver.load("Shaders/FluidSolver");
    fluidShower.load("Shaders/FluidShower");

    solverBuffer.allocate(X_RES, Y_RES);
    copyBuffer.allocate(X_RES, Y_RES);
    randomBuffer.allocate(X_RES, Y_RES);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetElapsedTimef() < 1.0) {
        randomBuffer.begin();
        for(int i = 0; i < X_RES; i++) {
            for(int j = 0; j < Y_RES; j++) {
                ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
                ofDrawRectangle(i, j, 1, 1);
            }
        }
        randomBuffer.end();
        
        solverBuffer.begin();
        for(int i = 0; i < X_RES; i++) {
            for(int j = 0; j < Y_RES; j++) {
                ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
                ofDrawRectangle(i, j, 1, 1);
            }
        }
        solverBuffer.end();
    }
    
    copyBuffer.begin();
    solverBuffer.draw(0, 0);
    copyBuffer.end();
    
    solverBuffer.begin();
    fluidSolver.begin();
    fluidSolver.setUniform2f("resolution", solverBuffer.getWidth(), solverBuffer.getHeight());
    fluidSolver.setUniformTexture("inputTexture1", copyBuffer, 0);
    fluidSolver.setUniformTexture("randomTexture", randomBuffer, 1);
    ofDrawRectangle(0, 0, solverBuffer.getWidth(), solverBuffer.getHeight());
    fluidSolver.end();
    solverBuffer.end();
    
    fluidShower.begin();
    fluidSolver.setUniform2f("resolution", solverBuffer.getWidth(), solverBuffer.getHeight());
    fluidSolver.setUniformTexture("inputTexture1", solverBuffer, 0);
    ofDrawRectangle(0, 0, solverBuffer.getWidth(), solverBuffer.getHeight());
    fluidSolver.end();
//    randomBuffer.draw(200, 0);
    
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
