//
//  Box2dController.cpp
//  box2DFaceTrack
//
//  Created by 入田隆 on 2019/04/18.
//

#include "Box2dController.hpp"
#include "ofxBox2d.h"
#include "ofMain.h"

//--------------------------------------------------------------
void Box2dController::setup(){
    box2D.init();
    box2D.setGravity(0, 5);
    box2D.createBounds();//周囲に壁を設置
//    box2D.createGround();
    box2D.setFPS(30.0);
//    box2D.registerGrabbing();
    timer = 0;
    timerLimit = 7;
}

//--------------------------------------------------------------
void Box2dController::update(){
    box2D.update();
//    ofRemove(circles, removeShapeOffScreen);画面外のモノを削除
}

//--------------------------------------------------------------
void Box2dController::draw(float scaledVol, float smoothedVol){
    drawBox();
    drawCircle(scaledVol, smoothedVol);
}

//--------------------------------------------------------------
void Box2dController::clear(){
    circles.clear();
    boxes.clear();
    edges.clear();
    faceEdge.clear();
}

//--------------------------------------------------------------
void Box2dController::clearFaceEdge(){
    faceEdge.clear();
}

//--------------------------------------------------------------
void Box2dController::pushFaceEdgeInstance(){
    faceEdge.push_back(ofxBox2dEdge());
}

//--------------------------------------------------------------
void Box2dController::drawBox(){
    for(int i = 0; i<boxes.size();i++){
        ofSetHexColor(0xBF2545);
        boxes[i].get()->draw();
    }
}
//--------------------------------------------------------------
void Box2dController::drawCircle(float scaledVol, float smoothedVol){
    for(int i = 0; i<circles.size();i++){
        changeCircleRadius(circles[i], scaledVol);
        checkExplosion(circles[i], smoothedVol);;
        circles[i].get()->draw();
    }
}

//--------------------------------------------------------------
void Box2dController::drawFaceLine(vector <ofPolyline> faceLines,bool faceDrawFlg){
    ofFill();
    ofSetLineWidth(1.0);
    ofSetColor(31, 127, 255);
    if(faceLines.size() > 0){
        for (int i =0 ; i < faceLines.size(); i++){
            faceLines[i].simplify();
            faceEdge[i].destroy();
            for(int j=0; j<faceLines[i].size(); j ++){
                faceEdge[i].addVertex(faceLines[i][j]);
            }
            faceEdge[i].create(box2D.getWorld());
            
            if(faceDrawFlg){
                faceEdge[i].draw();
            }
            faceLines[i].clear();
        }
    }
}


//--------------------------------------------------------------
void Box2dController::addLineEdges(vector <ofPolyline> lines){
    shared_ptr<ofxBox2dEdge> edge = std::make_shared<ofxBox2dEdge>();
    lines.back().simplify();
    
    for(int i=0; i<lines.back().size(); i ++){
        edge.get() -> addVertex(lines.back()[i]);
    }
    
    edge.get()->create(box2D.getWorld());
    edges.push_back(edge);
}

//--------------------------------------------------------------
void Box2dController::changeCircleRadius(ofPtr <CustomParticle> circle, float scaledVol){
    circle.get()->volRadius = scaledVol * 100;
}

//--------------------------------------------------------------
void Box2dController::checkExplosion(ofPtr <CustomParticle> circle, float smoothedVol){
    if(smoothedVol > 0.05){
        circle.get()->addForce(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)).normalize(), 20000);
    };
}

//--------------------------------------------------------------
void Box2dController::addBox(int mouseX, int mouseY){
    float w = ofRandom(4,20);
    float h = ofRandom(4, 20);
    boxes.push_back(std::make_shared<ofxBox2dRect>());
    boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
    boxes.back().get()->setup(box2D.getWorld(), mouseX, mouseY, w, h);
}
//--------------------------------------------------------------
void Box2dController::addInervalCircle(){
    timer ++;
    if(timer > timerLimit){
        addCircle();
        timer = 0;
    }
}
//--------------------------------------------------------------
void Box2dController::addCircle(){
    circles.push_back(std::make_shared<CustomParticle>());
    circles.back().get()->setPhysics(3.0 * 10, 0.53 / 3, 0.1 * 10);
    circles.back().get()->color.r = ofRandom(255);
    circles.back().get()->color.g = ofRandom(255);
    circles.back().get()->color.b = ofRandom(255);
    circles.back().get()->volRadius = 0.0;
    setCircleFireDirection();
}

//--------------------------------------------------------------
void Box2dController::fallCircleFromIos(ofColor color,float radisu){
    circles.push_back(std::make_shared<CustomParticle>());
    circles.back().get()->setPhysics(3.0 * 10, 0.53 / 3, 0.1 * 10);
    circles.back().get()->color = color;
    circles.back().get()->volRadius = 0.0;
    circles.back().get()->setup(box2D.getWorld(), ofRandom(0, ofGetWidth()), -300, radisu);
//    circles.back().get()->addForce(ofVec2f(0,ofRandom(-30,30)), ofRandom(100,150));
}
//--------------------------------------------------------------
void Box2dController::fireRightCircle(){
    circles.back().get()->setup(box2D.getWorld(), ofGetWidth()-50, ofGetHeight()/2 , ofRandom(12,18));
    circles.back().get()->addForce(ofVec2f(ofRandom(-30,-50),ofRandom(-30,-50)), ofRandom(100,150));
}
//--------------------------------------------------------------
void Box2dController::fireLeftCircle(){
    circles.back().get()->setup(box2D.getWorld(), 50, ofGetHeight()/2 , ofRandom(12,18));
    circles.back().get()->addForce(ofVec2f(ofRandom(30,50),ofRandom(-30,-50)), ofRandom(100,150));
}
//--------------------------------------------------------------
void Box2dController::fireTopCircle(){
    circles.back().get()->setup(box2D.getWorld(), ofRandom(0, ofGetWidth()), 0, ofRandom(10,20));
}
//--------------------------------------------------------------
void Box2dController::setCircleFireDirection(){
    int randomNum =  floor(ofRandom(0,3));
    
    switch (randomNum) {
        case 0:
            fireRightCircle();
            break;
        case 1:
            fireLeftCircle();
            break;
        default:
            fireTopCircle();
            break;
    }
}

//--------------------------------------------------------------

//bool Box2dController::removeShapeOffScreen(shared_ptr<CustomParticle> shape) {
//    if (!ofRectangle(-30, -400, ofGetWidth()+100, ofGetHeight()+400).inside(shape.get()->getPosition())) {
//        return true;
//    }
//    return false;
//}
