#pragma once
#include "ofMain.h"


class portraitImage : public ofImage
{
  public:
    portraitImage();
    void incrementRes();
    void decrementRes();
    int getRes();
    
  private:
    vector<int> res;
    //int res[11];
    int currentRes;
};