#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxNestedFileLoader loader;
    imagePaths = loader.load("images");
    img.load(imagePaths[0]);
    
    originalSize = ofVec2f(img.getWidth(), img.getHeight());
    
    gui.setup("controls", "settings/settings.xml");
    gui.add(scale.set("Scale", 1, 0, 1));
    gui.add(yPos.set("yPos", 0, -ofGetHeight(), ofGetHeight()));
    gui.add(boxSize.set("boxSize", 177, 100, 500));
    gui.add(displayScale.set("scale", 1, 0.1, 10));
    gui.loadFromFile("settings.settings.xml");
    
    loader.clearPaths();
    videoPaths = loader.load("videos");
    player.load(videoPaths[0]);
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(0, yPos);
    ofScale(displayScale, displayScale);
    //player.draw(0, 0);
    img.draw(0, 0, originalSize.x, originalSize.y);
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofDrawRectangle(0, 0, boxSize, boxSize);
    ofPopMatrix();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_RIGHT) {
        imageIndex++;
        imageIndex %= imagePaths.size();
        img.load(imagePaths[imageIndex]);
        originalSize = ofVec2f(img.getWidth(), img.getHeight());
        videoIndex++;
        videoIndex %= videoPaths.size();
        player.load(videoPaths[videoIndex]);
        player.play();
    }
    if(key == OF_KEY_LEFT) {
        imageIndex--;
        imageIndex = (imageIndex < 0) ? imagePaths.size()-1 : imageIndex;
        img.load(imagePaths[imageIndex]);
        originalSize = ofVec2f(img.getWidth(), img.getHeight());
        videoIndex--;
        videoIndex = (videoIndex < 0) ? videoPaths.size()-1 : videoIndex;
        player.load(videoPaths[videoIndex]);
        player.play();
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
