#include "ofApp.h"
#define NUM_STEPS 100

#define CAM_WIDTH 160
#define CAM_HEIGHT 90

float getColorDistance(ofColor col1, ofColor col2) {
	float r = col2.r - col1.r;
	float g = col2.g - col1.g;
	float b = col2.b - col1.b;

	float dist = sqrt(r*r + g*g + b*b);

	return dist;
}

struct ColorPosition {
	ofColor col;
	int id;
	ofVec2f nextPos = ofVec2f(20, 20);
	int lastIndex;
};

//--------------------------------------------------------------
void ofApp::setup(){
	img.load("Tapestry.png");

	videoPlayer.load("Videos/BirdsEyeViewWaves480.mov");

	vector<ColorPosition> colorStartingPositions;

	float distTolerance = 18.0;
	float i = 0;

	for (int x = 0; x < img.getWidth(); x += img.getWidth()/NUM_STEPS) {
		for (int y = 0; y < img.getHeight(); y += img.getHeight() / NUM_STEPS) {
			ofColor col = img.getColor(x, y);
			int id = -1;
			for (auto it = colorStartingPositions.begin(); it != colorStartingPositions.end(); it++) {
				if (getColorDistance(col, it->col) < distTolerance) {
					id = it->id;
				}
			}
			if (id != -1) {
				// add to bin
				for (auto it = colorStartingPositions.begin(); it != colorStartingPositions.end(); it++) {
					if (it->id == id) {
						meshes[id].addVertex(it->nextPos);
						meshes[id].addColor(col);
						meshes[id].addIndex(it->lastIndex);
						it->lastIndex = meshes[id].getNumVertices() - 1;
						meshes[id].addIndex(it->lastIndex);
						it->nextPos.x += 5;
					}
				}
			}
			else {
				// Create new bin
				ColorPosition p;
				//p.nextPos.y = colorStartingPositions.size() * 5;
				p.col = col;
				p.id = colorStartingPositions.size();
				ofMesh mesh;
				mesh.addVertex(p.nextPos);
				mesh.addColor(col);
				p.lastIndex = mesh.getNumVertices() - 1;
				p.nextPos.x += 5;
				colorStartingPositions.push_back(p);
				mesh.setMode(OF_PRIMITIVE_LINES);
				meshes.push_back(mesh);

			}
			//i++;
			//float percent = (float)i;// / (float)(NUM_STEPS*NUM_STEPS);
			//cout << percent << "%" << endl;
		}
	}
    
    ofSetLineWidth(3);
    
    gui.setup("controls", "settings/settings.xml");
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 200, 1, 500));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(holes.set("Holes", false));
    gui.loadFromFile("settings/settings.xml");
    
    gui.setPosition(20, videoPlayer.getHeight() + 20);
    
	videoPlayer.play();
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	videoPlayer.update();
    //videoGrabber.update();
    
    if(videoPlayer.isFrameNew()) {
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.setFindHoles(holes);
        contourFinder.findContours(videoPlayer);
        //flow.calcOpticalFlow(videoPlayer);
        //cout<<flow.getAverageFlow()<<endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetLineWidth(3);
	//ofEnableDepthTest();
	//cam.begin();
	//ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
	//offset.begin();
	//offset.setUniform1f("u_time", ofGetElapsedTimef());
	//offset.setUniformTexture("diffuseTexture", img, 0);
	float x = 50;
	float y = 50;
	for (int i = 0; i < meshes.size()-1; i+=2) {
		float meshWidth = meshes[i].getVertex(meshes[i].getNumVertices() - 1).x - meshes[i].getVertex(0).x;
		float offset = ofGetWidth() / 2 - meshWidth;
        float noise = 0.0;//0.5 - ofNoise(ofGetElapsedTimef()/5, y / 80);
		noise *= 100;
		ofPushMatrix();
		ofTranslate(x + offset + noise, y);
		meshes[i].draw();
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(x + meshWidth + offset + 5 + noise, y);
		meshes[i + 1].draw();
		y += 5;
		ofPopMatrix();
	}
    ofSetColor(255);
    ofSetLineWidth(1);
//    videoPlayer.draw(0, 0, videoPlayer.getWidth(), videoPlayer.getHeight());
//    contourFinder.draw();
//    auto contours = contourFinder.getContours();
//    for(int i = 0; i < contours.size(); i++) {
//        ofSetColor(255, 255, 0);
//        for(int j = 0; j < contours[i].size()-1; j+=2) {
//            cv::Point p1 = contours[i][j];
//            cv::Point p2 = contours[i][j+1];
//            ofDrawLine(p1.x, p1.y, p2.x, p2.y);
//        }
//    }
    
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
