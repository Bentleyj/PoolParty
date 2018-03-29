#include "ofApp.h"
#define NUM_LINES 10

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
    gui.add(bufferSize.set("Buffer Size", ofGetHeight(), 0.0, ofGetHeight()));
	gui.loadFromFile(settingsPath);
    
    ofImage img;
    img.load("Images/Tapestry.jpg");
    
    spectrumFinder f;
    cols = f.getColorsFromImage(img);

    ofColor topCol = cols[int(ofRandom(cols.size()))];
    ofColor botCol = cols[int(ofRandom(cols.size()))];
    
    for(int i = 0; i < NUM_LINES; i++) {
        line newLine;
        newLine.col = topCol;
        newLine.setup(ofGetHeight());
        newLine.sign = 1;
        linesBottom.push_back(newLine);
    }
    
    for(int i = 0; i < NUM_LINES; i++) {
        line newLine;
        newLine.col = botCol;
        newLine.setup(0);
        newLine.sign = -1;
        linesTop.push_back(newLine);
    }
    
    mix.load("shaders/mix");

	ofBackground(20);
    
    ofSetLineWidth(2);
    
    drawBuffer.allocate(ofGetHeight(), ofGetHeight());
    topBuffer.allocate(ofGetHeight(), ofGetHeight());
    botBuffer.allocate(ofGetHeight(), ofGetHeight());

    
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
    //drawBuffer.begin();
    botBuffer.begin();
    ofClear(0);
    for(int i = 1; i < linesBottom.size(); i++) {
        linesBottom[i].draw();
    }
    botBuffer.end();
    
    topBuffer.begin();
    ofClear(0);
    for(int i = 1; i < linesBottom.size(); i++) {
        linesTop[i].draw();
    }
    topBuffer.end();
    //drawBuffer.end();
    topBuffer.draw(0, 0, bufferSize, bufferSize);
    
    drawBuffer.begin();
    mix.begin();
    mix.setUniformTexture("top", topBuffer, 0);
    mix.setUniformTexture("bot", botBuffer, 1);
    ofDrawRectangle(0, 0, drawBuffer.getWidth(), drawBuffer.getHeight());
    mix.end();
    drawBuffer.end();
    
    drawBuffer.draw(0, 0, bufferSize, bufferSize);
    
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') {
        for(int i = 1; i < linesBottom.size(); i++) {
            linesBottom[i].setColor(cols[int(ofRandom(cols.size()))]);
            linesTop[i].setColor(cols[int(ofRandom(cols.size()))]);
        }
    }
    if(key == '2') {
        ofColor topCol = cols[int(ofRandom(cols.size()))];
        ofColor botCol = cols[int(ofRandom(cols.size()))];
        for(int i = 1; i < linesBottom.size(); i++) {
            linesBottom[i].setColor(topCol);
            linesTop[i].setColor(botCol);
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
