#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0, 0, 10);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    radius = 200.0;
    
    sphere = ofMesh::sphere(radius);
    
    sphere.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    ofBackground(0);
    
    gui.setup("Star Position", "settings/starPosition.xml");
    star.setName("Star");
    star.add(ra.set("Right Ascension",0, 0, 24));
    star.add(de.set("Declination", 0, -90, 90));
    gui.add(star);
    test.setName("Test");
    test.add(theta.set("Theta",0, 0, 2*PI));
    test.add(phi.set("Phi", 0, 0, PI));
    gui.add(test);
    gui.loadFromFile("settings/starPosition.xml");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
//    float theta = 0;
//    float phi = 0;
//    float r = radius;
    int numSteps = 100;
    ofSetColor(255);
//    for(int i = 0; i < numSteps; i++) {
//        for(int j = 0; j < numSteps; j++) {
//            ofVec3f p = sphericalToCartesian(ofVec3f(r, theta, phi));
//            ofDrawSphere(p, 10.0);
//            phi += 2 * PI / numSteps;
//        }
//        phi += PI / numSteps;
//    }
    ofSetColor(255, 0, 0);
    sphere.draw();
    
    ofSetColor(0, 255, 0);
    ofVec3f p = sphericalToCartesian(starCoordsToSpherical(ra, de));
  //  ofVec3f p = sphericalToCartesian(ofVec3f(radius, theta, phi));

    ofDrawSphere(p, 15);
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
ofVec3f ofApp::starCoordsToSpherical(float ra, float de) {
    // phi -> declination
    // theta -> right ascension
    float phi = ofMap(de, -90, 90, 0, PI);
    float theta = ofMap(ra, 0, 24, 0, 2 * PI);
    return ofVec3f(radius, theta, phi);
}

//--------------------------------------------------------------
ofVec3f ofApp::cartesianToSpherical(ofVec3f point) {
    float r = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    float theta = atan2(point.y , point.x);
    float phi = acos(point.z/r);
    return ofVec3f(r, theta, phi);
}

//--------------------------------------------------------------
ofVec3f ofApp::sphericalToCartesian(ofVec3f point) {
    float r = point.x;
    float theta = point.y;
    float phi = point.z;
    float x = r * cos(theta) * sin(phi);
    float y = r * sin(theta) * sin(phi);
    float z = r * cos(phi);
    return ofVec3f(x, y, z);
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
