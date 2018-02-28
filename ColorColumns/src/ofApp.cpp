#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofImage img;
    img.load("Images/Tapestry.jpg");
    spectrumFinder f;
    cols = f.getColorsFromImage(img);
    
    for(int i = 0; i < 200; i++) {
        Column col;
        col.height = ofGetHeight() / 4;
        col.baseHeight = col.height;
        col.col = cols[int(ofRandom(cols.size()))];
        col.order = i;
        topCols.push_back(col);
    }
    
    for(int i = 0; i < 200; i++) {
        Column col;
        col.height = ofGetHeight() / 4;
        col.baseHeight = col.height;
        col.col = cols[int(ofRandom(cols.size()))];
        col.order = i + 100;
        botCols.push_back(col);
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Settings", settingsPath);
    gui.add(numCols.set("Num Cols", 5, 1, 200));
    gui.add(noiseSpeed.set("Noise Speed", 0.0, 0.0, 10.0));
    gui.add(noiseScale.set("Noise Scale", 20.0, 0.0, 500.0));
    gui.add(noiseResolution.set("Noise Res", 0.5, 0.0, 1.03));
    gui.add(baseHeight.set("Base Col Height", ofGetHeight()/4, 0.0, ofGetHeight()));
    gui.add(bufferSize.set("Buffer Size", 128, 0.0, ofGetHeight()));

    ofBackground(0);
    
    topBuffer.allocate(ofGetHeight(), ofGetHeight());
    botBuffer.allocate(ofGetHeight(), ofGetHeight());
    viewBuffer.allocate(ofGetHeight(), ofGetHeight());
    
    mix.load("shaders/mix");
    
    topCap.addVertex(ofVec3f(0, 0, 0));
    topCap.addVertex(ofVec3f(0, 10, 0));
    topCap.addVertex(ofVec3f(10, 10, 0));
    topCap.addVertex(ofVec3f(10, 0, 0));
    topCap.addIndex(0);
    topCap.addIndex(1);
    topCap.addIndex(2);
    topCap.addIndex(0);
    topCap.addIndex(2);
    topCap.addIndex(3);
    topCap.addColor(ofColor(255));
    topCap.addColor(ofColor(0));
    topCap.addColor(ofColor(0));
    topCap.addColor(ofColor(255));
    
    topCap.setMode(OF_PRIMITIVE_TRIANGLES);
    
    botCap.addVertex(ofVec3f(0, 0, 0));
    botCap.addVertex(ofVec3f(0, 10, 0));
    botCap.addVertex(ofVec3f(10, 10, 0));
    botCap.addVertex(ofVec3f(10, 0, 0));
    botCap.addIndex(0);
    botCap.addIndex(1);
    botCap.addIndex(2);
    botCap.addIndex(0);
    botCap.addIndex(2);
    botCap.addIndex(3);
    botCap.addColor(ofColor(0));
    botCap.addColor(ofColor(255));
    botCap.addColor(ofColor(255));
    botCap.addColor(ofColor(0));
    
    botCap.setMode(OF_PRIMITIVE_TRIANGLES);

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < topCols.size(); i++) {
        topCols[i].baseHeight = baseHeight;
        topCols[i].update(noiseSpeed, noiseScale, noiseResolution);
    }
    for(int i = 0; i < botCols.size(); i++) {
        botCols[i].baseHeight = baseHeight;
        botCols[i].update(noiseSpeed, noiseScale, noiseResolution);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    topBuffer.begin();
    ofClear(0);
    for(int i = 0; i < topCols.size(); i++) {
        Column col = topCols[i];
        ofSetColor(col.col);
        ofDrawRectangle(i * topBuffer.getWidth() / numCols, 0, topBuffer.getWidth() / numCols, col.height);
        ofPushMatrix();
        ofTranslate(i * topBuffer.getWidth() / numCols, col.height);
        ofScale(topBuffer.getWidth() / numCols / 10, 2);
        topCap.setColor(0, col.col);
        topCap.setColor(3, col.col);
        topCap.draw();
        ofPopMatrix();
    }
    topBuffer.end();
    
    botBuffer.begin();
    ofClear(0);
    for(int i = 0; i < botCols.size(); i++) {
        Column col = botCols[i];
        ofSetColor(col.col);
        ofDrawRectangle(i * botBuffer.getWidth() / numCols, botBuffer.getHeight() - col.height, botBuffer.getWidth() / numCols, col.height);
        ofPushMatrix();
        ofTranslate(i * botBuffer.getWidth() / numCols, botBuffer.getHeight() - col.height);
        ofScale(topBuffer.getWidth() / numCols / 10, 2);
        botCap.setColor(1, col.col);
        botCap.setColor(2, col.col);
        botCap.draw();
        ofPopMatrix();
    }
    botBuffer.end();
    
    viewBuffer.begin();
    mix.begin();
    mix.setUniformTexture("top", topBuffer, 0);
    mix.setUniformTexture("bot", botBuffer, 1);
    ofDrawRectangle(0, 0, viewBuffer.getWidth(), viewBuffer.getHeight());
    mix.end();
    viewBuffer.end();
    
    viewBuffer.draw(0, 0, bufferSize, bufferSize);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        for(int i = 0; i < topCols.size(); i++) {
            topCols[i].col = cols[int(ofRandom(cols.size()))];
        }
        for(int i = 0; i < botCols.size(); i++) {
            botCols[i].col = cols[int(ofRandom(cols.size()))];

        }
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
