#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  ofSetVerticalSync( true );
  
  isFullScreen = false;
  isCapturing = false;
  
  int camWidth = 1080;
  int camHeight = 1920;
  
  
  vector<ofVideoDevice> devices = grabber.listDevices();
  numGrabbers = devices.size();
  
  for(int i = 0; i < devices.size(); i++){
    cout << devices[i].id << ": " << devices[i].deviceName;
    if( devices[i].bAvailable ){
      cout << endl;
    }else{
      cout << " - unavailable " << endl;
    }
  }
  
  grabber.setDeviceID( 0 );
  grabber.setDesiredFrameRate( 60 );
  grabber.initGrabber( camWidth, camHeight );
  
  numCaptures = 0;
  
  portrait.loadImage("bowie.jpg");
  
  res = portrait.getRes();
}


//--------------------------------------------------------------
void ofApp::update(){
  grabber.update();
}


//--------------------------------------------------------------
void ofApp::draw(){
  
  ofClear( 0 );

  
  if( !isCapturing )
  {
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    
    int ix = 0;
    int iy = 0;
    
    for( iy = 0; iy < res; iy++ )
    {
      for( ix = 0; ix < res; ix++ )
      {
        float pw, ph;
        
        pw = ofGetWidth()/res;
        ph = ofGetHeight()/res;
        
        
        //draw subImage
        ofSetColor( 70, 255 );
        portrait.draw( ix * pw, iy * ph, pw, ph );
        
        
        //get colour from portrait
        //portrait has this info - should be able to just call getColor(ix, iy)
        ofColor c = portrait.getColor( portrait.getWidth()/res * ix + (portrait.getWidth()/res/2),
                                       portrait.getHeight()/res * iy + (portrait.getHeight()/res/2) );
        
        //store brightness in alpha
        c.a = c.getBrightness();
        
        float brightness = 0.7;
        c.setBrightness( c.a * brightness );

        ofSetColor( c );
        
        //draw rect over pixel image to set master tone
        ofRect( ix * pw, iy * ph, pw, ph );
        
      }
    }
    

    ofEnableBlendMode( OF_BLENDMODE_SCREEN );
    ofColor c;
    c.r = 255;
    c.g = 255;
    c.b = 255;
    c.a = 120;
    c.setBrightness( 60 );
    ofSetColor( c );
    portrait.draw( 0.0, 0.0, ofGetWidth(), ofGetHeight() );
  }
  else //is capturing
  {
    ofSetColor( 255 );
    grabber.draw( 0, 0, ofGetWidth(), ofGetHeight() );
  }
  
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key ){

  switch( key )
  {
      
    case '-':
      portrait.decrementRes();
      res = portrait.getRes();
      break;
      
    case '=':
      portrait.incrementRes();
      res = portrait.getRes();
      break;
      
    case 'f':
      isFullScreen = !isFullScreen;
      ofSetFullscreen( isFullScreen );
      break;
      
    case ' ':
      if( isCapturing )
      {
        //capture image
        cout << "CAPTURING!" << endl;;
        ofImage capture;
        capture.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        capture.saveImage( "frame" + ofToString( numCaptures++ ) + ".png" );
      }
      isCapturing = !isCapturing;
      break;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
