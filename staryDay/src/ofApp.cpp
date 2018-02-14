#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0, 0, 0);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    radius = 200.0;
    
    sphere = ofMesh::sphere(radius);
    
    sphere.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    ofBackground(0);
    
    gui.setup("Star Position", "settings/starPosition.xml");
    starGroup.setName("Star");
    starGroup.add(ra.set("Right Ascension",12, 0, 24));
    starGroup.add(de.set("Declination", 45, -90, 90));
    gui.add(starGroup);
    testGroup.setName("Test");
    testGroup.add(theta.set("Theta",0, 0, 2*PI));
    testGroup.add(phi.set("Phi", 0, 0, PI));
    gui.add(testGroup);
    gui.loadFromFile("settings/starPosition.xml");
    
    starData.load("data/hygdata_v3.csv", ",");
    int step = 5;
    for(int i = 1; i < starData.getNumRows()-step; i+=step) {
        star newStar;
        ofxCsvRow row = starData.getRow(i);
        newStar.ra = row.getFloat(7);
        newStar.de = row.getFloat(8);
        newStar.p = sphericalToCartesian(starCoordsToSpherical(newStar.ra, newStar.de));
        newStar.mag = row.getFloat(13);
        stars.push_back(newStar);
        celestialSphere.addVertex(newStar.p);
        celestialSphere.addColor(ofColor(ofMap(newStar.mag, 0.0, 15.0, 0.0, 255, true)));
        pointSize.push_back(ofMap(newStar.mag, 0.0, 15.0, 0.0, 5.0, true));
    }
    
    starPoints.load("shaders/starSize");
    
    starPoints.begin();
    celestialSphere.getVbo().setAttributeData(starPoints.getAttributeLocation("point_size"), &pointSize[0], 1, pointSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    starPoints.end();
    
//    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    celestialSphere.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    
    ofSetColor(0, 255, 0);
    
    starPoints.begin();
    celestialSphere.draw();
    starPoints.end();
//    ofVec3f p = sphericalToCartesian(starCoordsToSpherical(ra, de));
//    ofDrawSphere(p, 2.0);
//
//    for(int i = 0; i < stars.size(); i++) {
//        ofSetColor(ofMap(stars[i].mag, 0.0, 15.0, 0.0, 255, true));
//        ofVec3f p = stars[i].p;
//        ofDrawSphere(p, ofMap(stars[i].mag, 0.0, 15.0, 0.0, 1.0, true));
//    }

    cam.end();
    

    
    ofDisableDepthTest();
    gui.draw();
    
//    for(int i = 0; i < stars.size(); i++) {
//        ofDrawCircle(ofMap(stars[i].ra, 0, 24, 0, ofGetWidth()), ofMap(stars[i].de, -90, 90, ofGetHeight(), 0), 2);
//    }

}

void ofApp::pChanged(float & p) {

//    string starURL = url[0] + ofToString(ra) + url[1] + ofToString(de) + url[2];
//    ofHttpResponse resp = ofLoadURL(starURL);
//
//    bool loaded = starsData.loadFromBuffer(resp.data);
//
//    starsData.pushTag("response");
//    int numStars = starsData.getNumTags("star");
//
//    stars.clear();
//
//    for(int i = 0; i < numStars; i++) {
//        starsData.pushTag("star", i);
//        star newStar;
//        newStar.ra = starsData.getValue("ra", 0);
//        newStar.de = starsData.getValue("de", 0);
//        newStar.catID = starsData.getValue("catId", "NONE");
//        newStar.mag = starsData.getValue("mag", 0);
//        ofVec3f p = sphericalToCartesian(starCoordsToSpherical(newStar.ra, newStar.de));
//        newStar.p = p;
//        stars.push_back(newStar);
//        starsData.popTag();
//    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
ofVec3f ofApp::starCoordsToSpherical(double ra, double de) {
    // phi -> declination
    // theta -> right ascension
    double phi = ofMap(de, -90, 90, 0, PI);
    double theta = ofMap(ra, 0, 24, 0, 2 * PI);
    return ofVec3f(radius, theta, phi);
}

//--------------------------------------------------------------
ofVec3f ofApp::cartesianToSpherical(ofVec3f point) {
    double r = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    double theta = atan2(point.y , point.x);
    double phi = acos(point.z/r);
    return ofVec3f(r, theta, phi);
}

//--------------------------------------------------------------
ofVec3f ofApp::sphericalToCartesian(ofVec3f point) {
    double r = point.x;
    double theta = point.y;
    double phi = point.z;
    double x = r * cos(theta) * sin(phi);
    double y = r * sin(theta) * sin(phi);
    double z = r * cos(phi);
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
