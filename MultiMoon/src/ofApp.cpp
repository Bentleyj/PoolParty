#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string settingsPath = "settings/settings.xml";
    gui.setup(settingsPath);
    gui.add(x.set("X", ofGetWidth()/2, 0, ofGetWidth()));
    gui.add(y.set("Y", ofGetHeight()/2, 0, ofGetHeight()));
    gui.add(horizon.set("Horizon", ofGetHeight()/2, 0, ofGetHeight()));
    gui.add(width.set("width", 50, 0, ofGetWidth()));
    gui.add(animate.set("animate", false));
    gui.loadFromFile(settingsPath);
    
    top.allocate(ofGetWidth(), ofGetHeight());
    bottom.allocate(ofGetWidth(), ofGetHeight());
    
    myMoon.horizon = &horizon;
    myMoon.color = ofColor(255);
    myMoon.width = width;
    myMoon.x = x;
    myMoon.y = y;
    myMoon.radius = 20;
    
    for(int i = 0; i < 5; i++) {
        Moon moon;
        float r = ofRandom(0, 255);
        float g = ofRandom(0, 255);
        float b = ofRandom(0, 255);

        moon.color = ofColor(r, g, b);
        moon.width = 200;
        moon.x = ofRandom(0, ofGetWidth());
        moon.y = ofRandom(0, ofGetHeight());
        moon.radius = ofRandom(5, 25);
        moon.horizon = &horizon;
        moons.push_back(moon);
    }
    
    ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < moons.size(); i++) {
        moons[i].width = width;
    }
    
    myMoon.width = width;
    myMoon.y = y;
    
    if(animate) {
        myMoon.x += 0.5;
        if(myMoon.x > ofGetWidth() + 20) {
            myMoon.x = -20;
        }
        for(int i = 0; i < moons.size(); i++) {
            moons[i].update();
        }
    } else {
        myMoon.x = x;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    top.begin();
    ofClear(0);
    for(int i = 0; i < moons.size(); i++) {
        moons[i].drawTop();
    }
    myMoon.drawTop();
    top.end();
    
    bottom.begin();
    ofClear(0);
    for(int i = 0; i < moons.size(); i++) {
        moons[i].drawBottom();
    }
    myMoon.drawBottom();
    bottom.end();
    
    top.draw(0, 0);
    bottom.draw(0, 0);
    
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
