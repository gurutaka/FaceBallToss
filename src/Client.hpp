//
//  Client.hpp
//  box2DFaceTrack
//
//  Created by 入田隆 on 2019/04/17.
//

#ifndef Client_hpp
#define Client_hpp
#include "ofxOsc.h"
#include "ofMain.h"

class Client {
public:
    void update(ofxOscMessage message);
    void draw();
    void clear();
    ofPoint pos;
    bool touchUp = false;
    vector <ofPolyline> lines;//線の配列
};

#endif /* Client_hpp */
