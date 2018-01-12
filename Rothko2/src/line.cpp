//
//  line.cpp
//  Rothko2
//
//  Created by cafe on 11/01/2018.
//

#include "line.hpp"

#define LINE_RESOLUTION 300

line::line() {
    offset = ofRandom(10000);
}

void line::setup() {
    for(int i = 0; i < LINE_RESOLUTION; i++) {
        ofVec2f p;
        p.x = i * ofGetWidth() / LINE_RESOLUTION;
        p.y = ofGetHeight() / 2;
        mesh.addVertex(ofVec3f(p.x, p.y, 0));
        //points.push_back(p);
    }
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
}

void line::update(line* comparatorLine) {
    if(comparatorLine == nullptr) {
        return;
    } else {
        for(int i = 0; i < noiseIterations; i++) {
            float o = i;
            for(int j = 0; j < mesh.getNumVertices(); j++) {
                ofVec3f v = mesh.getVertex(j);
                v.y = comparatorLine->mesh.getVertex(j).y + sign * ofNoise(ofGetElapsedTimef() * noiseSpeed, mesh.getVertex(j).x * (noiseScale*o), offset) * noiseSize*o;
                v.y += sign * baseHeight;
                mesh.setVertex(j, v);
            }
            
        }
    }
}

void line::draw() {
    ofPushStyle();
    ofSetColor(col);
    mesh.draw();
//    for(int i = 0; i < points.size()-1; i++) {
//        ofDrawLine(points[i], points[i+1]);
//    }
    ofPopStyle();
}
