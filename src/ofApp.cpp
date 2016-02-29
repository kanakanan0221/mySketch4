#include "ofApp.h"

static bool shouldRemove(shared_ptr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
}
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofDisableAntiAliasing();
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);
    
    // Box2d
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(30.0);
    
    //    breakupIntoTriangles = true;
    
    // load the shape we saved...
    vector <ofPoint> pts = loadPoints("shape.dat");
    shared_ptr<ofxBox2dPolygon> poly = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    poly->addVertices(pts);
    poly->setPhysics(1.0, 0.3, 0.3);
    poly->triangulatePoly();
    poly->create(box2d.getWorld());
    polyShapes.push_back(poly);

    
    
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    img.loadImage("名称未設定 5.png");
    //    p.setIntialCondition(ofGetWidth()/2, ofGetHeight()/2, ofRandom(-10,10), ofRandom(-10,10));
    //
    cam.setOrientation(ofPoint(-20,0,0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leap.open();
    
    //    manbo.loadImage("manbo.gif");
    
    
}

//--------------------------------------------------------------
vector <ofPoint> ofApp::loadPoints(string file) {
    vector <ofPoint> pts;
    vector <string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (int i=0; i<ptsStr.size(); i+=2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}



//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i<particles.size(); i++){
        particles[i].resetForce();
        //        particles[i].addForce(0, 0.1);
        particles[i].addDampingFoece();
        particles[i].update();
    }
    
    if((int)ofRandom(0, 10) == 0) {
        shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
        circle->setPhysics(0.3, 0.5, 0.1);
        circle->setup(box2d.getWorld(), (ofGetWidth()/2)+ofRandom(-20, 20), -20, ofRandom(10, 20));
        
    }

    box2d.update();

//    
//    simpleHands = leap.getSimpleHands();
//    if (leap.isFrameNew() && simpleHands.size() ) {
//        fingerPos.clear();
//        
//        handPos.clear();
//        
//        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
//        leap.setMappingY(90, 490, -ofGetHeight()/2
//                         , ofGetHeight()/2);
//        leap.setMappingZ(-150,150,-200,200);
//        
//        fingerType fingerTypes[] = {THUMB, INDEX,MIDDLE,RING,PINKY};
//        
//        for (int i = 0; i < simpleHands.size(); i++) {
//            
//            handPos.push_back(simpleHands[i].handPos);
//            
//            for (int f = 0; f<5 ; f++ ) {
//                
//                
//                
//                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
//                fingerPos.push_back(mcp);
//                
//                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;
//                fingerPos.push_back(pip);
//                
//                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;
//                fingerPos.push_back(dip);
//                
//                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;
//                fingerPos.push_back(tip);
//                
//            }
//            
//        }
    
//    }
    leap.markFrameAsOld();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255, 255, 255);
    
    string message = "current particle num = "+ ofToString(particles.size(),0);
    ofDrawBitmapString(message, 20,20);
    
    for(int i = 0; i < particles.size(); i++){
        float posx = particles[i].pos.x - 16;
        float posy = particles[i].pos.y - 16;
        img.draw(posx,posy);
        
        
    }
    
    ofSetColor(180,15,173);	ofFill();
    shape.draw();
    
    ofSetColor(180,15,173);
    ofNoFill();
    for (int i=0; i<polyShapes.size(); i++) {
        polyShapes[i]->draw();
        
        ofCircle(polyShapes[i]->getPosition(), 3);
    }	
    

    
//    if(fingerPos.size() !=0 ){
//        
//        Particle myParticle;
//        float vx = ofRandom(-10,10);
//        float vy = ofRandom(-10,10);
//        
//        
//        //    myParticle.setIntialCondition(x, y, vx, vy);
//        myParticle.setIntialCondition(fingerPos.at(10).x,fingerPos.at(10).y, vx, vy);
//        cout << " x : " << fingerPos.at(10).x << endl;
//        cout << " y : " <<  fingerPos.at(10).y<< endl;
//        
//        
//        particles.push_back(myParticle);
//        
//    }
//    
    //       ofBackground(0, 0,0);
    
    //       ofBackground(0);
        cam.begin();
    //
    //    Particle myParticle;
    //    float vx = ofRandom(-1,1);
    //    float vy = ofRandom(-1,1);
    ////    ( fingerPos.at(7)  , img.getWidth(), img.getHeight());
    //    particles.push_back(myParticle);
    //
    //
    
    
    
    
    
    
    
    //    manbo.draw(mouseX, mouseY, manbo.getWidth(), manbo.getHeight());
    
//    for (int i = 0; i <simpleHands.size(); i++) {
//        for (int f =0; f<5; f++) {
//            
//            //            manbo.draw(ofPoint( fingerPos.at(7) ) , manbo.getWidth(), manbo.getHeight());
//            
//            
//            ofSetColor(0, 255, 0);
//            ofDrawSphere(handPos.at(i), 20);
//            
//            
//            ofSetColor(255);
//            ofDrawSphere(fingerPos.at(20*i+4*f+0),10);
//            cout << " ‰∏≠ÂøÉ„Åã„Çâ0 : " << fingerPos.at(20*i+4*f+0) << endl;
//            
//            
//            ofSetColor(200);
//            ofDrawSphere(fingerPos.at(20*i+4*f+1),10);
//            cout << " ‰∏≠ÂøÉ„Åã„Çâ1 : " << fingerPos.at(20*i+4*f+1) << endl;
//            
//            
//            ofSetColor(155);
//            ofDrawSphere(fingerPos.at(20*i+4*f+2),10);
//            cout << " ‰∏≠ÂøÉ„Åã„Çâ2 : " << fingerPos.at(20*i+4*f+2) << endl;
//            
//            
//            ofSetColor(100);
//            ofDrawSphere(fingerPos.at(20*i+4*f+3),10);
//            
//            ofLine(fingerPos.at(20*i+4*f+0), fingerPos.at(20*i+4*f+1));
//            ofLine(fingerPos.at(20*i+4*f+1), fingerPos.at(20*i+4*f+2));
//            ofLine(fingerPos.at(20*i+4*f+2), fingerPos.at(20*i+4*f+3));
//        }
//    }
    cam.end();
}

void ofApp::exit(){
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key =='c') {
        shape.clear();
        polyShapes.clear();
        particles.clear();
    }
    if (key =='f') {
        ofToggleFullscreen();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
        Particle myParticle;
        float vx = ofRandom(-1,1);
            float vy = ofRandom(-1,1);
         myParticle.setIntialCondition(x, y, vx, vy);
         particles.push_back(myParticle);
    shape.addVertex(x, y);

    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //    particles.clear();
    //    for(int i = 0; i<NUM; i++){
    //        Particle myParticle;
    //
    //        float vx = ofRandom(-10,10);
    //        float vy = ofRandom(-10,10);
    //        myParticle.setIntialCondition(x, y, vx, vy);
    //
    //        particles.push_back(myParticle);
    //
    //    }
    shape.clear();
    shape.addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    // first simplify the shape
    shape.simplify();
    
    // save the outline of the shape
    ofPolyline outline = shape;
    
    // resample shape
    ofPolyline resampled = shape.getResampledBySpacing(25);
    
    // trangleate the shape, return am array of traingles
    vector <TriangleShape> tris = triangulatePolygonWithOutline(resampled, outline);
    
    // add some random points inside
    addRandomPointsInside(shape, 255);
    
    // now loop through all the trainles and make a box2d triangle
    for (int i=0; i<tris.size(); i++) {
        
        shared_ptr<ofxBox2dPolygon> triangle = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
        triangle->addTriangle(tris[i].a, tris[i].b, tris[i].c);
        triangle->setPhysics(1.0, 0.3, 0.3);
        triangle->create(box2d.getWorld());
        
        polyShapes.push_back(triangle);
    }
    

    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
