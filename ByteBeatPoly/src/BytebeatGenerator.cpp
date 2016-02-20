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
    rateDivider = 12;
    time = 0;
    pan = ofRandom(0.4, 0.6);
    output = new float[bufferSize * nChannels];
    width = ofGetWidth();
    height = ofGetHeight();
}

void BytebeatGenerator::setup(){
    bytebeatFbo.allocate(width, height);
    audioPixels.allocate(width, height, 4);
    
    bytebeatHeader = R"(
    #extension GL_EXT_gpu_shader4 : enable
    const int width = 1920;
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
    ofSetColor(255);
    bytebeatFbo.begin();
    ofClear(0);
    bytebeatShader.begin();
    ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
    bytebeatFbo.end();
    bytebeatFbo.draw(0, 0);
    bytebeatFbo.readToPixels(audioPixels);

    /*
    int wh = audioPixels.getWidth() * audioPixels.getHeight();
    int curTime = (time / rateDivider) % wh;
    ofDrawLine(0, curTime / width, width, curTime / width);
    ofSetColor(255, 0, 0);
    ofDrawRectangle(curTime % width, curTime / width, 8, 8);
    ofSetColor(255);
     */
}

void BytebeatGenerator::audioOut(){
    unsigned char* pixels = audioPixels.getData();
    int wh = audioPixels.getWidth() * audioPixels.getHeight();
    int cwh = audioPixels.getNumChannels() * wh;
    if(cwh > 0) {
        for(int i = 0; i < bufferSize; i++) {
            int curTime = (time / rateDivider) % wh;
            int curPixel = curTime * 4;
            int cur = pixels[curPixel];
            output[i * nChannels + 0] = (cur / 128. - 1.) * pan * 2.0;
            output[i * nChannels + 1] = (cur / 128. - 1.) * (1.0 - pan) * 2.0;
            time++;
        }
    }
}