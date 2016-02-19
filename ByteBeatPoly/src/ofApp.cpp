#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    soundStream.printDeviceList();
    soundStream.setDeviceID(4);
    soundStream.setup(this, 2, 0, 96000, 1024, 4);
    
    ofHideCursor();
    loadData();
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < bytebeats.size(); i++) {
        bytebeats[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    for (int i = 0; i < bytebeats.size(); i++) {
        bytebeats[i]->draw();
        ofTranslate(0, ofGetHeight()/bytebeats.size());
    }
    ofPopMatrix();
}

void ofApp::audioOut(float* output, int n, int channels) {
    for(int k = 0; k < bytebeats.size(); k++) {
        bytebeats[k]->audioOut();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < channels; j++) {
                output[i * channels + j] += bytebeats[k]->output[i * channels + j] * (1.0 / bytebeats.size());
            }
        }
    }
}

template <typename List>
void ofApp::split(const string& s, const string& delim, List& result)
{
    result.clear();
    using string = string;
    string::size_type pos = 0;
    while(pos != string::npos ){
        string::size_type p = s.find(delim, pos);
        if(p == string::npos){
            result.push_back(s.substr(pos));
            break;
        }
        else {
            result.push_back(s.substr(pos, p - pos));
        }
        pos = p + delim.size();
    }
}

void ofApp::loadData(){
    bytebeats.clear();
    string data = ofBufferFromFile("bytebeat.txt").getText();
    vector<string> beatStr;
    split(data, ";", beatStr);
    for (int i = 0; i < beatStr.size(); i++) {
        BytebeatGenerator *bg = new BytebeatGenerator();
        bg->setup();
        bg->beat = beatStr[i] + ";";
        bytebeats.push_back(bg);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {
        loadData();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
