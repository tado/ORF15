#include "ofApp.h"

void ofApp::setup() {
    soundStream.printDeviceList();
    soundStream.setDeviceID(3);
    soundStream.setup(this, 2, 0, 96000, 2048, 4);
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    fxFbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
	time = 0;
    rateDivider = 12;
    useFx = false;
    
    bytebeatShader.load("bytebeat");
    fxShader.load("fxShader");
    bytebeatShader.setMillisBetweenFileCheck(100);
    
    fx = new ofxSCSynth("bytebeatFx");
    fx->create();
    fx->set("amp", 0.5);
}

void ofApp::update() {
}

void ofApp::exit(){
    fx->free();
    delete fx;
}

void ofApp::draw() {
	ofSetColor(255);
	
	bytebeatFbo.begin();

    bytebeatShader.begin();
	ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
	bytebeatFbo.end();
    
    if (useFx) {
        fxFbo.begin();
        fxShader.begin();
        fxShader.setUniform1f("u_time", ofGetElapsedTimef() );
        bytebeatFbo.draw(0, 0);
        fxShader.end();
        fxFbo.end();
        fxFbo.draw(0, 0);
        fxFbo.readToPixels(audioPixels);
    } else {
        bytebeatFbo.draw(0, 0);
        bytebeatFbo.readToPixels(audioPixels);
    }
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
                input[i * channels + j] *= .75;
            }
			time+=1;
		}
	}
}

void ofApp::keyPressed(int key){
    if (key == 'f') {
        if (useFx == false) {
            useFx = true;
        } else {
            useFx = false;
        }
    }
}