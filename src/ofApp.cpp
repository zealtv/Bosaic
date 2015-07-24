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
  
  grabber.setDeviceID( 1 );
  grabber.setDesiredFrameRate( 60 );
  grabber.initGrabber( camWidth, camHeight );
  grabber.setAnchorPoint( camWidth/2, camHeight/2 );
  
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
  grabber.update();
  
  if( isZoomingIn )
  {
    
    if(  ofGetElapsedTimeMillis() > 70 )
    {
      portrait.decrementRes();
      res = portrait.getRes();
      ofResetElapsedTimeCounter();
      cellOffset = (int) ofRandom( 40 );
    }
    if( portrait.getRes() == 1 )
    {
      singleColor = portrait.getColor( ofRandom( portrait.getWidth() ), ofRandom( portrait.getHeight()/2 + portrait.getHeight()/4 ) );
      isZoomingIn = false;
    }
  }

  if( isZoomingOut )
  {
    if(  ofGetElapsedTimeMillis() > 70 )
    {
      portrait.incrementRes();
      res = portrait.getRes();
      ofResetElapsedTimeCounter();
      cellOffset = (int) ofRandom( 40 );
    }
    if( portrait.getRes() == 30 ) isZoomingOut = false;
  }
  
  
  
  if( ofGetElapsedTimeMillis() > toggleTime )
  {
    cout<< "Bang!" << endl;
    if( portrait.getRes() == 30 )
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

  
  if( !isCapturing )
  {
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    
    int ix = 0;
    int iy = 0;
    
    for( iy = 0; iy < res; iy++ )
    {
      for( ix = 0; ix < res; ix++ )
      {
        
        
        
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
    c.setBrightness( 70 );
    ofSetColor( c );
    if(res == 30 ) portrait.draw( 0.0, 0.0, ofGetWidth(), ofGetHeight() );
  }
  else //is capturing
  {

    
    //TODO check if image is to be rotated before applying these transformations
    ofPushMatrix();
    ofScale( 9.0/16.0, 9.0/16.0 );
    ofRotate( camRotate );
    ofTranslate( camWidth/2, -camHeight/2);

    ofSetColor( 255 );

    grabber.draw( 0.0, 0.0, camWidth, camHeight );
    ofPopMatrix();
    
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
