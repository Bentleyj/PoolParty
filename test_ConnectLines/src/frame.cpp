#include "Frame.h"

Frame::Frame() {
    img = nullptr;
	shader.load("shaders/cutout");
}

float Frame::angleBetweenTwoPoints(ofVec2f p1, ofVec2f p2)
{
	return atan2(p2.y - p1.y, p2.x - p1.x);
}

ofVec2f Frame::getMidpoint(ofVec2f p1, ofVec2f p2) {
    return ofVec2f((p1.x + p2.x)/2, (p1.y + p2.y)/2);
}

void Frame::draw() 
{
	ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
    float aVal = angleBetweenTwoPoints(startPoint, endPoint);
    float aTar = angleBetweenTwoPoints(targetStartPoint, targetEndPoint);

    float diff = (aTar - aVal) * 180 / PI;
    
    ofVec2f midPointVal = getMidpoint(startPoint, endPoint);
    ofVec2f midPointTar = getMidpoint(targetStartPoint, targetEndPoint);
    
    ofVec2f midPointDiff = midPointTar - midPointVal;
    
    float distVal = distance(startPoint, endPoint);
    float distTar = distance(targetStartPoint, targetEndPoint);
    
    float percent = distVal / distTar;

	ofPopStyle();
	ofPushStyle();
	ofTranslate(midPointDiff);
    ofTranslate(midPointVal);
    ofRotate(diff, 0, 0, 1);
    ofScale(1/percent, 1/percent);
    ofTranslate(-midPointVal);
    if(img != nullptr) {
        ofSetColor(255, 255, 255, 127);
		//shader.begin();
		//shader.setUniformTexture("diffuseTexture", *img, 0);
		//shader.setUniform4f("bounds", x, y, x + width, y + height);
        img->draw(0, 0);
		//shader.end();
    }
	ofNoFill();

    vector<ofPoint> verts = line->getVertices();
    if (verts.size() > 2) {
        for (int i = 1; i < verts.size() - 1; i++) {
            if (isInsideBox(verts[i])) {
                ofDrawLine(verts[i], verts[i + 1]);
            }
            if (!isInsideBox(verts[i - 1]) && isInsideBox(verts[i])) {
                startPoint = getNearestEdge(verts[i], verts[i - 1]);
                ofSetColor(0, 0, 255);
                ofDrawLine(verts[i], verts[i - 1]);
            }
            else if (isInsideBox(verts[i]) && !isInsideBox(verts[i + 1])) {
                endPoint = getNearestEdge(verts[i], verts[i + 1]);
                ofSetColor(0, 0, 255);
                ofDrawLine(verts[i], verts[i + 1]);
            }
        }
        ofSetColor(255, 127, 127);
        ofDrawLine(startPoint, endPoint);
        ofDrawCircle(midPointVal, 5);
    }
    
	ofSetColor(0, 255, 0);
	ofDrawCircle(startPoint, 5);
	ofSetColor(255, 0, 0);
	ofDrawCircle(endPoint, 5);

	ofPopMatrix();
    
    ofSetColor(0, 200, 0);
    ofDrawCircle(targetStartPoint, 5);
    
    ofSetColor(200, 0, 0);
    ofDrawCircle(targetEndPoint, 5);
    
    ofSetColor(127, 255, 127);
    ofDrawLine(targetStartPoint, targetEndPoint);
    ofDrawCircle(midPointTar, 5);

	ofSetColor(255);
	ofDrawRectangle(x, y, width, height);
	ofPopStyle();
    
}

bool Frame::isInsideBox(ofVec2f p)
{
	if (p.x > x && p.x < x + width) {
		if (p.y > y && p.y < y + height) {
			return true;
		}
	}
	return false;
}

ofVec2f Frame::getNearestEdge(ofVec2f p1, ofVec2f p2)
{
	float m = (p2.y - p1.y) / (p2.x - p1.x);
	float b = p2.y - m * p2.x;

	float leftX = x;
	float leftY = m * leftX + b;

	float rightX = x + width;
	float rightY = m * rightX + b;

	float topY = y;
	float topX = (topY - b) / m;

	float bottomY = y + height;
	float bottomX = (bottomY - b) / m;

	float leftDist = distance(p1, ofVec2f(leftX, leftY));
	float rightDist = distance(p1, ofVec2f(rightX, rightY));
	float topDist = distance(p1, ofVec2f(topX, topY));
	float bottomDist = distance(p1, ofVec2f(bottomX, bottomY));

	ofVec3f nearest;
	nearest = ofVec2f(leftX, leftY);

	float minDist = width + height;
	if (leftDist < minDist) {
		minDist = leftDist;
	}
	if (rightDist < minDist) {
		minDist = rightDist;
		nearest = ofVec2f(rightX, rightY);
	}
	if (topDist < minDist) {
		minDist = topDist;
		nearest = ofVec2f(topX, topY);
	}
	if (bottomDist < minDist) {
		nearest = ofVec2f(bottomX, bottomY);
	}
	return nearest;
}

float Frame::distance(ofVec2f p1, ofVec2f p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void Frame::setTargetStartPoint(ofVec2f p) {
    targetStartPoint = getTargetPoint(p);
}

void Frame::setTargetEndPoint(ofVec2f p) {
    targetEndPoint = getTargetPoint(p);
}

ofVec2f Frame::getTargetPoint(ofVec2f p) {
    if(isInsideBox(p)) {
        return ofVec2f(0, 0);
    }
    if(p.y < y + height && p.y > y) {
        if(p.x < x) {
            return ofVec2f(x, p.y);
        } else if(p.x > x + width) {
            return ofVec2f(x + width, p.y);
        }
    }
    if(p.x < x + width && p.x > x) {
        if(p.y < y) {
            return ofVec2f(p.x, y);
        } else if(p.y > y + height) {
            return ofVec2f(p.x, y + height);
        }
    }
    if(p.x > x + width) {
        if(p.y > y + height) {
            return ofVec2f(x + width, y + height);
        } else if(p.y < y) {
            return ofVec2f(x + width, y);
        }
    }
    if(p.x < x) {
        if(p.y > y + height) {
            return ofVec2f(x, y + height);
        } else if(p.y < y) {
            return ofVec2f(x, y);
        }
    }
}


Frame::~Frame() {
    img = nullptr;
    line = nullptr;
}
