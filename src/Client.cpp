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
    
    // Clientオブジェクトの更新
    if ( m.getAddress() == "/touch/position"){

//        if(m.getArgAsString(0) == "Down"){
//            lines.push_back(ofPolyline());
//            std::cout << "down!" << endl;
//        }
//        pos.x = ofGetWidth() * m.getArgAsFloat(0);
//        pos.y = ofGetHeight() * m.getArgAsFloat(1);
//        lines.back().addVertex(pos.x,pos.y);

//        if(m.getArgAsString(0) == "Up"){
//            touchUp = true;
//        }else{
//            pos.x = ofGetWidth() * m.getArgAsFloat(0);
//            pos.y = ofGetHeight() * m.getArgAsFloat(1);
//            lines.back().addVertex(pos);
//        }
    }
    
        if ( m.getAddress() == "/touch/position"){
                pos.x = ofGetWidth() * m.getArgAsFloat(0);
                pos.y = ofGetHeight() * m.getArgAsFloat(1);
        }
    
}

//--------------------------------------------------------------
void Client::draw(){
    ofCircle(pos.x, pos.y, 30);
    
    for (int i=0; i<lines.size(); i++) {
        lines[i].draw();
    }
}

//--------------------------------------------------------------
void Client::clear(){
    lines.clear();
}
