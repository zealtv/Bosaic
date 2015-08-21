#pragma once

#include "ofMain.h"
#include "portraitImage.h"
#include "cell.h"

#define MAX_CELLS 60 * 60 * 2


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
    float aspectRatio;
    bool isCapturing;
    ofVideoGrabber grabber;
    int camWidth;
    int camHeight;
    ofTexture *camTexture;
    int numGrabbers;
    int numCaptures;
    int camRotate;
    vector<cell> cells;
    void loadCaptures();
    void createRandomizedCellIndex();
//    int RandomizedCellIndex[ 60 * 60 ];
    vector<int> RandomizedCellIndex;
  
    int toggleTime;
    bool isZoomingIn;
    bool isZoomingOut;
    int transistionSpeed;
  
    bool doAnimate;
  
    int TOP_RES;
  
    int cellOffset;
    ofColor singleColor;

  
};
