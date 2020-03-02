#include "ofApp.h"

#include "ofxNI2.h"

ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::setup()
{
	 ofSetFrameRate(60);
	   ofSetVerticalSync(true);
	   ofBackground(0);

	   device.setLogLevel(OF_LOG_NOTICE);
	   device.setup(0);
	   tracker.setup(device);
}

void ofApp::exit()
{
	tracker.exit();
    device.exit();
}

//--------------------------------------------------------------
void ofApp::update()
{
	device.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	depthPixels = tracker.getPixelsRef(1000, 4000);
    depthTexture.loadData(depthPixels);

    // draw in 2D
    ofSetColor(255);
    depthTexture.draw(0, 0);
    tracker.draw();
	
	ofDrawBitmapString("Tracker FPS: "+ofToString(tracker.getFrameRate()),20,ofGetHeight()-40);
    ofDrawBitmapString("Application FPS: "+ofToString(ofGetFrameRate()),20,ofGetHeight()-20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
