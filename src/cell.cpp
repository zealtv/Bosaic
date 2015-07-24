#include "cell.h"

void cell::setPos( int posX, int posY )
{
  this->posX = posX;
  this->posY = posY;
  

}

cell::cell( ofImage image )
{
  this->image = image;
  isActive = true;
}

void cell::setColor( ofColor color )
{
  this->color = color;
  this->brightness = color.getBrightness();
}

/*
cell::cell( string fileName )
{
  
}
*/