#include "ofApp.h"

void ofApp::setup() {
	//ofSetFrameRate();
    soundStream.printDeviceList();
    soundStream.setDeviceID(3);
    soundStream.setup(this, 2, 0, 96000, 2048, 4);
	fbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
	time = 0;
    rateDivider = 8;
    
    bytebeatShader.load("bytebeat");
}

void ofApp::update() {
}

void ofApp::draw() {
	ofSetColor(255);
	
	fbo.begin();
	bytebeatShader.begin();
	ofFill();
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
	bytebeatShader.end();
	fbo.end();
	fbo.draw(0, 0);
	fbo.readToPixels(audioPixels);
}


void ofApp::audioOut(float* input, int n, int channels) {
    unsigned char* pixels = audioPixels.getData();
    
	int wh = audioPixels.getWidth() * audioPixels.getHeight();
	int cwh = audioPixels.getNumChannels() * wh;
	if(cwh > 0) {
		for(int i = 0; i < n; i++) {
			int curTime = (time / rateDivider) % wh;
			int curPixel = 4 * curTime;
			for(int j = 0; j < channels; j++) {
				int cur = pixels[curPixel + j];
				input[i * channels + j] = cur / 128. - 1.;
                input[i * channels + j] *= .5;
            }
			time+=1;
		}
	}
}