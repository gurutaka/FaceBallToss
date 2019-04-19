//
//  Client.hpp
//  box2DFaceTrack
//
//  Created by 入田隆 on 2019/04/17.
//

#ifndef Client_hpp
#define Client_hpp
#include "ofxOsc.h"

class Client {
public:
    void update(ofxOscMessage message);
    void draw();
    ofPoint pos;
};

#endif /* Client_hpp */
