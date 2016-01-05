#include "ofApp.h"

void ofApp::setup() {
    soundStream.printDeviceList();
    soundStream.setDeviceID(2);
    soundStream.setup(this, 2, 0, 96000, 1024, 4);
    //ofSoundStreamSetup(2, 0, 96000, 512, 3);
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    fxFbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
    time = 0;
    rateDivider = 12;
    
    bytebeatShader.load("bytebeat");
    bytebeatShader.setMillisBetweenFileCheck(100);
    
    fx = new ofxSCSynth("bytebeatFx");
    fx->create();
    fx->set("amp", 0.2);
    
    chain = new ofxISF::Chain();
    chain->setup(ofGetWidth(), ofGetHeight(), GL_RGB32F);
    chain->setImage(bytebeatFbo.getTexture());
    chain->load("ISF/RGB Halftone-lookaround.fs");
    chain->load("ISF/Strobe.fs");
    chain->load("ISF/Convergence.fs");
    chain->load("ISF/Collage.fs");
    chain->load("ISF/Pixel Shifter.fs");
    chain->load("ISF/KaleidoCenter.fs");
    chain->load("ISF/Kaleidoscope Tile.fs");
    chain->load("ISF/Pixellate.fs");
    chain->load("ISF/Quad Tile.fs");
    chain->load("ISF/Meta Image.fs");
    //chain->load("ISF/Noise Blur 4dl.fs");
    for (int i = 0; i < chain->size(); i++) {
        chain->toggle(i);
    }
}

void ofApp::update() {
    //chain->getShader(0)->setUniform<float>("seed", ofRandom(0.01, 1.0));
    //unique_lock<mutex> lock(audioMutex);
    chain->update();
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
    
    fxFbo.begin();
    chain->draw(0, 0);
    fxFbo.end();
    fxFbo.readToPixels(audioPixels);
    fxFbo.draw(0, 0);
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
    if (key == '1') {
        chain->toggle(0);
    }
    if (key == '2') {
        chain->toggle(1);
    }
    if (key == '3') {
        chain->toggle(2);
    }
    if (key == '4') {
        chain->toggle(3);
    }
    if (key == '5') {
        chain->toggle(4);
    }
    if (key == '6') {
        chain->toggle(5);
    }
    if (key == '7') {
        chain->toggle(6);
    }
    if (key == '8') {
        chain->toggle(7);
    }
    if (key == '9') {
        chain->toggle(8);
    }
    if (key == '0') {
        for (int i = 0; i < chain->size(); i++) {
            chain->toggle(i);
        }
    }
}