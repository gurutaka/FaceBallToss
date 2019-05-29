// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "Box2dController.hpp"
#include "ofxOsc.h"
#define PORT 8888

// -------------------------------------------------

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void drawTextUI();
    void drawEdgeLine();
    void setFaceLine();
    void setMicrophoneSetting();
    
    int getInvertedYaxis(int x);
    int width;
    int height;
    bool faceDrawFlg;
    bool breathFlg;
    bool breathMaxFlg;
    
    ofxFaceTracker2 tracker;
    ofVideoGrabber grabber;
    ofxCvColorImage colorImg;

    vector <ofPolyline> faceLines;
    
    ofSoundStream soundStream;
    float smoothedVol;
    float scaledVol;
    void audioIn(ofSoundBuffer & input);
    
    void updateClient();
    void playSoundbreath();
    ofxOscReceiver  receiver;
    Box2dController box2dController;
    ofSoundPlayer sound;
    ofSoundPlayer soundMax;
    ofSoundPlayer backmusic;
    
    void backmusicPlay();
    int breathSoundTime = 0;
};
