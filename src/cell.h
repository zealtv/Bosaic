#pragma once
#include "ofMain.h"


class cell
{
  public:
    int posX;
    int posY;
    ofColor color;
    ofImage image;
    float brightness;
    bool isActive;

    void setPos( int posX, int posY );
    void setColor( ofColor color );
    cell( ofImage image );
    //cell( string  fileName );
  
  private:
  
};