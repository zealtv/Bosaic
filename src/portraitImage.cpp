#include "portraitImage.h"

portraitImage::portraitImage()
{
  //60, 30, 20, 15, 10, 6, 5, 4, 3, 2, 1
  res.push_back( 1 );
  res.push_back( 2 );
  res.push_back( 3 );
  res.push_back( 4 );
  res.push_back( 5 );
  res.push_back( 6 );
  res.push_back( 10 );
  res.push_back( 15 );
  res.push_back( 20 );
  res.push_back( 30 );
 // res.push_back( 60 );
  
  currentRes = 9;
}


void portraitImage::incrementRes()
{
  if( ++currentRes >= res.size() ) currentRes = res.size() - 1;
}


void portraitImage::decrementRes()
{
    if( --currentRes < 0 ) currentRes = 0;
}


int portraitImage::getRes()
{
  return res[ currentRes ];
}



