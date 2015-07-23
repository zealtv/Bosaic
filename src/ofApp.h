#pragma once

#include "ofMain.h"
#include "portraitImage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
    int pixelsX;
    int pixelsY;
		
    portraitImage portrait;
  
    bool isFullScreen;
  
  private:
    int res;
    bool isCapturing;
    ofVideoGrabber grabber;
    int camWidth;
    int camHeight;
    ofTexture camTexture;
    int numGrabbers;
    int numCaptures;

  
};
