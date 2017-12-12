#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxNestedFileLoader loader;
    imagePaths = loader.load("images");
    img.load(imagePaths[0]);
    
    originalSize = ofVec2f(img.getWidth(), img.getHeight());
    
    gui.setup("controls", "settings/settings.xml");
    gui.add(scale.set("Scale", 1, 0, 1));
    gui.loadFromFile("settings.settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    img.draw(0, 0, originalSize.x, originalSize.y);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT) {
        imageIndex++;
        imageIndex %= imagePaths.size();
        img.load(imagePaths[imageIndex]);
        originalSize = ofVec2f(img.getWidth(), img.getHeight());
    }
    if(key == OF_KEY_LEFT) {
        imageIndex--;
        imageIndex = (imageIndex < 0) ? imagePaths.size()-1 : imageIndex;
        img.load(imagePaths[imageIndex]);
        originalSize = ofVec2f(img.getWidth(), img.getHeight());
    }
    if(key == ' ') {
        img.load(imagePaths[imageIndex]);
        originalSize = ofVec2f(img.getWidth(), img.getHeight());
        ofxCv::resize(img, dst, scale, scale);
        img = dst;
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
