#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
//    ofSetFullscreen(true);
    ofSetDataPathRoot("../Resources/data/");
    width = 1920;
    height = 1080;
    
    ofSetWindowShape(width, height);
    grabber.setDeviceID(0);
    grabber.setup(width, height);
    colorImg.allocate(grabber.getWidth() ,grabber.getHeight());
    setMicrophoneSetting();
    
    tracker.setup();
    
    faceDrawFlg = true;
    
    smoothedVol = 0.0;
    scaledVol = 0.0;
    
    sound.load("breath/sound3.mp3");
    soundMax.load("breath/sound5.mp3");
    receiver.setup( PORT );
    box2dController.setup();
    
    backmusicPlay();

}


//--------------------------------------------------------------
void ofApp::update(){
    
//    OSC通信→四角いチリ＠なし
//    updateClient();
    
    scaledVol = ofMap(smoothedVol, 0.02, 0.17, 0.0, 1.0, true);
    grabber.update();
    colorImg.setFromPixels(grabber.getPixels().getData(), grabber.getWidth(), grabber.getHeight());
    colorImg.mirror(false, true);
    
    if(grabber.isFrameNew()){
        tracker.update(colorImg);
    }
    
    box2dController.update();
    box2dController.addInervalCircle();
    
    //顔のラインをreset
    faceLines.clear();
    box2dController.clearFaceEdge();
    setFaceLine();
    playSoundbreath();
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw camera image
    colorImg.draw(0,0, width,height);
    
    // Draw text UI
//    drawTextUI();
    
    ofPushMatrix();
    ofPushStyle();
    
    box2dController.drawFaceLine(faceLines, faceDrawFlg);
    box2dController.draw(scaledVol, smoothedVol);
    
    ofPopStyle();
    ofPopMatrix();
    
}

void ofApp::playSoundbreath(){
    breathSoundTime ++;
    if(!breathFlg && smoothedVol > 0.05){
        breathFlg = true;
        sound.play();
        breathSoundTime = 0;
    }else if(breathFlg && smoothedVol < 0.05 && breathSoundTime > 50){
        breathFlg = false;
    }
    
    if(!breathMaxFlg && smoothedVol > 0.2){
        breathMaxFlg = true;
        soundMax.play();
    }else if(breathMaxFlg && smoothedVol < 0.2){
        breathMaxFlg = false;
    }
    
    
}


//--------------------------------------------------------------
void ofApp::backmusicPlay(){
    backmusic.load("backmusic.mp3");
    backmusic.setLoop(true);
    backmusic.play();
}

//--------------------------------------------------------------
void ofApp::setMicrophoneSetting(){
    ofSoundStreamSettings settings;
    
    ofSoundStreamListDevices();
    
    auto devices = soundStream.getMatchingDevices("default");

    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = 256;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::setFaceLine(){
    if(tracker.size()>0){
        for (int faceNum = 0;faceNum < tracker.size(); faceNum++){
            for(int i = 2; i < 13;i++){
                auto facePoints = tracker.getInstances()[faceNum].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::Feature(i));
                
                faceLines.push_back(ofPolyline());
                box2dController.pushFaceEdgeInstance();

                for(int j=0; j< facePoints.size();j++){
                    faceLines.back().addVertex(facePoints[j].x * width/1280, facePoints[j].y * height/720);
//                    faceLines.back().addVertex(facePoints[j].x, facePoints[j].y );
                }
                
                if(i == 4 || i == 5 || i == 9 || i == 10){
                    faceLines.back().addVertex(facePoints[0].x * width/1280, facePoints[0].y * height/720);
//                    faceLines.back().addVertex(facePoints[0].x, facePoints[0].y );
                }
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::updateClient(){
    
    while( receiver.hasWaitingMessages() ){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/touchDown/position" || m.getAddress() == "/touchMoved/position"){
            ofPoint pos;
            pos.x = ofGetWidth() * m.getArgAsFloat(0);
            pos.y = ofGetHeight() * m.getArgAsFloat(1);
            box2dController.addBox(pos.x,pos.y);
        }

    }

    
}
//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
        
        float left = 0;
        left = input[i]*0.5;//channel only 1
        curVol += pow (left, 2);
        numCounted ++;
    }
    
    
    curVol /= (float)numCounted;//型変換
    curVol = sqrt( curVol );
    smoothedVol *= ofRandom(0.93,0.99);
    smoothedVol += 0.07 * curVol;
    
}

//--------------------------------------------------------------
void ofApp::drawTextUI(){
    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);
    ofDrawBitmapStringHighlight("Reset Key : Space", 10, 60);
    ofDrawBitmapStringHighlight("Face Line Toggle: f", 10, 80);
    ofDrawBitmapStringHighlight("smoothedVol : "+ofToString(smoothedVol), 10, 100);
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,120);
    ofSetColor(ofColor::white);
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'f'){
        faceDrawFlg = !faceDrawFlg;
    }
    
    if(key == 'b'){
        box2dController.addBox(mouseX, mouseY);
    }
    
    if(key == ' '){
        box2dController.clear();
    }
}
