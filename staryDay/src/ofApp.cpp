#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0, 0, 10);
    cam.lookAt(ofVec3f(0, 0, 0));
<<<<<<< Updated upstream
=======
    
    radius = 200.0;
    
    ofBackground(0);
    
    gui.setup("Controls", "settings/starPosition.xml");
    starGroup.setName("Stars");
    starGroup.add(starDensity.set("Density", 0.0, 0.0, 1.0));
    starGroup.add(maxStarSize.set("Max Size", 4.0, 0.0, 10.0));
    starGroup.add(rotSpeed.set("Rotation Speed", 0.0, 0.0, 1.0));
    starGroup.add(trailLength.set("Trail Length", 0.0, 0.0, 1.0));
    starGroup.add(threshold.set("Threshold", 0.0, 0.0, 1.0));

    gui.add(starGroup);
    cameraGroup.setName("Camera");
    cameraGroup.add(freeCamera.set("Free Camera", true));
    cameraGroup.add(ra.set("Right Ascension",12, 0, 24));
    cameraGroup.add(de.set("Declination", 45, -90, 90));
    
    gui.add(cameraGroup);
    gui.loadFromFile("settings/starPosition.xml");
    
    img.load("images/Tapestry.png");
    
    cols = colorFinder.getColorsFromImage(img);
    
    ofMesh verts;
    verts.load("models/sphere.ply");

    for(int i = 0; i < verts.getNumVertices(); i++) {
        ofVec3f v = verts.getVertex(i);
        ofVec3f vS = cartesianToSpherical(v);
        vS.x += radius/4 - ofRandom(0, radius/2);
        ofVec3f vr = sphericalToCartesian(vS);
        celestialSphere.addVertex(vr);
        celestialSphere.addColor(cols[i%cols.size()]);
        pointSize.push_back(ofMap(verts.getColor(i).r*255, 45, 65, 0.0, 4.0));
    }
    
    starPoints.load("shaders/starSize");
    fade.load("shaders/fade");
    
    camPosTarget = ofVec3f(0, 0, 0);

    starPoints.begin();
    celestialSphere.getVbo().setAttributeData(starPoints.getAttributeLocation("point_size"), &pointSize[0], 1, pointSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    celestialSphere.getVbo().setAttributeData(starPoints.getAttributeLocation("point_size"), &pointSize[0], 1, pointSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    starPoints.end();
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    celestialSphere.setMode(OF_PRIMITIVE_POINTS);
        
    drawBuffer.allocate(ofGetWidth(), ofGetHeight());
    fadeBufferDraw.allocate(ofGetWidth(), ofGetHeight());
    fadeBufferSave.allocate(ofGetWidth(), ofGetHeight());
    
    fadeBufferDraw.begin();
    ofBackground(0);
    fadeBufferDraw.end();
>>>>>>> Stashed changes
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    float theta = 0;
    float phi = 0;
    float r = 20.0;
    int numSteps = 100;
    for(int i = 0; i < numSteps; i++) {
        for(int j = 0; j < numSteps; j++) {
            ofVec3f p = sphericalToCartesian(ofVec3f(r, theta, phi));
            ofDrawSphere(p, 0.1);
            theta += 2 * PI / numSteps;
        }
        phi += PI / numSteps;
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
ofVec3f ofApp::starCoordsToSpherical(float ra, float de) {
    //float r = 1.0;
}

//--------------------------------------------------------------
ofVec3f ofApp::cartesianToSpherical(ofVec3f point) {
    float r = point.length();
    float theta = atan2(point.y , point.x);
    float phi = acos(point.z / r);
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
