#pragma once

#include "ofMain.h"
#include "ofxSuperCollider.h"

class SawSynth {
public:
    SawSynth(int n);
    ~SawSynth();
    void update();
    void draw();
    void clear();
    
    ofxSCSynth *synth;
    int nth;
    float freq;
    float detune;
    float alpha;
    float startTime;
    float phase;
    float height;
    bool death;
    float alphaMax;
    int deleteMode; // 0:none, 1:front, 2:back
};
