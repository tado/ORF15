#pragma once

#include "ofMain.h"
#include "BytebeatGenerator.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void loadData();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut(float * input, int bufferSize, int nChannels);
    vector<string> split(const string &str, char delim);
    
    ofSoundStream soundStream;
    vector<BytebeatGenerator *> bytebeats;
    unsigned int rateDivider;
    int bufferSize;
    int nChannels;
    string lastBeat;
    long time;
};
