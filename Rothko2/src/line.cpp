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

void line::setup(float base) {
    for(int i = 0; i < LINE_RESOLUTION; i++) {
        ofVec2f p;
        p.x = i * ofGetWidth() / LINE_RESOLUTION;
        p.y = ofGetHeight() / 2;
        mesh.addVertex(ofVec3f(p.x, p.y, 0));
        mesh.addColor(col);
        mesh.addVertex(ofVec3f(p.x, base));
        mesh.addColor(255);

    }
    for(int i = 0; i < mesh.getNumVertices()-2; i++) {
        mesh.addIndex(i);
        mesh.addIndex(i+1);
        mesh.addIndex(i+2);
    }
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
}

void line::update(line* comparatorLine) {
    if(comparatorLine == nullptr) {
        return;
    } else {
        for(int i = 0; i < noiseIterations; i++) {
            float o = i;
            for(int j = 0; j < mesh.getNumVertices(); j+=2) {
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
