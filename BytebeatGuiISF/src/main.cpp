#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 512, 512, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}
