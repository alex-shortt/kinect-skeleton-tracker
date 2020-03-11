#include "ofApp.h"

#include "ofxNI2.h"

ofEasyCam cam;

size_t SCREEN_W;
size_t SCREEN_H;

bool showDebugging = true;
int NEAR = 1300;
int FAR = 2400;
int TRANSLATE_X = 0;
int TRANSLATE_Y = 0;
float ZOOM = 1;
float TOLERANCE_RANGE = 0.8;

//--------------------------------------------------------------
void ofApp::setup()
{
	SCREEN_W = ofGetScreenWidth();
	SCREEN_H = ofGetScreenHeight();
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	wrapper.load("movies/waves.mp4");
	wrapper.play();

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
	wrapper.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// setup video frame, deptht data
	ofPixels framePixels = wrapper.getPixels();
	ofImage *depthFrame = new ofImage(tracker.getPixelsRef(NEAR, FAR));
	depthFrame->resize((int) framePixels.getWidth(), (int) framePixels.getHeight());
	ofPixels depthPixels =  depthFrame->getPixels();
	delete depthFrame;
	
	// resize/recolor video
    for (int y = 0; y < framePixels.getHeight(); y++) {
        for (int x = 0; x < framePixels.getWidth(); x++) {
            unsigned long i = y * framePixels.getHeight() + x;
			
			float dist = depthPixels[i] / 255.0;
			int opacity = 0 ;
			float diff = (1 - TOLERANCE_RANGE) / 2.0f;
			
			if(dist > diff && dist < 1 - diff){
				opacity = 1;
			}
			
	
			unsigned int r = (int) framePixels[i * 3] * opacity;
			unsigned int g = (int) framePixels[i * 3 + 1] * opacity;
			unsigned int b = (int) framePixels[i * 3 + 2] * opacity;
            framePixels.setColor( x, y , ofColor(r, g, b));
        }
    }
	
	// draw
	ofPushMatrix();

	ofScale(ZOOM);
	ofTranslate(TRANSLATE_X, TRANSLATE_Y);
    
	ofTexture depthTexture;
	depthTexture.loadData(framePixels); // takes a long	 time
	depthTexture.draw(0, 0);
	
	ofPopMatrix();
	
	if (showDebugging){
		tracker.draw();
		ofDrawBitmapString("TRANSLATE_Y (r+/f-): " + ofToString(TRANSLATE_Y), 20, ofGetHeight() - 120);
		ofDrawBitmapString("TRANSLATE_X (t+/g-): " + ofToString(TRANSLATE_X), 20, ofGetHeight() - 100);
		ofDrawBitmapString("ZOOM (y+/h-): " + ofToString(ZOOM), 20, ofGetHeight() - 80);
		ofDrawBitmapString("TOLERANCE_RANGE (u+/j-): " + ofToString(TOLERANCE_RANGE), 20, ofGetHeight() - 60);
		ofDrawBitmapString("NEAR (i+/k-): " + ofToString(NEAR), 20, ofGetHeight() - 40);
		ofDrawBitmapString("FAR (o+/l-): " + ofToString(FAR), 20, ofGetHeight() - 20);
		
		ofDrawBitmapString("Tracker FPS: "+ofToString(tracker.getFrameRate()),20,ofGetHeight()-10);
		ofDrawBitmapString("Application FPS: "+ofToString(ofGetFrameRate()),20,ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'd') {
		showDebugging = !showDebugging;
	} else if (key == 'i') {
		NEAR += 100;
	} else if (key == 'k') {
		NEAR -= 100;
	} else if (key == 'o') {
		FAR += 100;
	} else if (key == 'l') {
		FAR -= 100;
	} else if (key == 'u') {
	   TOLERANCE_RANGE += 0.05;
	} else if (key == 'j') {
	   TOLERANCE_RANGE -= 0.05;
	} else if (key == 'y') {
		ZOOM += 0.05;
	}  else if (key == 'h') {
		ZOOM -= 0.05;
    } else if (key == 't') {
		TRANSLATE_X += 20;
	} else if (key == 'g') {
		TRANSLATE_X -= 20;
	} else if (key == 'r') {
		TRANSLATE_Y += 20;
	} else if (key == 'f') {
		TRANSLATE_Y -= 20;
	}
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
