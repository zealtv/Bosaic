#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  //these work
  //60, 30, 20, 15, 10, 6, 5, 4, 3, 2, 1
  pixelsX = 30;
  pixelsY = pixelsX;
  
  portrait.loadImage("bowie.jpg");
}


//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
  
  ofClear( 0 );

  ofEnableBlendMode( OF_BLENDMODE_ADD );
  
  int ix = 0;
  int iy = 0;
  
  for( iy = 0; iy < pixelsY; iy++ )
  {
    for( ix = 0; ix < pixelsX; ix++ )
    {
      float pw, ph;
      
      pw = ofGetWidth()/pixelsX;
      ph = ofGetHeight()/pixelsY;
      
      
      //draw subImage
      ofSetColor( 70, 255 );
      portrait.draw( ix * pw, iy * ph, pw, ph );
      
      
      //get colour from portrait
      ofColor c = portrait.getColor( portrait.getWidth()/pixelsX * ix + (portrait.getWidth()/pixelsX/2),
                                     portrait.getHeight()/pixelsY * iy + (portrait.getHeight()/pixelsY/2) );
      
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

//--------------------------------------------------------------
void ofApp::keyPressed( int key ){

  switch( key )
  {
    case ',':
      pixelsY = --pixelsX;
      cout << pixelsX << endl;
      break;
    case '.':
      pixelsY = ++pixelsX;
      cout << pixelsX << endl;
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
