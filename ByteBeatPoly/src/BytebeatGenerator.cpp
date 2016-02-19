//
//  BytebeatGenerator.cpp
//  ByteBeatPoly
//
//  Created by Atsushi Tadokoro on 2/18/16.
//
//

#include "BytebeatGenerator.hpp"

BytebeatGenerator::BytebeatGenerator(){
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    audioPixels.allocate(ofGetWidth(), ofGetHeight(), 4);
    buffer = 1024;
    channels = 2;
    time = 0;
    rateDivider = 8;
    pan = ofRandom(0.4, 0.6);
    output = new float[buffer * channels];
}

void BytebeatGenerator::setup(){
    bytebeatHeader = R"(
#extension GL_EXT_gpu_shader4 : enable
    const int width = 1920;
    void main() {
        int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x);
        int v =
        )";
        bytebeatFooter = R"(
        gl_FragColor = vec4(vec3(float(v % 256) / 256.),1.);
    }
    )";
}

void BytebeatGenerator::update(){
    string bytebeatAll = bytebeatHeader + beat + bytebeatFooter;
    bytebeatShader.setupShaderFromSource(GL_FRAGMENT_SHADER, bytebeatAll);
    bytebeatShader.linkProgram();
}

void BytebeatGenerator::draw(){
    bytebeatFbo.begin();
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
    if(cwh > 0) {
        for(int i = 0; i < buffer; i++) {
            int curTime = (time / rateDivider) % wh;
            int curPixel = curTime * 4;
            int cur = pixels[curPixel];
            output[i * channels + 0] = (cur / 128. - 1.) * pan * 4.0;
            output[i * channels + 1] = (cur / 128. - 1.) * (1.0 - pan) * 4.0;
            time++;
        }
    }
}