//
//  BytebeatGenerator.hpp
//  ByteBeatPoly
//
//  Created by Atsushi Tadokoro on 2/18/16.
//
//

#pragma once
#include "ofMain.h"

class BytebeatGenerator {
public:
    BytebeatGenerator();
    void setup();
    void update();
    void draw();
    void audioOut();
    
    ofShader bytebeatShader;
    ofFbo bytebeatFbo;
    ofPixels audioPixels;
    int rateDivider;
    int time;
    
    string bytebeatHeader;
    string bytebeatFooter;
    string beat;

    int buffer;
    int channels;
    float *output;
    float pan;
};
