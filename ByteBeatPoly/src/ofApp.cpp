#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    soundStream.printDeviceList();
    soundStream.setDeviceID(4);
    soundStream.setup(this, 2, 0, 96000, 1024, 4);
    bytebeatFbo.allocate(ofGetWidth(), ofGetHeight());
    
    time = 0;
    rateDivider = 12;
    
    bytebeatHeader = R"(
    #extension GL_EXT_gpu_shader4 : enable
    const int width = 1920*1080;
    void main() {
        int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x);
        int v =
    )";
    bytebeatFooter = R"(
        gl_FragColor = vec4(vec3(float(v % 256) / 256.),1.);
    }
    )";
}

//--------------------------------------------------------------
void ofApp::update(){
    string data = ofBufferFromFile("bytebeat.txt").getText();
    string bytebeatAll = bytebeatHeader + data + bytebeatFooter;
    bytebeatShader.setupShaderFromSource(GL_FRAGMENT_SHADER, bytebeatAll);
    bytebeatShader.linkProgram();
}

//--------------------------------------------------------------
void ofApp::draw(){
    bytebeatFbo.begin();
    bytebeatShader.begin();
    ofFill();
    ofDrawRectangle(0, 0, bytebeatFbo.getWidth(), bytebeatFbo.getHeight());
    bytebeatShader.end();
    bytebeatFbo.end();
    bytebeatFbo.readToPixels(audioPixels);
    bytebeatFbo.draw(0, 0);
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
