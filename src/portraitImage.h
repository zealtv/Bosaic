#pragma once
#include "ofMain.h"


class portraitImage : public ofImage
{
  public:
    portraitImage();
    void incrementRes();
    void decrementRes();
    int getRes();
    int currentRes;
  
  private:
    vector<int> res;
    //int res[11];

};