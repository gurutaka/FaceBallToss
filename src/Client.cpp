//
//  Client.cpp
//  box2DFaceTrack
//
//  Created by 入田隆 on 2019/04/17.
//

#include "Client.hpp"
#include "ofxOsc.h"
#include "ofMain.h"

//--------------------------------------------------------------
void Client::update(ofxOscMessage message){
    ofxOscMessage m = message;
    touchUp = false;
    
    
    if ( m.getAddress() == "/touchDown/position"){
        clientLines.push_back(ofPolyline());
        pos.x = ofGetWidth() * m.getArgAsFloat(0);
        pos.y = ofGetHeight() * m.getArgAsFloat(1);
        clientLines.back().addVertex(pos);
    }
    
    if ( m.getAddress() == "/touchMoved/position"){
        pos.x = ofGetWidth() * m.getArgAsFloat(0);
        pos.y = ofGetHeight() * m.getArgAsFloat(1);
        clientLines.back().addVertex(pos);
    }
    
    if ( m.getAddress() == "/touchMoved/position"){
        touchUp = m.getArgAsBool(0);
    }
    
}

//--------------------------------------------------------------
void Client::draw(){
    ofNoFill();
    ofSetLineWidth(2.0);
    ofSetColor(ofColor::red);
    
    for (int i=0; i<clientLines.size(); i++) {
        clientLines[i].draw();
    }
}

//--------------------------------------------------------------
void Client::clear(){
    clientLines.clear();
}
