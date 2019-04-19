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

class CustomParticle1 : public ofxBox2dCircle {
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
    void addLineEdges(vector <ofPolyline> lines);
    
    void changeCircleRadius(ofPtr <CustomParticle1> circle, float scaledVol);
    void checkExplosion(ofPtr <CustomParticle1> circle, float smoothedVol);
    
    void fireRightCircle();
    void fireLeftCircle();
    void fireTopCircle();
    void setCircleFireDirection();
    void clear();
    void clearFaceEdge();
    void pushFaceEdgeInstance();
    
    ofxBox2d box2D;
    int timer;
    int timerLimit;
    
    vector <ofPtr <CustomParticle1> > circles;
    vector <ofPtr <ofxBox2dRect> > boxes;

    vector <shared_ptr <ofxBox2dEdge> > edges;
    vector <ofxBox2dEdge> faceEdge;
};


#endif /* Box2dController_hpp */
