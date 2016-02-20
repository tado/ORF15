#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    soundStream.printDeviceList();
    soundStream.setDeviceID(4);
    nChannels = 2;
    bufferSize = 1024;
    soundStream.setup(this, nChannels, 0, 96000, bufferSize, 4);
    ofHideCursor();
    loadData();
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < bytebeats.size(); i++) {
        bytebeats[i]->update();
    }
    if (lastBeat != ofBufferFromFile("bytebeat.txt").getText()) {
        loadData();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
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

vector<string> ofApp::split(const string &str, char delim){
    istringstream iss(str); string tmp; vector<string> res;
    while(getline(iss, tmp, delim)) res.push_back(tmp);
    return res;
}

void ofApp::loadData(){
    bytebeats.clear();
    string data = ofBufferFromFile("bytebeat.txt").getText();
    lastBeat = data;
    data = data.substr(0, data.length()-1);
    vector<string> beatStr = split(data, ';');
    for (int i = 0; i < beatStr.size(); i++) {
        BytebeatGenerator *bg = new BytebeatGenerator(bufferSize, nChannels);
        bg->height = ofGetHeight() / beatStr.size();
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
