#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  

  //set up globals
  //--------------------------------------
  ofSetEscapeQuitsApp( false );
  
  ofSetVerticalSync( true );
  
  isFullScreen = false;
  isCapturing = false;
  
  toggleTime = 10000;
  transistionSpeed = 200;
  
  TOP_RES = 60;
  
  
  //aspectRatio = 1.77778;
  aspectRatio = 0.5625;
  
  //set up cam
  //--------------------------------------
  camWidth = 1920;
  camHeight = 1080;
  
  
  vector<ofVideoDevice> devices = grabber.listDevices();
  numGrabbers = devices.size();
  
  for( int i = 0; i < devices.size(); i++ )
  {
    cout << devices[i].id << ": " << devices[i].deviceName;
    if( devices[i].bAvailable ){
      cout << endl;
    }
    else
    {
      cout << " - unavailable " << endl;
    }
  }
  
  grabber.setDeviceID( numGrabbers -1  );
  grabber.setDesiredFrameRate( 60 );
  grabber.initGrabber( camWidth, camHeight );
  grabber.setAnchorPoint( camWidth/2, camHeight/2 );
  
  camTexture = &grabber.getTextureReference();
  
  camRotate = 90;
  
  
  
  //set up capture cells
  //--------------------------------------
  loadCaptures();
  cellOffset = (int) ofRandom( 40 );

  
  //set up portrait
  //--------------------------------------
  portrait.loadImage("bowie.jpg");
  
  res = portrait.getRes();
  
  
  
}


//--------------------------------------------------------------
void ofApp::update(){
  
  if( TOP_RES == 60 ) doAnimate = false;
  
  grabber.update();
  
  if( isZoomingIn )
  {
    
    if(  ofGetElapsedTimeMillis() > transistionSpeed )
    {
      portrait.decrementRes();
      res = portrait.getRes();
      ofResetElapsedTimeCounter();
      cellOffset = (int) ofRandom( 40 );
    }
    if( portrait.getRes() == 1 )
    {
      singleColor = portrait.getColor( ofRandom( portrait.getWidth() ), ofRandom( portrait.getHeight()/2 ) );
      isZoomingIn = false;
    }
  }

  if( isZoomingOut )
  {
    if(  ofGetElapsedTimeMillis() > transistionSpeed )
    {
      portrait.incrementRes();
      res = portrait.getRes();
      ofResetElapsedTimeCounter();
      cellOffset = (int) ofRandom( 40 );
    }
    if( portrait.getRes() == TOP_RES ) isZoomingOut = false;
  }
  
  
  
  if( ofGetElapsedTimeMillis() > toggleTime )
  {
    if( portrait.getRes() == TOP_RES && ofGetElapsedTimeMillis() > toggleTime * 2.0 )
    {
      cout<< "zooming in" << endl;
      isZoomingIn = true;
      ofResetElapsedTimeCounter();
    }
    if( portrait.getRes() == 1 )
    {
      cout<< "zooming out" << endl;
      isZoomingOut = true;
      ofResetElapsedTimeCounter();
    }
    
  }
  
}


//--------------------------------------------------------------
void ofApp::draw(){
  

  
  ofClear( 0 );
  
  
  float aspectFactor = ( ofGetHeight() * aspectRatio )/ofGetWidth();
  
  ofPushMatrix();
  //scale to preserve aspect ratio
  ofTranslate( ofGetWidth()/2.0, 0.0 );
  ofScale( aspectFactor, 1.0 );
  ofTranslate( -ofGetWidth()/2.0, 0.0 );

  
  if( !isCapturing )
  {
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    
    int ix = 0;
    int iy = 0;
    
    for( iy = 0; iy < res; iy++ )
    {
      for( ix = 0; ix < res; ix++ )
      {
        

        
        ofPushMatrix();
        //ANIMATE
        if( doAnimate ) ofTranslate( 0.0, 0.0, sin(  0.2*(ix+iy) + (float)ofGetElapsedTimeMillis()/1600.0 ) * 10.0 );
        
        //DRAW CELLS
        //--------------------------------------
        float pw, ph;
        
        pw = ofGetWidth()/res;
        ph = ofGetHeight()/res;
        
        
        int cellIndex = ix + iy * res;
        
        
        //draw subImage

        
        ofSetColor( 100, 255 );
        if(cells.size() > 0)
        {

          
          int randomizedIndex = RandomizedCellIndex[cellIndex + cellOffset];
          cells[ randomizedIndex ].image.draw( ix * pw, iy * ph, pw, ph );
        }
        else portrait.draw( ix * pw, iy * ph, pw, ph );
        
        
        ofColor c;
        
        if( res == 1 ) c = singleColor;
        else  c = portrait.getColor( portrait.getWidth()/res * ix + (portrait.getWidth()/res/2),
                                                   portrait.getHeight()/res * iy + (portrait.getHeight()/res/2) );
        
        //store brightness in alpha
        c.a = 255;
        
        float brightness = 0.7;
        c.setBrightness( c.getBrightness() * brightness );
        
        ofSetColor( c );
        
        //draw rect over cell to set master tone
        ofRect( ix * pw, iy * ph, pw, ph );
        
        
        ofPopMatrix();

        
      }
    }
    

    //DRAW PORTAIT BLEND
    //--------------------------------------
    ofEnableBlendMode( OF_BLENDMODE_SCREEN );
    ofColor c;
    c.r = 255;
    c.g = 255;
    c.b = 255;
    c.a = 120;
    c.setBrightness( 90 );
    ofSetColor( c );
    if(res == 60 || res == 30 ) portrait.draw( 0.0, 0.0, ofGetWidth(), ofGetHeight() );
  }
  else //is capturing
  {

    
    ofPushMatrix();
    
    ofSetColor( 255 );
    ofTranslate( camWidth/2, camHeight/2 );
    ofPixels grabberPixels = grabber.getPixelsRef();
    grabberPixels.rotate90( 1 );
    camTexture->loadData( grabberPixels );
    camTexture->draw( 0.0, 0.0, ofGetWidth(), ofGetHeight() );


    ofPopMatrix();
    
  }
  
  
  //endscale
  ofPopMatrix();
  
}

//--------------------------------------------------------------
void ofApp::keyPressed( int key ){

  switch( key )
  {
      
    case '-':
      portrait.decrementRes();
      res = portrait.getRes();
      TOP_RES = res;
      
      break;
      
    case '=':
      portrait.incrementRes();
      res = portrait.getRes();
      TOP_RES = res;
      
      break;
      
    case 'f':

      isFullScreen = !isFullScreen;
      ofSetFullscreen( isFullScreen );
//      mosaicFbo.allocate( ofGetWidth(), ofGetHeight() );
      break;
      
    case 'a':
      doAnimate = !doAnimate;
      break;
      
    case ' ':
      if( isCapturing )
      {
        //ofColor(255);
        //ofRect( 0, 0, ofGetWidth(), ofGetHeight() );
        //capture image
        cout << "CAPTURING!" << endl;
        ofImage capture;
        capture.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        capture.saveImage( "captures/frame" + ofToString( numCaptures++ ) + ".png" );
        loadCaptures();
        
      }
      isCapturing = !isCapturing;
      portrait.currentRes = 0;
      res = portrait.getRes();
      isZoomingOut = true;
      break;
      
      case OF_KEY_ESC:
      if( isCapturing ) isCapturing = false;
      break;
      
      case ',':
      isZoomingOut = true;
      ofResetElapsedTimeCounter();
      break;
      
      case '.':
      isZoomingIn = true;
      ofResetElapsedTimeCounter();
      break;
  }
  
  
  
}


void ofApp::loadCaptures()
{
  numCaptures = 0;
  
  ofDirectory captureDirectory( "captures/" );
  captureDirectory.allowExt( "png" );
  captureDirectory.allowExt( "jpg" );
  captureDirectory.listDir();
  vector<ofFile> captureFiles = captureDirectory.getFiles();
  
  cout << "number of files " << captureFiles.size() << endl;
  
  cells.clear();
  
  for( int i = 0; i < captureFiles.size(); i++ )
  {
    ofImage image( captureFiles[i].getAbsolutePath() );
    cells.push_back( cell( image ) );
  }
  
  random_shuffle( cells.begin(), cells.end() );
  
  cout << "number of cells " << cells.size() << endl;
  numCaptures = cells.size();
  if(cells.size() > 0 ) createRandomizedCellIndex();
  
}



void ofApp::createRandomizedCellIndex()
{
  RandomizedCellIndex.clear();
  for( int i = 0; i < MAX_CELLS; i++ )
  {
    RandomizedCellIndex.push_back( i % cells.size() );
  }
  random_shuffle( RandomizedCellIndex.begin(), RandomizedCellIndex.end() );
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
