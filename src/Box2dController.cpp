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
    box2D.enableEvents();
    box2D.setGravity(0, 5);
    box2D.createBounds();
    box2D.setFPS(30.0);
    timer = 0;
    timerLimit = 10;
    objectLimit = 400;
    initTexture();
    ofAddListener(box2D.contactStartEvents, this, &Box2dController::contactStart);
    
    ofDirectory dir;//data直下
    int n = dir.listDir("sounds");
    for (int i=0; i<n; i++) {
        ofSoundPlayer sound;
        sound.load(dir.getPath(i));
        sounds.push_back(sound);
    }
}

//--------------------------------------------------------------
void Box2dController::initTexture(){
    ofDirectory dir;//data直下
    ofDisableArbTex();//テクスチャの型
    int n = dir.listDir("textures");
    for (int i=0; i<n; i++) {
        textures.push_back(ofImage(dir.getPath(i)));
    }
}

//--------------------------------------------------------------
void Box2dController::contactStart(ofxBox2dContactArgs &e) {
    

    if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
        
//        CustomParticle * aData = (CustomParticle*)e.a->GetBody()->GetUserData();
        
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//        std::cout << "value: " << aData << endl;
    }
}

//--------------------------------------------------------------
void Box2dController::update(){
    box2D.update();
    setBox2dBound();
    ofRemove(circles, removeShapeOffScreen);
    ofRemove(boxes, removeBox2dRectOffScreen);
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
        checkExplosion(circles[i], smoothedVol);
        circles[i].get()->drawTexture();
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
//            faceEdge[i].addVertexes(faceLines[i]);
            faceEdge[i].create(box2D.getWorld());
            
            if(faceDrawFlg){
                faceEdge[i].draw();
            }
            faceLines[i].clear();
        }
    }
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
//    sounds[(int)ofRandom(sounds.size())].play();
    circles.push_back(std::make_shared<CustomParticle>());
    circles.back().get()->texture = textures[(int)ofRandom(textures.size())];
    circles.back().get()->init();
    setCircleFireDirection();
    
//    ★setDataに入れる意味
    
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

void Box2dController::setBox2dBound(){
    if(circles.size() + boxes.size() > objectLimit){
        box2D.createBounds(0, 0, 0, 0);
        box2D.checkBounds(false);
    }else{
        box2D.createBounds();
        box2D.checkBounds(true);
    }
}

//--------------------------------------------------------------

bool Box2dController::removeShapeOffScreen(shared_ptr<CustomParticle> shape) {
    if (!ofRectangle(-150, -150, ofGetWidth()+300, ofGetHeight()+300).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------

bool Box2dController::removeBox2dRectOffScreen(shared_ptr<ofxBox2dRect> shape) {
    if (!ofRectangle(-150, -150, ofGetWidth()+300, ofGetHeight()+300).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}
