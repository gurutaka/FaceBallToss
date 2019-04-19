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
    
    // Clientオブジェクトの更新
    if ( m.getAddress() == "/mouse/position"){
        pos.x = ofGetWidth() * m.getArgAsFloat(0);
        pos.y = ofGetHeight() * m.getArgAsFloat(1);
    }
}

//--------------------------------------------------------------
void Client::draw(){
    ofCircle(pos.x, pos.y, 30);
}
