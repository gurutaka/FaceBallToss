//
//  Box2dController.hpp
//  box2DFaceTrack
//
//  Created by 入田隆 on 2019/04/18.
//

#ifndef Box2dController_hpp
#define Box2dController_hpp

#include "ofxBox2d.h"
#include "ofMain.h"


class SoundData {
public:
    int  soundID;
    bool bHit;
};



class CustomParticle : public ofxBox2dCircle {
public:
    ofColor color;
    ofImage texture;
    ofSoundPlayer sound;
    bool stopSounded;
    float volRadius;
    void init(){
        setPhysics(3.0 * 10, 0.53 / 3, 0.1 * 10);
        volRadius = 0.0;
        texture.setAnchorPercent(0.5, 0.5);
        float circRadA = 100.0;
    }
//    void draw() {
//        float radius = getRadius() + volRadius;
//        glPushMatrix();
//        glTranslatef(getPosition().x, getPosition().y, 0);
//        ofSetColor(color.r, color.g, color.b);
//        ofFill();
//        ofDrawCircle(0, 0, radius);
//        glPopMatrix();
//    }
    
    
    void drawTexture() {

        float radius = ( getRadius() + volRadius ) * 2;
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(getPosition());
        ofRotateDeg(getRotation());
        ofSetColor(255, 255, 255);
        texture.draw(0,0, radius, radius);
        ofPopStyle();
        ofPopMatrix();
    }
};

class Box2dController {
public:
    void setup();
    void update();
    void draw(float scaledVol, float smoothedVol);
    void drawBox();
    void drawCircle(float scaledVol, float smoothedVol);
    void drawFaceLine(vector <ofPolyline> faceLines, bool faceDrawFlg);
    void addBox(int mouseX, int mouseY);
    void addCircle();
    void addInervalCircle();
    
    void changeCircleRadius(ofPtr <CustomParticle> circle, float scaledVol);
    void checkExplosion(ofPtr <CustomParticle> circle, float smoothedVol);
    
    void fireRightCircle();
    void fireLeftCircle();
    void fireTopCircle();
    void setCircleFireDirection();
    void clear();
    void clearFaceEdge();
    void pushFaceEdgeInstance();
    void setBox2dBound();
    void initTexture();
    
    ofxBox2d box2D;
    int timer;
    int timerLimit;
    int objectLimit;
//    void contactStart(ofxBox2dContactArgs &e);
    
    vector <ofPtr <CustomParticle> > circles;
    vector <ofPtr <ofxBox2dRect> > boxes;
    vector <ofxBox2dEdge> faceEdge;
    vector <ofImage> textures;
    vector <ofSoundPlayer> sounds;
    
    static bool removeShapeOffScreen(shared_ptr<CustomParticle> shape);
    static bool removeBox2dRectOffScreen(shared_ptr<ofxBox2dRect> shape);
    
};


#endif /* Box2dController_hpp */
