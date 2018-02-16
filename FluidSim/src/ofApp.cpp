#include "ofApp.h"

ofVec3f colorToUniformRange(ofColor col) {
    float r = col.r / 255.0;
    float g = col.g / 255.0;
    float b = col.b / 255.0;
    return ofVec3f(r, g, b);
}

//--------------------------------------------------------------
void ofApp::setup(){
    fluidSolver.load("Shaders/FluidSolver");
    fluidShower.load("Shaders/FluidShower");

    solverBuffer.allocate(X_RES, Y_RES);
    copyBuffer.allocate(X_RES, Y_RES);
    randomBuffer.allocate(X_RES, Y_RES);
    particleBuffer.allocate(X_RES, Y_RES);
    
    img.load("Images/Tapestry.png");
    
    spectrumFinder f;

    cols = f.getColorsFromImage(img);
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
    
//    particleBuffer.begin();
    fluidShower.begin();
//    fluidShower.setUniformTexture("particleBuffer", particleCopyBuffer, 0);
    fluidShower.setUniformTexture("texSolver", copyBuffer, 0);
    fluidShower.setUniform3f("col1", colorToUniformRange(cols[0]));
    fluidShower.setUniform3f("col2", colorToUniformRange(cols[int(cols.size()-1) / 4]));
    fluidShower.setUniform3f("col3", colorToUniformRange((cols[int(cols.size()-1) / 4 + 1])));
    fluidShower.setUniform3f("col4", colorToUniformRange(cols[cols.size() / 2]));
    ofDrawRectangle(0, 0, solverBuffer.getWidth(), solverBuffer.getHeight());
    fluidShower.end();
//    particleBuffer.end();
    
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
