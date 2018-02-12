#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int x = 0; x < X_RES; x++) {
        for(int y = 0; y < Y_RES; y++) {
            ofVec2f uv = ofVec2f(x, y);
            uv /= ofVec2f(X_RES, Y_RES);
            ofVec2f uvAbs = uv * ofVec2f(X_RES, Y_RES);
            ofVec2f scr = uv * 2.0 - ofVec2f(1.0, 1.0);
            float sc = 1.0 / X_RES; // Note this should be the maximum value between X_RES and Y_RES
            ofVec2f v = ofVec2f(0.0, 0.0);
            for(int level = 0; level < 20; level++) {
                if(sc > 0.7) break;
                float ang2 = angRnd*ang*randS().y;
                ofVec2f p = ofVec2f(cos(ang2), sin(ang2));
                for(int i = 0; i < RotNum; i++) {
                    ofVec2f p2 = p * sc;
                    float rot = getRot(uv + p2, sc);
                    v += ofVec2f(p2.y, p2.x) * rot * ofVec2f(-1, 1);
                    p = m * p;
                }
                sc *= 2.0;
            }
            cellsFlop[x][y].u = cellsFlip[int(uvAbs.x + v.x)][int(uvAbs.y + v.y)].u;
        }
    }
    Cell cellsTemp[X_RES][Y_RES];// = cellsFlip;
    for(int x = 0; x < X_RES; x++) {
        for(int y = 0; y < Y_RES; y++) {
            cellsTemp[x][y] = cellsFlip[x][y];
            cellsFlip[x][y] = cellsFlop[x][y];
            cellsFlop[x][y] = cellsTemp[x][y];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float size = 20;
    ofSetColor(255);
    ofNoFill();
    for(int x = 0; x < X_RES; x++) {
        for(int y = 0; y < Y_RES; y++) {
            ofDrawRectangle(x * size, y * size, size, size);
            ofPushMatrix();
            ofTranslate(x * size + size/2, y * size + size/2);
            ofDrawLine(0, 0, cellsFlip[x][y].u.x * 10, cellsFlip[x][y].u.y * 10);
            ofPopMatrix();
        }
    }
}

//--------------------------------------------------------------
float ofApp::getRot(ofVec2f uv, float sc) {
    float ang2 = angRnd*randS().x*ang;
    ofVec2f p = ofVec2f(cos(ang2),sin(ang2));
    float rot=0.0;
    for(int i=0;i<RotNum;i++)
    {
        ofVec2f uvAbs = uv * ofVec2f(X_RES, Y_RES);
        ofVec2f p2 = (p+posRnd*ofVec2f(randS().x, randS().y))*sc;
        ofVec2f v = cellsFlip[int(uvAbs.x)][int(uvAbs.y)].u;//texture(iChannel0,fract(uv+p2)).xy-ofVec2f(0.5, 0.5);
        rot += ofVec3f(v.x, v.y, 0.0).getCrossed(ofVec3f( p2.x, p2.y, 0.0)).z / p2.dot(p2);//cross(, ).z / dot(p2,p2);
        ofVec3f v3;
        
        p = m*p;
    }
    rot/=float(RotNum);
    return rot;
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
