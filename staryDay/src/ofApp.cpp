#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0, 0, 0);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    radius = 200.0;
    
    sphere = ofMesh::sphere(radius);
    
    sphere.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    ofBackground(0);
    
    gui.setup("Controls", "settings/starPosition.xml");
    starGroup.setName("Stars");
    starGroup.add(starDensity.set("Density", 0.0, 0.0, 1.0));
    starGroup.add(maxStarSize.set("Max Size", 4.0, 0.0, 10.0));

    gui.add(starGroup);
    cameraGroup.setName("Camera");
    cameraGroup.add(freeCamera.set("Free Camera", true));
    cameraGroup.add(ra.set("Right Ascension",12, 0, 24));
    cameraGroup.add(de.set("Declination", 45, -90, 90));
    
    gui.add(cameraGroup);
    gui.loadFromFile("settings/starPosition.xml");
    
    ofMesh verts;
    verts.load("models/sphere.ply");

    for(int i = 0; i < verts.getNumVertices(); i++) {
        celestialSphere.addVertex(verts.getVertex(i));
        pointSize.push_back(ofMap(verts.getColor(i).r*255, 45, 60, 0.0, 4.0));
    }
    
//    starData.load("data/hygdata_v3.csv", ",");
//    int step = 1;
//    for(int i = 1; i < starData.getNumRows()-step; i+=step) {
//        star newStar;
//        ofxCsvRow row = starData.getRow(i);
//        newStar.ra = row.getFloat(7);
//        newStar.de = row.getFloat(8);
//        newStar.p = sphericalToCartesian(starCoordsToSpherical(newStar.ra, newStar.de));
//        newStar.mag = row.getFloat(13);
//        stars.push_back(newStar);
//        celestialSphere.addVertex(newStar.p);
//        celestialSphere.addColor(ofColor(ofMap(newStar.mag, 0.0, 15.0, 0.0, 255), 0.0, 0.0));
//        pointSize.push_back(ofMap(newStar.mag, 0.0, 15.0, 0.0, 6.0, true));
//    }

//    celestialSphere.save("models/sphere.ply");
    
    starPoints.load("shaders/starSize");
    
    camPosTarget = ofVec3f(0, 0, 0);
    camPosTarget = ofVec3f(0, 0, 0);

    starPoints.begin();
    celestialSphere.getVbo().setAttributeData(starPoints.getAttributeLocation("point_size"), &pointSize[0], 1, pointSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    starPoints.end();
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    celestialSphere.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!freeCamera) {
        ofVec3f camPos = cam.getPosition();
        camPos.x = ofLerp(camPos.x, camPosTarget.x, 0.1);
        camPos.y = ofLerp(camPos.y, camPosTarget.y, 0.1);
        camPos.z = ofLerp(camPos.z, camPosTarget.z, 0.1);
        cam.setPosition(camPos);
        
        camLookAtTarget = sphericalToCartesian(starCoordsToSpherical(ra, de));
        ofVec3f lookDir = cam.getLookAtDir();
        lookDir.x = ofLerp(lookDir.x, camLookAtTarget.x, 0.1);
        lookDir.y = ofLerp(lookDir.y, camLookAtTarget.y, 0.1);
        lookDir.z = ofLerp(lookDir.z, camLookAtTarget.z, 0.1);
        cam.lookAt(lookDir);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    
    ofSetColor(0, 255, 0);
    starPoints.begin();
    starPoints.setUniform1f("distanceToCenter", ofMap((cam.getPosition() - ofVec3f(0, 0, 0)).length(), 0.0, 666.0, 1.0, 0.5, true));
    starPoints.setUniform1f("starDensity", starDensity);
    starPoints.setUniform1f("maxSize", maxStarSize);

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
    float r = ofRandom(0.0, radius);
    return ofVec3f(r, theta, phi);
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
