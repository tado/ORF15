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
    template <typename List>
    void split(const string& s, const string& delim, List& result);
    
    ofSoundStream soundStream;
    vector<BytebeatGenerator *> bytebeats;
    unsigned long time;
    unsigned int rateDivider;
};
