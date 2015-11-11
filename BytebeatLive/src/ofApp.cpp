#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(15);
    soundStream.printDeviceList();
    soundStream.setDeviceID(2);
    soundStream.setup(this, 2, 0, 96000, 2048, 4);
	fbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
	time = 0;
    rateDivider = 8;
}

void ofApp::update() {
    shader.load("", "bytebeat.frag");
}

void ofApp::draw() {
	ofSetColor(255);
	
	fbo.begin();
	shader.begin();
	ofFill();
    ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
	shader.end();
	fbo.end();
	fbo.draw(0, 0);
	fbo.readToPixels(audioPixels);
}


void ofApp::audioOut(float* input, int n, int channels) {
	//unsigned char* pixels = audioPixels.getPixels();
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
                input[i * channels + j] *= .75;
            }
			time+=1;
		}
	}
}