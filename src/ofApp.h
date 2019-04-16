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

// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
    
public:

    ofColor color;
    float volRadius;
    void draw() {
        float radius = getRadius() + volRadius;
        
        glPushMatrix();
        glTranslatef(getPosition().x, getPosition().y, 0);
        
        ofSetColor(color.r, color.g, color.b);
        ofFill();
        ofDrawCircle(0, 0, radius);
        
        glPopMatrix();
    }
};

// -------------------------------------------------
#define BUFSIZE 512

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void addCircle();
    void fireRightCircle();
    void fireLeftCircle();
    void fireTopCircle();
    void setCircleFireDirection();
    void setFieldFadeFaceLine();
    
    int getInvertedYaxis(int x);
    int width;
    int height;
    bool faceDrawFlg;

    
    ofxFaceTracker2 tracker;
    ofVideoGrabber grabber;
    ofxCvColorImage colorImg;
    ofxBox2d box2D;
    int timer;
    int timerLimit;
    int limitBottomHeight;
    
    vector <ofPtr <CustomParticle> > circles;
    vector <ofPtr <ofxBox2dRect> > boxes;
    vector <shared_ptr <ofxBox2dEdge> > edges;
    vector <ofxBox2dEdge> faceEdge;
    
    vector <ofPolyline> lines;//線の配列
    vector <ofPolyline> faceLines;
    
    ofSoundStream soundStream;
    float smoothedVol;
    float scaledVol;
    void audioIn(ofSoundBuffer & input);
    
};
