#include "particle.h"

Particle::Particle()
{
	offset = ofRandom(0, 10000);
}

Particle::~Particle()
{
}

void Particle::draw()
{
	ofPushStyle();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofSetColor(col);
	ofDrawRectangle(pos, width, height);
	ofPopStyle();
}

void Particle::update()
{
	pos.y += (0.5 - ofNoise(ofGetElapsedTimef() + offset)) * 2;
}
