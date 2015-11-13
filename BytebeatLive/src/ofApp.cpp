#include "ofApp.h"

void ofApp::setup() {
    soundStream.printDeviceList();
    soundStream.setDeviceID(3);
    soundStream.setup(this, 2, 0, 96000, 1024, 4);
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
    time = 0;
    rateDivider = 12;
    sawNum = 0;
    
    bytebeatShader.load("bytebeat");
    bytebeatShader.setMillisBetweenFileCheck(100);
    
    sawFx = new ofxSCSynth("col_closefx");
    sawFx->create();
    fx = new ofxSCSynth("bytebeatFx");
    fx->create();
    fx->set("amp", 0.15);

    currentNoiseAmp = setNoiseAmp = 0.0;
    post = new ofxPostProcessing();
    post->init(ofGetWidth(), ofGetHeight());
    noise = post->createPass<NoiseWarpPass>();
    noise->setAmplitude(currentNoiseAmp);
    noise->setFrequency(8.0);
    noise->setEnabled(true);
}

void ofApp::update() {
    currentNoiseAmp += (setNoiseAmp - currentNoiseAmp) / 1000.0;
    noise->setAmplitude(currentNoiseAmp);
}

void ofApp::exit(){
    fx->free();
    delete fx;
    sawFx->free();
    delete sawFx;
    for (int i = 0; i < saws.size(); i++) {
        saws[i]->synth->free();
    }
}

void ofApp::draw() {
    ofSetColor(255);
    
    bytebeatFbo.begin();
    
    bytebeatShader.begin();
    ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
    bytebeatFbo.end();
    
    post->begin();
    bytebeatFbo.draw(0, 0);
    post->end();
    
    bytebeatFbo.readToPixels(audioPixels);
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
    if (key == 'z') {
        if (saws.size() < 19) {
            SawSynth *saw = new SawSynth(sawNum);
            sawNum++;
            saws.push_back(saw);
            
            if (setNoiseAmp == 0) {
                setNoiseAmp = 0.001;
            } else {
                setNoiseAmp *= 1.4;
            }
        }
    }
}