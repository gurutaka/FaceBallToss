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
#include "Client.hpp"


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
    void fallCircleFromIos(ofColor color,float radisu);
    void addInervalCircle();
    void addLineEdges(vector <ofPolyline> lines);
    
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
    
    ofxBox2d box2D;
    int timer;
    int timerLimit;
    int objectLimit;
    
    vector <ofPtr <CustomParticle> > circles;
    vector <ofPtr <ofxBox2dRect> > boxes;
    vector <shared_ptr <ofxBox2dEdge> > edges;
    vector <ofxBox2dEdge> faceEdge;
    
    static bool removeShapeOffScreen(shared_ptr<CustomParticle> shape);
    
};


#endif /* Box2dController_hpp */
