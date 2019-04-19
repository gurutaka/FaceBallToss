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
#include "Client.hpp"
#include "Box2dController.hpp"
#define PORT 8888

// -------------------------------------------------

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void drawTextUI();
    void drawEdgeLine();
    void setFaceLine();
    void setMicrophoneSetting();
    
    int getInvertedYaxis(int x);
    int width;
    int height;
    bool faceDrawFlg;

    
    ofxFaceTracker2 tracker;
    ofVideoGrabber grabber;
    ofxCvColorImage colorImg;

    vector <ofPolyline> lines;//線の配列
    vector <ofPolyline> faceLines;
    
    ofSoundStream soundStream;
    float smoothedVol;
    float scaledVol;
    void audioIn(ofSoundBuffer & input);
    
    void updateClient();
    ofxOscReceiver  receiver;
    Client client;
    Box2dController box2dController;
    
};
