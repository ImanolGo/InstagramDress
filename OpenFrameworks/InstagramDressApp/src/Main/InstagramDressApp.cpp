/*
 *  InstagramDressApp.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "AppManager.h"

#include "InstagramDressApp.h"

//--------------------------------------------------------------
void InstagramDressApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void InstagramDressApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void InstagramDressApp::draw(){
    AppManager::getInstance().draw();
}

void InstagramDressApp::exit()
{
    ofLogNotice() <<"InstagramDressApp::exit";
    AppManager::getInstance().exit();
}

//--------------------------------------------------------------
void InstagramDressApp::keyPressed(int key){

}

//--------------------------------------------------------------
void InstagramDressApp::keyReleased(int key){

}

//--------------------------------------------------------------
void InstagramDressApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void InstagramDressApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void InstagramDressApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void InstagramDressApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void InstagramDressApp::windowResized(int w, int h)
{
    AppManager::getInstance().getLayoutManager().windowResized(w,h);
}

//--------------------------------------------------------------
void InstagramDressApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void InstagramDressApp::dragEvent(ofDragInfo dragInfo)
{
}
