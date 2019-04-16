#include "ofApp.h"

//--------------------------------------------------------------

static bool removeShapeOffScreen(shared_ptr<CustomParticle> shape) {
    if (!ofRectangle(-30, -400, ofGetWidth()+100, ofGetHeight()+400).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // Setup grabber
    width = 1280;
    height = 720;
    
    ofSetWindowShape(width, height);
    grabber.setup(width,height);
    colorImg.allocate(width,height);

    tracker.setup();
    
    box2D.init();
    box2D.setGravity(0, 5);
    box2D.createBounds();//周囲に壁を設置
//    box2D.createGround();
    box2D.setFPS(30.0);
    box2D.registerGrabbing();
    
    timerLimit = 7.5;
    timer = 0;
    faceDrawFlg = true;
    limitBottomHeight = 50;
    
    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    
    int bufferSize = 256;
    smoothedVol = 0.0;
    scaledVol = 0.0;
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    scaledVol = ofMap(smoothedVol, 0.02, 0.17, 0.0, 1.0, true);
    grabber.update();
    colorImg.setFromPixels(grabber.getPixels().getData(), width, height);
    colorImg.mirror(false, true);
    
    if(grabber.isFrameNew()){
        tracker.update(colorImg);
    }
    
    ofRemove(circles, removeShapeOffScreen);
    box2D.update();
    
    
    
    timer ++;
    if(timer > timerLimit){
        addCircle();
        setCircleFireDirection();
        timer = 0;
    }
    
    //顔のラインをreset
    faceLines.clear();
    faceEdge.clear();
    
    if(tracker.size()>0){
        
        for (int faceNum = 0;faceNum < tracker.size(); faceNum++){
            
            //futureのkength-1分
            auto facePoints = tracker.getInstances()[faceNum].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::ALL_FEATURES);
            
            //顔が出ないライン
//            if(facePoints[7].y > height - limitBottomHeight){
//                continue;
//            }
            
//            ofxFaceTracker2Landmarks::Feature(0);
            //なぜ値が出てこないのか？
//            std::cout << "value: " << static_cast <ofxFaceTracker2Landmarks::Feature>(0) << endl;
            
//            std::cout << "value: " << ofxFaceTracker2Landmarks::Feature(0) << endl;
            
            //            auto facePatterns = tracker.getInstances()[faceNum].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::Feature);
            
            
            for(int i = 0; i < 68; i++){
                if(i == 0 || i == 17 || i == 22 || i==27  || i== 31  || i== 36  || i == 42  || i == 48  || i== 60){
                    faceLines.push_back(ofPolyline());
                    faceEdge.push_back(ofxBox2dEdge());
                }
                
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
                faceLines.back().addVertex(facePoints[i].x, facePoints[i].y);
                
                switch (i) {
                    case 41:
                        faceLines.back().addVertex(facePoints[36].x, facePoints[36].y);
                        break;
                    case 47:
                        faceLines.back().addVertex(facePoints[42].x, facePoints[42].y);
                        break;
                    case 59:
                        faceLines.back().addVertex(facePoints[48].x, facePoints[48].y);
                        break;
                    case 67:
                        faceLines.back().addVertex(facePoints[60].x, facePoints[60].y);
                        break;
                }
                
            }
            
//            //顔
//            faceLines.push_back(ofPolyline());
//            for (int i = 0; i < 17; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//            }
//
//            //左眉
//            faceLines.push_back(ofPolyline());
//            for (int i = 17; i < 22; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//            }
//
//            //右眉
//            faceLines.push_back(ofPolyline());
//            for (int i = 22; i < 27; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//            }
//
//            //鼻筋
//            faceLines.push_back(ofPolyline());
//            for (int i = 27; i < 31; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//            }
//
//            //鼻
//            faceLines.push_back(ofPolyline());
//            for (int i = 31; i < 36; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//            }
//
//            //左目
//            faceLines.push_back(ofPolyline());
//            for (int i = 36; i < 42; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//
//                if(i == 41){
//                    faceLines.back().addVertex(getInvertedYaxis(facePoints[36].x), facePoints[36].y);
//                }
//            }
//
//            //右目
//            faceLines.push_back(ofPolyline());
//            for (int i = 42; i < 48; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//
//                if(i == 47){
//                    faceLines.back().addVertex(getInvertedYaxis(facePoints[42].x), facePoints[42].y);
//                }
//            }
//
//            //外口枠
//            faceLines.push_back(ofPolyline());
//            for (int i = 48; i < 60; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//
//                if(i == 59){
//                    faceLines.back().addVertex(getInvertedYaxis(facePoints[48].x), facePoints[48].y);
//                }
//            }
//
//            //内口枠
//            faceLines.push_back(ofPolyline());
//            for (int i = 60; i < 68; i++) {
//                faceLines.back().addVertex(getInvertedYaxis(facePoints[i].x), facePoints[i].y);
//                if(i == 67){
//                    faceLines.back().addVertex(getInvertedYaxis(facePoints[60].x), facePoints[60].y);
//                }
//            }
        
        }
        
    }
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw camera image
    colorImg.draw(0,0, width,height);
    
    // 顔のラインが消える領域
//    setFieldFadeFaceLine();
    
    // Draw text UI
    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);
    ofDrawBitmapStringHighlight("Reset Key : Space", 10, 60);
    ofDrawBitmapStringHighlight("Face Line Toggle: f", 10, 80);
    ofDrawBitmapStringHighlight("smoothedVol : "+ofToString(smoothedVol), 10, 120);
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,100);
    ofSetColor(ofColor::white);
#endif
    
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    ofSetLineWidth(1.0);
    
    
    for(int i = 0; i<circles.size();i++){
        circles[i].get()->volRadius = scaledVol * 100;
        if(smoothedVol > 0.05){
            circles[i].get()->addForce(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)).normalize(), 10000);
        }
        circles[i].get()->draw();
    }
    
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

    for(int i = 0; i<boxes.size();i++){
        ofSetHexColor(0xBF2545);
        boxes[i].get()->draw();
    }
    
    ofNoFill();
    ofSetLineWidth(2.0);
    ofSetColor(ofColor::white);
    for (int i=0; i<lines.size(); i++) {
        lines[i].draw();
    }
    
    ofPopStyle();
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::addCircle(){
    circles.push_back(std::make_shared<CustomParticle>());
    circles.back().get()->setPhysics(3.0 * 10, 0.53 / 3, 0.1 * 10);
    circles.back().get()->color.r = ofRandom(255);
    circles.back().get()->color.g = ofRandom(255);
    circles.back().get()->color.b = ofRandom(255);
    circles.back().get()->volRadius = 0.0;
}

void ofApp::fireRightCircle(){
    circles.back().get()->setup(box2D.getWorld(), width+5, height/2 , ofRandom(12,18));
    circles.back().get()->addForce(ofVec2f(ofRandom(-30,-50),ofRandom(-30,-50)), ofRandom(100,150));
}

void ofApp::fireLeftCircle(){
    circles.back().get()->setup(box2D.getWorld(), -5, height/2 , ofRandom(12,18));
    circles.back().get()->addForce(ofVec2f(ofRandom(30,50),ofRandom(-30,-50)), ofRandom(100,150));
}

void ofApp::fireTopCircle(){
    circles.back().get()->setup(box2D.getWorld(), ofRandom(0, width), 0, ofRandom(10,20));
}

void ofApp::setCircleFireDirection(){
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
void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
//        left[i]        = input[i*2]*0.5;
//        right[i]    = input[i*2+1]*0.5;
//
//        curVol += left[i] * left[i];
//        curVol += right[i] * right[i];
        curVol += pow (input[i*2]*0.5, 2) + pow (input[i*2 + 1]*0.5, 2) ;
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;//型変換
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= ofRandom(0.93,0.99);
    smoothedVol += 0.07 * curVol;
//
//    bufferCounter++;
    
}
//--------------------------------------------------------------
void ofApp::setFieldFadeFaceLine(){
    ofPushStyle();
    ofFill();
    ofSetColor(50,50,50,200);
    ofRect(0, height - limitBottomHeight, width, height);
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c'){
        addCircle();
        circles.back().get()->setup(box2D.getWorld(), mouseX, mouseY, ofRandom(4,20));
    }
    
    if(key == 'b'){
        float w = ofRandom(4,20);
        float h = ofRandom(4, 20);
        boxes.push_back(std::make_shared<ofxBox2dRect>());
        boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
        boxes.back().get()->setup(box2D.getWorld(), mouseX, mouseY, w, h);
    }
    
    if(key == 'f'){
        faceDrawFlg = !faceDrawFlg;
    }
    
    if(key == ' '){
        circles.clear();
        boxes.clear();
        lines.clear();
        edges.clear();
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    lines.back().addVertex(x,y);//最後の要素に頂点を追加
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    lines.push_back(ofPolyline());//プッシュ
//    lines.back().addVertex(x,y);//最後の要素に頂点を追加
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    shared_ptr<ofxBox2dEdge> edge = std::make_shared<ofxBox2dEdge>();
//    lines.back().simplify();
//
//    for(int i=0; i<lines.back().size(); i ++){
//        edge.get() -> addVertex(lines.back()[i]);
//    }
//
//    edge.get()->create(box2D.getWorld());
//    edges.push_back(edge);
}
