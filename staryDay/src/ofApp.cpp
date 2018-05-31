#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0, 0, 0);
    cam.lookAt(ofVec3f(0, 0, 0));
    
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
    gui.add(bufferSize.set("Buffer Size", ofGetHeight(),0.0, ofGetHeight()));
    gui.loadFromFile("settings/starPosition.xml");
    
    ofImage img;
    img.load("images/Tapestry.jpg");
    
    spectrumFinder colorFinder;
    cols = colorFinder.getColorsFromImage(img);
    
    ofMesh verts;
    verts.load("models/sphere.ply");

    for(int i = 0; i < verts.getNumVertices(); i++) {
        ofVec3f v = verts.getVertex(i);
        ofVec3f vS = cartesianToSpherical(v);
        vS.x += radius/4 - ofRandom(0, radius/2);
        ofVec3f vr = sphericalToCartesian(vS);
        points.push_back(vr);
        sizes.push_back(ofVec3f(ofMap(verts.getColor(i).r*255, 45, 65, 0.0, 4.0)));
        colors.push_back(cols[i%cols.size()]);
    }
    
    starPoints.load("shaders/starSize");
    fade.load("shaders/fade");
    
    camPosTarget = ofVec3f(0, 0, 0);
    int numPoints = (int)points.size();
    
    vbo.setVertexData(&points[0], numPoints, GL_STATIC_DRAW);
    vbo.setColorData(&colors[0], numPoints, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], numPoints, GL_STATIC_DRAW);
     
    ofDisableArbTex();
    ofLoadImage(starSprite, "images/circle.png");
    ofEnableArbTex();

    drawBuffer.allocate(ofGetHeight(), ofGetHeight());
    fadeBufferDraw.allocate(ofGetHeight(), ofGetHeight());
    fadeBufferSave.allocate(ofGetHeight(), ofGetHeight());
    
    ofSetBackgroundAuto(false);
    
    fadeBufferDraw.begin();
    ofBackground(0);
    fadeBufferDraw.end();
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
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();
    
    drawBuffer.begin();
    
    ofBackground(0);
    ofSetColor(255);
    
    cam.begin();
    starPoints.begin();
//    ofEnableDepthTest();
    starPoints.setUniform1f("distanceToCenter", ofMap((cam.getPosition() - ofVec3f(0, 0, 0)).length(), 0.0, 666.0, 1.0, 0.5, true));
    starPoints.setUniform1f("starDensity", starDensity);
    starPoints.setUniform1f("maxSize", maxStarSize);
    ofRotate(rotation, 0.5, 1, 0);
    starSprite.bind();
	vbo.draw(GL_POINTS, 0, (int)points.size());
    starSprite.unbind();
    starPoints.end();
    rotation += rotSpeed;
//    ofDisableDepthTest();
    cam.end();
    
    drawBuffer.end();
    
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    fadeBufferSave.begin();
    fade.begin();
    fade.setUniformTexture("thisFrame", drawBuffer, 0);
    fade.setUniformTexture("lastFrame", fadeBufferDraw, 1);
    fade.setUniform1f("percent", trailLength);
    fade.setUniform1f("threshold", threshold);
    ofSetColor(255);
    ofDrawRectangle(0, 0, fadeBufferSave.getWidth(), fadeBufferSave.getHeight());
    fade.end();
    fadeBufferSave.end();
    
    fadeBufferDraw.begin();
    ofBackground(0);
    fadeBufferSave.draw(0, 0, fadeBufferDraw.getWidth(), fadeBufferDraw.getHeight());
    fadeBufferDraw.end();
    
    ofSetColor(255);
    fadeBufferDraw.draw(0, 0, bufferSize, bufferSize);
    
    gui.draw();
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 10);
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
    /*
    drawBuffer.allocate(w, h);
    fadeBufferDraw.allocate(w, h);
    fadeBufferSave.allocate(w, h);
     */

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
