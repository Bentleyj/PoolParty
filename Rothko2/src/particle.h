#pragma once

#include "ofMain.h"

class Particle {
public:
	//Fields
	ofVec2f pos;
	float height;
	float width;
	float mass;
	int offset;
	//Constructor
	Particle();
	~Particle();
	// Functions
	void draw();
	void update();
	ofColor col;

};