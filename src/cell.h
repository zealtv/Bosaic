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

    cell( int _posX, int _posY );
  
  private:
  
};