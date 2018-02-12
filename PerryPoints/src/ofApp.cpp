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
    ofxNestedFileLoader loader;
    imagePaths = loader.load("Images");
	img.load(imagePaths[0]);

	vector<ColorPosition> colorStartingPositions;

	float distTolerance = 15.0;
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
						mesh.addVertex(it->nextPos);
						mesh.addColor(col);
						mesh.addIndex(it->lastIndex);
						it->lastIndex = mesh.getNumVertices() - 1;
						mesh.addIndex(it->lastIndex);
						it->nextPos.x += 5;
					}
				}
			}
			else {
				// Create new bin
				ColorPosition p;
				p.nextPos.y = colorStartingPositions.size() * 5;
				p.col = col;
				p.id = colorStartingPositions.size();
				mesh.addVertex(p.nextPos);
				mesh.addColor(col);
				p.lastIndex = mesh.getNumVertices() - 1;
				p.nextPos.x += 5;
				colorStartingPositions.push_back(p);
			}
		}
	}

	offset.load("Shaders/Offset");

	mesh.setMode(OF_PRIMITIVE_LINES);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableDepthTest();
    img.draw(ofGetWidth() - img.getWidth()/10, 0, img.getWidth()/10, img.getHeight()/10);
	//cam.begin();
	//ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
	//offset.begin();
	//offset.setUniform1f("u_time", ofGetElapsedTimef());
	//offset.setUniformTexture("diffuseTexture", img, 0);
	mesh.draw();
	//offset.end();
	//cam.end();

	//flowImg.draw(0, 0);

	//flow.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT) {
        imageIndex--;
        if(imageIndex < 0)
            imageIndex = imagePaths.size() - 1;
        
        img.load(imagePaths[imageIndex]);
    } else if(key == OF_KEY_RIGHT) {
        imageIndex++;
        imageIndex %= imagePaths.size();
        img.load(imagePaths[imageIndex]);
    }
    
    mesh.clear();
    
    vector<ColorPosition> colorStartingPositions;
    
    float distTolerance = 15.0;
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
                        mesh.addVertex(it->nextPos);
                        mesh.addColor(col);
                        mesh.addIndex(it->lastIndex);
                        it->lastIndex = mesh.getNumVertices() - 1;
                        mesh.addIndex(it->lastIndex);
                        it->nextPos.x += 5;
                    }
                }
            }
            else {
                // Create new bin
                ColorPosition p;
                p.nextPos.y = colorStartingPositions.size() * 5;
                p.col = col;
                p.id = colorStartingPositions.size();
                mesh.addVertex(p.nextPos);
                mesh.addColor(col);
                p.lastIndex = mesh.getNumVertices() - 1;
                p.nextPos.x += 5;
                colorStartingPositions.push_back(p);
            }
            //i++;
            //float percent = (float)i;// / (float)(NUM_STEPS*NUM_STEPS);
            //cout << percent << "%" << endl;
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
