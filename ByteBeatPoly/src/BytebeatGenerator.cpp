//
//  BytebeatGenerator.cpp
//  ByteBeatPoly
//
//  Created by Atsushi Tadokoro on 2/18/16.
//
//

#include "BytebeatGenerator.hpp"

BytebeatGenerator::BytebeatGenerator(int _bufferSize, int _nChannels){
    bufferSize = _bufferSize;
    nChannels = _nChannels;
    rateDivider = 16;
    pan = ofRandom(0.4, 0.6);
    output = new float[bufferSize * nChannels];
    width = ofGetWidth();
    height = ofGetHeight();
}

void BytebeatGenerator::setup(long *_time){
    time = _time;
    bytebeatFbo.allocate(width, height);
    audioPixels.allocate(width, height, 4);
    
    bytebeatHeader = R"(
    #extension GL_EXT_gpu_shader4 : enable
    const int width = 1920*1080;
    void main() {
        int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x);
        int v = )";
    bytebeatFooter = R"(
        gl_FragColor = vec4(vec3(float(v % 256) / 256.),1.);
    })";
}

void BytebeatGenerator::update(){
    string bytebeatAll = bytebeatHeader + beat + bytebeatFooter;
    bytebeatShader.setupShaderFromSource(GL_FRAGMENT_SHADER, bytebeatAll);
    bytebeatShader.linkProgram();
}

void BytebeatGenerator::draw(){
    bytebeatFbo.begin();
    ofClear(0);
    bytebeatShader.begin();
    ofSetColor(255);
    ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
    bytebeatFbo.end();
    bytebeatFbo.draw(0, 0);
    bytebeatFbo.readToPixels(audioPixels);
}

void BytebeatGenerator::audioOut(){
    unsigned char* pixels = audioPixels.getData();
    int wh = audioPixels.getWidth() * audioPixels.getHeight();
    int cwh = audioPixels.getNumChannels() * wh;
    long t = *time;
    if(cwh > 0) {
        for(int i = 0; i < bufferSize; i++) {
            int curTime = (t / rateDivider) % wh;
            int curPixel = curTime * 4;
            int cur = pixels[curPixel];
            output[i * nChannels + 0] = (cur / 128. - 1.) * pan * 4.0;
            output[i * nChannels + 1] = (cur / 128. - 1.) * (1.0 - pan) * 4.0;
            t++;
        }
    }
}