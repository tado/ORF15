#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(0);
    soundStream.printDeviceList();
    soundStream.setDeviceID(4);
    ofSoundStreamSetup(2, 0, 96000, 1024, 4);
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    fxFbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
    time = 0;
    rateDivider = 12;
    
    bytebeatShader.load("bytebeat");
    bytebeatShader.setMillisBetweenFileCheck(100);

    chain.setup(ofGetWidth(), ofGetHeight(), GL_RGB32F);
    chain.setImage(bytebeatFbo.getTexture());
    gui.setup(&chain);
}

void ofApp::update() {
    gui.update();
    chain.update();
}

void ofApp::exit(){
    /*
     fx->free();
     delete fx;
     */
}

void ofApp::draw() {
    ofSetColor(255);
    bytebeatFbo.begin();
    bytebeatShader.begin();
    ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
    bytebeatFbo.end();
    
    if (chain.size() > 0) {
        fxFbo.begin();
        chain.draw(0, 0);
        fxFbo.end();
        fxFbo.readToPixels(audioPixels);
        fxFbo.draw(0, 0);
    } else {
        bytebeatFbo.readToPixels(audioPixels);
        bytebeatFbo.draw(0, 0);
    }
    
    gui.draw();
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
    int num = key - 49;
    if (chain.size() > num) {
        bool enable = gui.gui.getGroup(chain.getShader(num)->getName()).getToggle("enable");
        if (enable) {
            gui.gui.getGroup(chain.getShader(num)->getName()).getToggle("enable") = false;
            gui.gui.getGroup(chain.getShader(num)->getName()).minimize();
        } else {
            gui.gui.getGroup(chain.getShader(num)->getName()).getToggle("enable") = true;
            gui.gui.getGroup(chain.getShader(num)->getName()).maximize();
        }
    }
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    for(unsigned int i = 0; i < dragInfo.files.size(); i++){
        string extention = dragInfo.files[i].substr(dragInfo.files[i].length()-3, dragInfo.files[i].length());
        string shaderName = dragInfo.files[i].substr(0,dragInfo.files[i].length()-3);
        if (extention == ".fs" || extention == ".vs") {
            if(!chain.load(shaderName)){
                ofLogError() << "Bad ISF format";
            } else {
                gui.addGuiParameters();
            }
        }
    }
}