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
//    touchUp = false;
    
    if ( m.getAddress() == "/touch/position"){
//        clientLines.push_back(ofPolyline());
        pos.x = ofGetWidth() * m.getArgAsFloat(0);
        pos.y = ofGetHeight() * m.getArgAsFloat(1);
//        clientLines.back().addVertex(pos);
    }
    
//    if ( m.getAddress() == "/touchMoved/position"){
//        pos.x = ofGetWidth() * m.getArgAsFloat(0);
//        pos.y = ofGetHeight() * m.getArgAsFloat(1);
//        clientLines.back().addVertex(pos);
//    }
//
//    if ( m.getAddress() == "/deleteCircle/info"){
//        color.r = m.getArgAsFloat(0);
//        color.g = m.getArgAsFloat(1);
//        color.b = m.getArgAsFloat(2);
//        radius = m.getArgAsFloat(3);
//    }
    
}
